#include "GyverButton.h"
#include <TM1637Display.h>
#include "GyverTimer.h" 
#include <Adafruit_NeoPixel.h>

#define MODE_BTN_PIN 15
#define SELECT_BTN_PIN 16
#define RESET_BTN_PIN 17

#define BUTTONS_QUANTITY 15

//gyver button настройки для обработки кнопок меню

#define DEBOUNCE 50 //антидребезг
#define HOLD_TIMEOUT 300
#define CLICK_TIMEOUT 600

#define PIN_1 5        // пин DI
#define PIN_2 3 
#define PIN_3 4 
#define NUM_LEDS 30   // число диодо
#define STRIP_LED_NUM 15 //чило секций на ленте(должно соответствовать числу кнопок)
#define INTERRUPT_3 2 //прерывание кнопок просто настраиваем этот пин на чтение оно не на что особо не влияет потому что в функции стоит 0 пин но работает пин 2

GTimer myTimer(MS, 3000);

GTimer led_timer(MS);

Adafruit_NeoPixel strip_1 = Adafruit_NeoPixel(NUM_LEDS, PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_2 = Adafruit_NeoPixel(NUM_LEDS, PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_3 = Adafruit_NeoPixel(NUM_LEDS, PIN_3, NEO_GRB + NEO_KHZ800);


GButton modeBtn(MODE_BTN_PIN);
GButton selectBtn(SELECT_BTN_PIN);
GButton resetBtn(RESET_BTN_PIN);


#include <TM1637Display.h>

#define CLK 52
#define DIO 53
#define SOUND_PIN 19

//константы с игровых режимов
#define CGK_main_time 60
#define CGK_sub_time 10


int8_t DispMSG[] = {1, 2, 3, 4}; 
 
// constants won't change. They're used here to set pin numbers:
#define buttonPin_37 37
#define buttonPin_38 38
#define buttonPin_39 39
#define buttonPin_40 40
#define buttonPin_41 41
#define buttonPin_42 42
#define buttonPin_43 43
#define buttonPin_44 44
#define buttonPin_45 45
#define buttonPin_46 46
#define buttonPin_47 47
#define buttonPin_48 48
#define buttonPin_49 49
#define buttonPin_50 50
#define buttonPin_51 51

const u8 button_pins[]{
  buttonPin_37, 
  buttonPin_38,
  buttonPin_39, 
  buttonPin_40, 
  buttonPin_41, 
  buttonPin_42, 
  buttonPin_43, 
  buttonPin_44, 
  buttonPin_45, 
  buttonPin_46, 
  buttonPin_47, 
  buttonPin_48, 
  buttonPin_49, 
  buttonPin_50, 
  buttonPin_51 
};

volatile u8 buttons_state[15]; // массив который хранит информацию собранную после опроса кнопок по прерыванию


#define ledPin_22 22
#define ledPin_23 23
#define ledPin_24 24
#define ledPin_25 25
#define ledPin_26 26
#define ledPin_27 27
#define ledPin_28 28
#define ledPin_29 29
#define ledPin_30 30
#define ledPin_31 31
#define ledPin_32 32
#define ledPin_33 33
#define ledPin_34 34
#define ledPin_35 35
#define ledPin_36 36

const u8 led_pins[] = {
  ledPin_22, 
  ledPin_23, 
  ledPin_24, 
  ledPin_25, 
  ledPin_26, 
  ledPin_27, 
  ledPin_28, 
  ledPin_29, 
  ledPin_30, 
  ledPin_31, 
  ledPin_32, 
  ledPin_33, 
  ledPin_34, 
  ledPin_35, 
  ledPin_36 
};
u8 leds_state[15]; //массив с состояниями светодиодов над кнопками

#define seg_1bit_pin_A 6
#define seg_1bit_pin_B 7
#define seg_1bit_pin_C 8
#define seg_1bit_pin_D 9
#define seg_1bit_pin_E 10
#define seg_1bit_pin_F 11
#define seg_1bit_pin_G 12
#define seg_1bit_pin_DP 13

const char seg_1bit[] = {
  seg_1bit_pin_A, 
  seg_1bit_pin_B, 
  seg_1bit_pin_C,
  seg_1bit_pin_D,
  seg_1bit_pin_E,
  seg_1bit_pin_F,
  seg_1bit_pin_G,
  seg_1bit_pin_DP,
  };
  
// the number of the LED pin
 
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
u8 led;
bool state = 1;
uint8_t tru_state;
u8 seg_1bit_pin = 6;
u8 button_state = 0;
u8 led_state = 0;
u8 current_button_pin = 37;

TM1637Display display(CLK, DIO);

//Константя для прерываний
volatile bool interrupt_state = 0;

u8 menu_state;

//таймеры
uint32_t test_timer;
uint32_t final_timer;

u8 THE_FINAL_COUNTDOWN;
u8 CGK_state;
enum {
   start_CGK,
   CGK_50,
   CGK_10,
   end_CGK,
   n0ll_CGK,
} CGK_states;

bool CGK_init, BRAIN_RING_init, W_KILLER_init, SWOYA_GAME_init;
u16 strip_mp = 2;//множитель для отношения времени к числу зажженных сд на ленте



void setup() {
  //инициализация массива с состояниями кнопок
  for(u8 i = 0; i < (BUTTONS_QUANTITY); i++){
      buttons_state[i] = 1; //опрос через обычные функции пока что button_pins[current_button_pin]              
  }
  // initialize the LED pin as an output:
{ //buttons and led setup
  pinMode(ledPin_22, OUTPUT);
  pinMode(ledPin_23, OUTPUT);
  pinMode(ledPin_24, OUTPUT);
  pinMode(ledPin_25, OUTPUT);
  pinMode(ledPin_26, OUTPUT);
  pinMode(ledPin_27, OUTPUT);
  pinMode(ledPin_28, OUTPUT);
  pinMode(ledPin_29, OUTPUT);
  pinMode(ledPin_30, OUTPUT);
  pinMode(ledPin_31, OUTPUT);
  pinMode(ledPin_32, OUTPUT);
  pinMode(ledPin_33, OUTPUT);
  pinMode(ledPin_34, OUTPUT);
  pinMode(ledPin_35, OUTPUT);
  pinMode(ledPin_36, OUTPUT);
  
  
  // initialize the pushbutton pin as an INPUT_PULLUP:
  pinMode(buttonPin_37, INPUT_PULLUP);
  pinMode(buttonPin_38, INPUT_PULLUP);
  pinMode(buttonPin_39, INPUT_PULLUP);
  pinMode(buttonPin_40, INPUT_PULLUP);
  pinMode(buttonPin_41, INPUT_PULLUP);
  pinMode(buttonPin_42, INPUT_PULLUP);
  pinMode(buttonPin_43, INPUT_PULLUP);
  pinMode(buttonPin_44, INPUT_PULLUP);
  pinMode(buttonPin_45, INPUT_PULLUP);
  pinMode(buttonPin_46, INPUT_PULLUP);
  pinMode(buttonPin_47, INPUT_PULLUP);
  pinMode(buttonPin_48, INPUT_PULLUP);
  pinMode(buttonPin_49, INPUT_PULLUP);
  pinMode(buttonPin_50, INPUT_PULLUP);
  pinMode(buttonPin_51, INPUT_PULLUP);


  pinMode( seg_1bit_pin_A, OUTPUT);
  pinMode( seg_1bit_pin_B, OUTPUT);
  pinMode( seg_1bit_pin_C, OUTPUT);
  pinMode( seg_1bit_pin_D, OUTPUT);
  pinMode( seg_1bit_pin_E, OUTPUT);
  pinMode( seg_1bit_pin_F, OUTPUT);
  pinMode( seg_1bit_pin_G, OUTPUT);
  pinMode( seg_1bit_pin_DP, OUTPUT);

  pinMode( INTERRUPT_3, INPUT);

  pinMode( PIN_1, OUTPUT);
  pinMode( PIN_2, OUTPUT);
  pinMode( PIN_3, OUTPUT);
}
  
  display.setBrightness(0x0f);
  uint8_t data[] = { 0x0, 0x0, 0x0, 0x0 };
  display.setSegments(data);

  Serial.begin(9600);

  pinMode(SOUND_PIN, OUTPUT);

  
 
  { //led strip setup
  strip_1.begin();
  strip_1.setBrightness(255);    // яркость, от 0 до 255
  strip_1.clear();                          // очистить
  strip_1.show();                           // отправить на ленту

  strip_2.begin();
  strip_2.setBrightness(255);    // яркость, от 0 до 255
  strip_2.clear();                          
  strip_2.show();
  
  strip_3.begin();
  strip_3.setBrightness(255);    // яркость, от 0 до 255
  strip_3.clear();                          // очистить
  strip_3.show();
  }
  //прерывания

  attachInterrupt(3, buttonTick, RISING); //buttonTick это функция прерывания никто не знает почему там должен быть 0 но иначе не работает 0/3
{
  //кнопки меню
//пока что не работает надо либо настроить либо убрать совсем
//  modeBtn.setDebounce(DEBOUNCE);        // настройка антидребезга (по умолчанию 80 мс)
//  modeBtn.setTimeout(SELECT_BTN_PIN);        // настройка таймаута на удержание (по умолчанию 500 мс)
//  modeBtn.setClickTimeout(CLICK_TIMEOUT);   // настройка таймаута между кликами (по умолчанию 300 мс)
//
//  selectBtn.setDebounce(DEBOUNCE);        // настройка антидребезга (по умолчанию 80 мс)
//  selectBtn.setTimeout(SELECT_BTN_PIN);        // настройка таймаута на удержание (по умолчанию 500 мс)
//  selectBtn.setClickTimeout(CLICK_TIMEOUT);   // настройка таймаута между кликами (по умолчанию 300 мс)
////
//  resetBtn.setDebounce(DEBOUNCE);        // настройка антидребезга (по умолчанию 80 мс)
//  resetBtn.setTimeout(SELECT_BTN_PIN);        // настройка таймаута на удержание (по умолчанию 500 мс)
//  resetBtn.setClickTimeout(CLICK_TIMEOUT);   // настройка таймаута между кликами (по умолчанию 300 мс)
}
    test_timer = millis();
    led_timer.setTimeout(1500);
    strip_mp = CGK_main_time/STRIP_LED_NUM;
}

void loop() {
  menu_buttons_tick(); // опрос кнопок меню
  if (selectBtn.isSingle()){
    menu_state++ ;
    BRAIN_RING_init = false; //c этим надо что-то сделать так нельзя мб засунуть в стракт или в массив
    CGK_init = false;
    W_KILLER_init = false;
    SWOYA_GAME_init = false;
    clean_7seg_1bit(); //petrify
  }
 if(myTimer.isReady()){
    for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
      digitalWrite(led_pins[i], 0);
    }
  
    for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
    leds_state[i] = buttons_state[i];
    if(leds_state[i] == !1) digitalWrite(led_pins[i], 1);
  // Serial.println(leds_state[i]);
    }
  
   
  
 }


//  Serial.println(menu_state);
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
  default:
  menu_state = 0;
  break;
  }
  
   
  if(resetBtn.isDouble()){
    for(u8 i = 0; i < 15; i++){
      Serial.println(buttons_state[i]);
    }
    
  }
  
  if (interrupt_state == 1){

    interrupt_state = 0;
  }




 //  if(((millis() - test_timer) >= 1000) && (resetBtn.isSingle() )) {
