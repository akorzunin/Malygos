#include "GyverButton.h"
#include <TM1637Display.h>
#include "GyverTimer.h" 
#include <Adafruit_NeoPixel.h>
#include <TM1637Display.h>
#include <ArduinoQueue.h>

#include "Programming_prototype_sketch.h"


// timers
GTimer myTimer(MS, 3000); //?
GTimer stripTimer(MS, 1000); 
GTimer led_timer(MS); //?
GTimer test_mode_timer(MS);

// rows of LED strip
Adafruit_NeoPixel strip_1 = Adafruit_NeoPixel(NUM_LEDS, PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_2 = Adafruit_NeoPixel(NUM_LEDS, PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_3 = Adafruit_NeoPixel(NUM_LEDS, PIN_3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_4 = Adafruit_NeoPixel(NUM_LEDS, PIN_4, NEO_GRB + NEO_KHZ800);

//menu buttons
GButton modeBtn(MODE_BTN_PIN);
GButton selectBtn(SELECT_BTN_PIN);
GButton resetBtn(RESET_BTN_PIN);
GButton debugBtn(DEBUG_BTN_PIN);

//queue object setup
ArduinoQueue<u8> ButtonsQueue(BUTTONS_QUANTITY);

//4 bit ss setup
TM1637Display display(CLK, DIO);

//interrupt var
volatile bool interrupt_state = 0;

bool CGK_init_flag, BR_init_flag, W_SHOOTER_init, SWOYA_GAME_init, test_mode_init_flag;
bool strip_blink_flag;

u8 CGK_state, BR_state, WS_state, SG_state;
u8 test_state = 0; //? mb add up, mb delete
u8 THE_FINAL_COUNTDOWN; //var to indicate time in game modes
u8 menu_state = 1;
u8 btn_buffer[BUTTONS_QUANTITY] = {}; //array with already pressed btns
u8 blink_buffer[BUTTONS_QUANTITY] = {}; //array with buttons to blink

u16 strip_mp = 2; //multiplyer for LED strip to indicate conuntdown right

//timers with millis()
uint32_t test_timer;
uint32_t final_timer;
uint32_t tone_timer;

void setup() {
    //init array with state 1
    for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
        buttons_state[i] = 1;              
    }
    // init buffer with state 1
    for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
        btn_buffer[i] = 1;              
    }
    //buttons and led setup
    for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
        pinMode(led_pins[i], OUTPUT);                 
    }
        
    // initialize the pushbutton pin as an INPUT_PULLUP:
    for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
        pinMode(button_pins[i], INPUT_PULLUP);                 
    }
    
    // init pins for 1bit ss
    for(u8 i = 0; i < 8; i++){
        pinMode(seg_1bit[i], OUTPUT); 
        digitalWrite(seg_1bit[i] , ONEBIT_LOW);                
    }

    // init pins for LED srip
    pinMode( PIN_1, OUTPUT);
    pinMode( PIN_2, OUTPUT);
    pinMode( PIN_3, OUTPUT);
    pinMode( PIN_4, OUTPUT);
  
    //init 4bit ss 
    display.setBrightness(0x0f);
    uint8_t data[] = { 0x0, 0x0, 0x0, 0x0 };
    display.setSegments(data);
    
    //init audio pin
    pinMode(SOUND_PIN, OUTPUT);

    //init COM port 
    Serial.begin(9600);

    //led strip setup
    strip_1.begin();
    strip_1.setBrightness(LED_STR_BR);    // brightness from 0 to 255
    strip_1.clear();                      
    strip_1.show();                       

    strip_2.begin();
    strip_2.setBrightness(LED_STR_BR);    
    strip_2.clear();                          
    strip_2.show();
    
    strip_3.begin();
    strip_3.setBrightness(LED_STR_BR);    
    strip_3.clear();                         
    strip_3.show();

    strip_4.begin();
    strip_4.setBrightness(LED_STR_BR);    
    strip_4.clear();                      
    strip_4.show();
    
    //init interrupt to poll player buttons
    pinMode( INTERRUPT_3, INPUT);
    attachInterrupt(3, buttonTick, RISING); //buttonTick это функция прерывания никто не знает почему там должен быть 0 но иначе не работает 0/3
  
    //init menu buttons
    modeBtn.setDebounce(SELECT_DEBOUNCE);        // настройка антидребезга (по умолчанию 80 мс)
    modeBtn.setTimeout(HOLD_TIMEOUT);        // настройка таймаута на удержание (по умолчанию 500 мс)
    modeBtn.setClickTimeout(CLICK_TIMEOUT);   // настройка таймаута между кликами (по умолчанию 300 мс)
  
    selectBtn.setDebounce(DEBOUNCE);        // настройка антидребезга (по умолчанию 80 мс)
    selectBtn.setTimeout(HOLD_TIMEOUT);        // настройка таймаута на удержание (по умолчанию 500 мс)
    selectBtn.setClickTimeout(SELECT_CLICK_TIMEOUT);   // настройка таймаута между кликами (по умолчанию 300 мс)
  
    resetBtn.setDebounce(DEBOUNCE);        // настройка антидребезга (по умолчанию 80 мс)
    resetBtn.setTimeout(HOLD_TIMEOUT);        // настройка таймаута на удержание (по умолчанию 500 мс)
    resetBtn.setClickTimeout(CLICK_TIMEOUT);   // настройка таймаута между кликами (по умолчанию 300 мс)
    
    debugBtn.setDebounce(DEBOUNCE);

    test_timer = millis(); //?
    led_timer.setTimeout(1500); //?
    strip_mp = CGK_main_time/STRIP_LED_NUM;
    test_mode_timer.setTimeout(20);
}

void loop() {
    // poll menu buttons
    menu_buttons_tick(); 
  
    if (modeBtn.isSingle()){ 
        menu_state++ ; //перелистывание разделов меню
        
        BR_init_flag = false;
        CGK_init_flag = false;
        W_SHOOTER_init = false;
        SWOYA_GAME_init = false;
        test_mode_init_flag = false;
        
        disp_1bit_7seg(0); //petrify 1 bit ss
        display.clear(); // petrify 4 bit ss
  }

    if(stripTimer.isReady()){  
        //handle blinking with strip and button LEDs
        strip_blink_flag = !strip_blink_flag;
        if(strip_blink_flag){
            //enable all blinking buttons
            for (u8 i = 0; i < BUTTONS_QUANTITY; ++i)
            {
            if (blink_buffer[i]) {
                static_btn_strip(i, true);
                static_lamp(i, true);
                }
            }
        }
    else{
        //disable all blinking buttons
        for (u8 i = 0; i < BUTTONS_QUANTITY; ++i)
        {
            if (blink_buffer[i]) {
                static_btn_strip(i, false);
                static_lamp(i, false);
            }
        }
    }
    led_strip_show();
  }

    //menu
    switch(menu_state) {      
        case 0:
        CGK_function(); //ЧГК -0
        break;
        case 1:
        BRAIN_RING_function();  //Брейн ринг - 1
        break;
        case 2:
        W_SHOOTER_function();  //Ворошиловский снайперок - 2
        break;
        case 3:
        SVOYA_GAME_function();  //Своя игра - 3
        break;
        case 4:
        #ifdef DEBUG
        test_mode();
        #endif
        break;
        default:
        menu_state = 0;
        break;
    }
    
    if (interrupt_state == 1){ //выполнение действий по прерыванию
        interrupt_state = 0;
    }
}




