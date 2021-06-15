#include "GyverButton.h"
#include <TM1637Display.h>
#include "GyverTimer.h" 
#include <Adafruit_NeoPixel.h>
#include <TM1637Display.h>
#include <ArduinoQueue.h>

#include "Programming_prototype_sketch.h"



// timers
GTimer myTimer(MS, 3000);
GTimer stripTimer(MS, 1000);
GTimer led_timer(MS);

//линии адресной СД ленты
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

//Константя для прерываний
volatile bool interrupt_state = 0;

u8 menu_state = 4;

//таймеры
uint32_t test_timer;
uint32_t final_timer;
uint32_t tone_timer;

u8 THE_FINAL_COUNTDOWN;
u8 CGK_state;

u8 btn_buffer[BUTTONS_QUANTITY] = {};
u8 blink_buffer[BUTTONS_QUANTITY] = {};


 enum {
  BR_init,
  BR_null,
  BR_timer_50,
  BR_timer_55,
  BR_timer_60,
  BR_answer,
  BR_endgame,
  BR_false_start,
} BR_states;


bool CGK_init_flag, BR_init_flag, W_KILLER_init, SWOYA_GAME_init;
u16 strip_mp = 2;//множитель для отношения времени к числу зажженных сд на ленте

u8 BR_state;
u8 test_state;

bool strip_blink_flag;

void setup() {
    //инициализация массива с состояниями кнопок, в массиве должны быть все 1 если ни одна кнопка не нажата
    for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
        buttons_state[i] = 1;              
    }
    // инициализация буфера нажатых кнопок
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
    // pinMode(43, INPUT);
    
    //инициализация пинов для однобитового 7сегментного индикатора для отображения режима игры
      for(u8 i = 0; i < 8; i++){
        pinMode(seg_1bit[i], OUTPUT); 
        digitalWrite(seg_1bit[i] , ONEBIT_LOW);                
    }

    //инициализация СД ленты
    pinMode( PIN_1, OUTPUT);
    pinMode( PIN_2, OUTPUT);
    pinMode( PIN_3, OUTPUT);
    pinMode( PIN_4, OUTPUT);
  
    //4 ьитовый 7сегм дисплей 
    display.setBrightness(0x0f);
    uint8_t data[] = { 0x0, 0x0, 0x0, 0x0 };
    display.setSegments(data);
    //пин аудио
    pinMode(SOUND_PIN, OUTPUT);

    Serial.begin(9600);

    //led strip setup
    strip_1.begin();
    strip_1.setBrightness(LED_STR_BR);    // яркость, от 0 до 255
    strip_1.clear();                          // очистить
    strip_1.show();                           // отправить на ленту

    strip_2.begin();
    strip_2.setBrightness(LED_STR_BR);    // яркость, от 0 до 255
    strip_2.clear();                          
    strip_2.show();
    
    strip_3.begin();
    strip_3.setBrightness(LED_STR_BR);    // яркость, от 0 до 255
    strip_3.clear();                          // очистить
    strip_3.show();

    strip_4.begin();
    strip_4.setBrightness(LED_STR_BR);    // яркость, от 0 до 255
    strip_4.clear();                          // очистить
    strip_4.show();
    

    //прерывание по которыму триггерится опрос кнопок
    pinMode( INTERRUPT_3, INPUT);
    attachInterrupt(3, buttonTick, RISING); //buttonTick это функция прерывания никто не знает почему там должен быть 0 но иначе не работает 0/3
  
    //кнопки меню
  //пока что не работает надо либо настроить либо убрать совсем
   modeBtn.setDebounce(DEBOUNCE);        // настройка антидребезга (по умолчанию 80 мс)
   // modeBtn.setTimeout(SELECT_BTN_PIN);        // настройка таймаута на удержание (по умолчанию 500 мс)
   // modeBtn.setClickTimeout(CLICK_TIMEOUT);   // настройка таймаута между кликами (по умолчанию 300 мс)
  //
   selectBtn.setDebounce(DEBOUNCE);        // настройка антидребезга (по умолчанию 80 мс)
   // selectBtn.setTimeout(SELECT_BTN_PIN);        // настройка таймаута на удержание (по умолчанию 500 мс)
   // selectBtn.setClickTimeout(CLICK_TIMEOUT);   // настройка таймаута между кликами (по умолчанию 300 мс)
  ////
   resetBtn.setDebounce(DEBOUNCE);        // настройка антидребезга (по умолчанию 80 мс)
   // resetBtn.setTimeout(SELECT_BTN_PIN);        // настройка таймаута на удержание (по умолчанию 500 мс)
   // resetBtn.setClickTimeout(CLICK_TIMEOUT);   // настройка таймаута между кликами (по умолчанию 300 мс)
  debugBtn.setDebounce(DEBOUNCE);
      test_timer = millis();
      led_timer.setTimeout(1500);
      strip_mp = CGK_main_time/STRIP_LED_NUM;
}

void loop() {
  //часть кода которую надо выполнить не зависимо от игрового режима
  menu_buttons_tick(); // опрос кнопок меню
  if (modeBtn.isSingle()){ //перелистывание разделов меню
    menu_state++ ;
    BR_init_flag = false; //c этим надо что-то сделать так нельзя мб засунуть в стракт или в массив
    CGK_init_flag = false;
    W_KILLER_init = false;
    SWOYA_GAME_init = false;
    // BR_state = BR_init; // верменное решение пока режим не доконца прописан
    disp_1bit_7seg(0); //petrify 1 bit ss
    display.clear();// очистить 4 битный семисегмент

  }

  // if (debugBtn.isSingle()) DebugFunction();
 
//отобразить состояние ленты раз в секунду TODO mb delete after
  if(stripTimer.isReady()){  
    strip_1.show(); 
    strip_2.show(); 
    strip_3.show();
    strip_4.show();
    //мб тут описать как вывод раз в секунду мигания илихз
    // Serial.println("PEPE");
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
  }

 
//отображение на ленте нажатой кнопки
//  for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
//  
//    if (!buttons_state[i]) {
//      display_btn_strip(i, 3);
//    }
// }

 //разделы меню
  switch(menu_state) {      
  case 0:
  CGK_function(); //ЧГК -0
  break;
  case 1:
  BRAIN_RING_function();  //Брейн ринг - 1
  break;
  case 2:
  W_KILLER_function();  //Ворошиловский снайперок - 2
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




