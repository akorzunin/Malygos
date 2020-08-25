
#define PIN_1 2        
#define PIN_2 3 
#define PIN_3 4 
#define NUM_LEDS 30   // число диодов на ленте
#define CLK 52
#define DIO 53
#define SOUND_PIN 19

#include <Adafruit_NeoPixel.h>
#include <TM1637Display.h>


Adafruit_NeoPixel strip_1 = Adafruit_NeoPixel(NUM_LEDS, PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_2 = Adafruit_NeoPixel(NUM_LEDS, PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_3 = Adafruit_NeoPixel(NUM_LEDS, PIN_3, NEO_GRB + NEO_KHZ800);






int8_t DispMSG[] = {1, 2, 3, 4}; 
 
// constants won't change. They're used here to set pin numbers:
const int buttonPin_37 = 37;
const int buttonPin_38 = 38;
const int buttonPin_39 = 39;
const int buttonPin_40 = 40;
const int buttonPin_41 = 41;
const int buttonPin_42 = 42;
const int buttonPin_43 = 43;
const int buttonPin_44 = 44;
const int buttonPin_45 = 45;
const int buttonPin_46 = 46;
const int buttonPin_47 = 47;
const int buttonPin_48 = 48;
const int buttonPin_49 = 49;
const int buttonPin_50 = 50;
const int buttonPin_51 = 51;


const int ledPin_22 = 22;
const int ledPin_23 = 23;
const int ledPin_24 = 24;
const int ledPin_25 = 25;
const int ledPin_26 = 26;
const int ledPin_27 = 27;
const int ledPin_28 = 28;
const int ledPin_29 = 29;
const int ledPin_30 = 30;
const int ledPin_31 = 31;
const int ledPin_32 = 32;
const int ledPin_33 = 33;
const int ledPin_34 = 34;
const int ledPin_35 = 35;
const int ledPin_36 = 36;

const int seg_1bit_pin_A = 6;
const int seg_1bit_pin_B = 7;
const int seg_1bit_pin_C = 8;
const int seg_1bit_pin_D = 9;
const int seg_1bit_pin_E = 10;
const int seg_1bit_pin_F = 11;
const int seg_1bit_pin_G = 12;
const int seg_1bit_pin_DP = 13;

int buttonState = 0;         
u8 led;
bool m_state = 1;
uint8_t tru_state;
u8 seg_1bit_pin = 6;

TM1637Display display(CLK, DIO);

void setup() {
  // initialize the LED pin as an output:
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

  pinMode( PIN_1, OUTPUT);
  pinMode( PIN_2, OUTPUT);
  pinMode( PIN_3, OUTPUT);

  display.setBrightness(0x0f);
  uint8_t data[] = { 0x0, 0x0, 0x0, 0x0 };
  display.setSegments(data);

  Serial.begin(9600);

  pinMode(SOUND_PIN, OUTPUT);

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

void loop() {


 //заливаем трёмя цвет_1ами плавно
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
  
  for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
    strip_1.setPixelColor(i, 0xffffff);     // залить белым
    strip_1.show();                         // отправить на ленту
    delay(500);
  }
  delay(1000);
  // заливаем чёрным
  for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
    strip_2.setPixelColor(i, 0xff0000);     // залить чёрным
    strip_2.show();                         // отправить на ленту
    delay(500);
  }
  delay(1000);
  // включаем случайные диоды жёлтым
  for (int i = 0; i < NUM_LEDS; i++ ) {         // 50 раз
    strip_3.setPixelColor(i, 0xffff00);     // залить жёлтым
    strip_3.show();                         // отправить на ленту
    delay(500);
  }




  
  delay(1000);
    for (led = 22; led <= (22+14);led++){
    if(m_state) tru_state = HIGH;
    else tru_state = LOW;
    digitalWrite (led, tru_state);
    display.showNumberDec(led, false, 4,0);
   
    Serial.println(led);

    
    digitalWrite(seg_1bit_pin, tru_state);
    seg_1bit_pin++;
    if(seg_1bit_pin == 14) seg_1bit_pin = 6;
    delay(1000);   
  }
  m_state = !m_state;
  tone(SOUND_PIN, 500, 500);
} 