//    tone(SOUND_PIN, 500, 100);
//    test_timer = millis();
//  }
{
  

//тест кнопок меню
//modeBtn.tick();  // обязательная функция отработки. Должна постоянно опрашиваться

// // if (modeBtn.isClick()) Serial.println("M_Click");         // проверка на один клик
//  if (modeBtn.isSingle()) Serial.println("M_Single");       // проверка на один клик
//  if (modeBtn.isDouble()) Serial.println("M_Double");       // проверка на двойной клик
//  if (modeBtn.isTriple()) Serial.println("M_Triple");       // проверка на тройной клик
//selectBtn.tick();  // обязательная функция отработки. Должна постоянно опрашиваться
//
//  //if (selectBtn.isClick()) Serial.println("S_Click");         // проверка на один клик
//  if (selectBtn.isSingle()) Serial.println("S_Single");       // проверка на один клик
//  if (selectBtn.isDouble()) Serial.println("S_Double");       // проверка на двойной клик
//  if (selectBtn.isTriple()) Serial.println("S_Triple");       // проверка на тройной клик
//
//resetBtn.tick();  // обязательная функция отработки. Должна постоянно опрашиваться
//
//  //if (resetBtn.isClick()) Serial.println("R_Click");         // проверка на один клик
//  if (resetBtn.isSingle()) Serial.println("R_Single");       // проверка на один клик
//  if (resetBtn.isDouble()) Serial.println("R_Double");       // проверка на двойной клик
//  if (resetBtn.isTriple()) Serial.println("R_Triple");       // проверка на тройной клик

//    strip_3.setPixelColor(3, 0xffff00);     // залить жёлтым
//    strip_3.show();


}
  
}

