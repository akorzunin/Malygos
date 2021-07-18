// Файл с насторйками для прошивки

// В режиме DEBUG выводится информация для отладки в СОМ порт
#define DEBUG 

//коллическтво кнопок игроков
#define BUTTONS_QUANTITY 15 

//пины кнопок
#define MODE_BTN_PIN 15 
#define SELECT_BTN_PIN 16
#define RESET_BTN_PIN 17
#define DEBUG_BTN_PIN 14

//настройки для обработки кнопок меню [мс]
#define DEBOUNCE 1 //антидребезг
#define HOLD_TIMEOUT 500 //удрежание
#define CLICK_TIMEOUT 300 //одиночное нажатие
// более быстрая обработка кнопки SLELECT 
#define SELECT_CLICK_TIMEOUT 1


//настройки адресной светодиодной ленты
//пины для вывода данных на ленту  
#define PIN_1 2     
#define PIN_2 3 
#define PIN_3 4 
#define PIN_4 5

// яркость СД ленты
#define LED_STR_BR 50

#define NUM_LEDS 30   // число диодов в ленте
#define STRIP_LED_NUM 15 //чило секций на ленте(должно соответствовать числу кнопок)
#define LED_STRIP_ROWS 4

//пин прерывания для опроса кнопок игроков
#define INTERRUPT_3 21 

//пины для 4битового 7-и сегментного индикатора
#define CLK 52 
#define DIO 53 

// пин для вывода звука на усилитель
#define SOUND_PIN 19

//настройки звуковых сигналов
#define SHORT_SHORT_TONE_DUR 100
#define SHORT_TONE_DUR 300
#define LONG_TONE_DUR 1000
#define TONE_FREQ 500

//константы из игровых режимов

// режим ЧТО ГДЕ КОГДА
#define CGK_main_time 60
#define CGK_sub_time 10
#define CGK_sub_sub_time 5

// режим БРЕЙН РИНГ
#define BR_main_time 60
#define BR_sub_time_10 10
#define BR_sub_time_5 5

// режим ВОРОШИЛОВСКИЙ СТРЕЛОК
#define WS_REFRESH_TIME 300

// режим СВОЯ ИГРА
#define SG_MAIN_TIME 7
//если true, позволяет нажимать кнопку игрока несколько раз
#define SG_QUEUE_MODE 1 



int8_t DispMSG[] = {1, 2, 3, 4}; //?
 
// пины кнопок для игроков
#define buttonPin_0 37
#define buttonPin_1 38
#define buttonPin_2 39
#define buttonPin_3 40
#define buttonPin_4 41
#define buttonPin_5 42
#define buttonPin_6 43
#define buttonPin_7 44
#define buttonPin_8 45
#define buttonPin_9 46
#define buttonPin_10 47
#define buttonPin_11 48
#define buttonPin_12 49
#define buttonPin_13 50
#define buttonPin_14 51

// массив с номерами кнопок игроков
const u8 button_pins[]{
  buttonPin_0, 
  buttonPin_1,
  buttonPin_2, 
  buttonPin_3, 
  buttonPin_4, 
  buttonPin_5, 
  buttonPin_6, 
  buttonPin_7, 
  buttonPin_8, 
  buttonPin_9, 
  buttonPin_10, 
  buttonPin_11, 
  buttonPin_12, 
  buttonPin_13, 
  buttonPin_14 
};

// массив-буфер для храниения состояния кнопок поле опроса по прерыванию
volatile u8 buttons_state[BUTTONS_QUANTITY]; 

//пины для управления светодиодными лампами над кнопками
#define ledPin_0 22
#define ledPin_1 23
#define ledPin_2 24
#define ledPin_3 25
#define ledPin_4 26
#define ledPin_5 27
#define ledPin_6 28
#define ledPin_7 29
#define ledPin_8 30
#define ledPin_9 31
#define ledPin_10 32
#define ledPin_11 33
#define ledPin_12 34
#define ledPin_13 35
#define ledPin_14 36

// массив с лампами игроков
const u8 led_pins[] = {
  ledPin_0, 
  ledPin_1, 
  ledPin_2, 
  ledPin_3, 
  ledPin_4, 
  ledPin_5, 
  ledPin_6, 
  ledPin_7, 
  ledPin_8, 
  ledPin_9, 
  ledPin_10, 
  ledPin_11, 
  ledPin_12, 
  ledPin_13, 
  ledPin_14 
};

//массив с состояниями светодиодов над кнопками
u8 leds_state[BUTTONS_QUANTITY]; 
//массив который помнит, кто уже в очереди 
u8 inQueue[BUTTONS_QUANTITY]; 

//пины одновитного семисегментного индикатора
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

//common anode/cathode for 1bit ss
// настройка режима с общим анодом/общим катодом для 1-битного семисегментного индикатора
#define ONEBIT_LOW 1 //
#define ONEBIT_HIGH 0