// заливаем трёмя цвет_1ами плавно
//  for (int i = 0; i < NUM_LEDS / 3; i++ ) {   // _1от 0 до первой трети
//    strip.setPixelColor(i, 0xff0000);     // залить красным
//    strip.show();                         // отправить на ленту
//    delay(100);_1
//  }
//  for (int i = NUM_LEDS / 3; i < NUM_LEDS * 2 / 3; i+_1+ ) {   // от 1/3 до 2/3
//    strip.setPixelColor(i, 0x00ff00);     // залить зелёным
//    strip.show();                         // отправить на ленту
//    delay(100);
//  }
//  for (int i = NUM_LEDS * 2 / 3; i < NUM_LEDS; i++ ) {   // от 2/3 до конца
//    strip.setPixelColor(i, 0x0000ff);     // залить синим
//    strip.show();                         // отправить на ленту
//    delay(100);
//  }
//  delay(1000);

  
//  for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
//    strip_1.setPixelColor(i, 0xffffff);     // залить белым
//    strip_1.show();                         // отправить на ленту
//    delay(500);
//  }
//  delay(1000);
//  // заливаем чёрным
//  for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
//    strip_2.setPixelColor(i, 0xff0000);     // залить чёрным
//    strip_2.show();                         // отправить на ленту
//    delay(500);
//  }
//  delay(1000);
//  // включаем случайные диоды жёлтым
//  for (int i = 0; i < NUM_LEDS; i++ ) {         // 50 раз
//    strip_3.setPixelColor(i, 0xffff00);     // залить жёлтым
//    strip_3.show();                         // отправить на ленту
//    delay(500);
//  }




  
//  delay(1000);
//    for (led = 22; led <= (22+14);led++){
//    if(state) tru_state = HIGH;
//    else tru_state = LOW;
//    digitalWrite (led, tru_state);
//    display.showNumberDec(led, false, 4,0);
//   
//    Serial.println(led);
//
//    
//    digitalWrite(seg_1bit_pin, tru_state);
//    seg_1bit_pin++;
//    if(seg_1bit_pin == 14) seg_1bit_pin = 6;
//    delay(1000);   
//  }
//  state = !state;
//  tone(SOUND_PIN, 500, 500); 
