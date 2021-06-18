

void buttonTick(){ //функция прерыввания по опросу кнопок игроков
  interrupt_state = 1;
  #ifdef DEBUG
  Serial.println("interrupt");
  #endif
    for(u8 i = 0; i < (BUTTONS_QUANTITY); i++){

      buttons_state[i] = !digitalRead(button_pins[i]);               
    
    } 
  // buttons_state[6] = 1; //временный костыль против нерабочей кнопки
}


void menu_buttons_tick(){ //опрос кнопок меню
   modeBtn.tick(); 
   selectBtn.tick();
   resetBtn.tick();
   debugBtn.tick();
}

void final_countdown(u16 time_var){ //число секунд, которое надо отобразить на 4 битовом 7сегм
   u8 mins_var;
   u8 secs_var;
   static bool out_of_mins;
    mins_var = time_var/60;
    secs_var = time_var%60;
    if(mins_var > 0) out_of_mins = false;
    if(mins_var > 0 && !out_of_mins) display.showNumberDec(mins_var, false, 2,0);
    else if(!out_of_mins){
      display.clear(); //если минуты закончилисмть то надо убрать символ минут с экрана
      out_of_mins = true;
    }
    if(!(secs_var/10) && mins_var > 0){
      display.showNumberDec(0, false, 1,2); //рисуем 0 чтобы не было пустого места при отбражении
      display.showNumberDec(secs_var, false, 1,3);
    }
    else display.showNumberDec(secs_var, false, 2,2);
  }


void led_strip_display(u16 led_val, u32 led_color){ //функция выводит полоску длиной led_val и цветом led_color если 0,0 то очищает ленту   
    strip_1.clear();
    strip_2.clear();
    strip_3.clear();
    strip_4.clear();
    
  if(led_val != 0){
  for (u8 i = 0; i < led_val; i++ ) {    
    strip_1.setPixelColor(i, led_color);            
    strip_2.setPixelColor(i, led_color);    
    strip_3.setPixelColor(i, led_color);     
    strip_4.setPixelColor(i, led_color);     
    }    
  }
  strip_1.show(); 
  strip_2.show(); 
  strip_3.show(); 
  strip_4.show(); 
}
void disp_1bit_7seg(u8 val){    //функция которая отвечает за однобитный семисегмент
  if(val == 0){
    for(u8 i = 0; i < 8; i++){
      digitalWrite(seg_1bit[i] , ONEBIT_LOW);
    }
  }

  if(val == 1){
    digitalWrite(seg_1bit[1] , ONEBIT_HIGH);
    digitalWrite(seg_1bit[2] , ONEBIT_HIGH);  

    
  }

  if(val == 2){
    digitalWrite(seg_1bit_pin_A , ONEBIT_HIGH); //ABGED
    digitalWrite(seg_1bit_pin_B , ONEBIT_HIGH);
    digitalWrite(seg_1bit_pin_G , ONEBIT_HIGH);
    digitalWrite(seg_1bit_pin_E , ONEBIT_HIGH);
    digitalWrite(seg_1bit_pin_D , ONEBIT_HIGH);
  }

  if(val == 3){
    digitalWrite(seg_1bit_pin_A , ONEBIT_HIGH);
    digitalWrite(seg_1bit_pin_B , ONEBIT_HIGH);
    digitalWrite(seg_1bit_pin_G , ONEBIT_HIGH);
    digitalWrite(seg_1bit_pin_C , ONEBIT_HIGH);
    digitalWrite(seg_1bit_pin_D , ONEBIT_HIGH);
  }

  if(val == 4){
    digitalWrite(seg_1bit_pin_F , ONEBIT_HIGH);
    digitalWrite(seg_1bit_pin_B , ONEBIT_HIGH);
    digitalWrite(seg_1bit_pin_G , ONEBIT_HIGH);
    digitalWrite(seg_1bit_pin_C , ONEBIT_HIGH);
  }

  if(val == 5){
    digitalWrite(seg_1bit_pin_A , ONEBIT_HIGH);
    digitalWrite(seg_1bit_pin_F , ONEBIT_HIGH);
    digitalWrite(seg_1bit_pin_G , ONEBIT_HIGH);
    digitalWrite(seg_1bit_pin_C , ONEBIT_HIGH);
    digitalWrite(seg_1bit_pin_D , ONEBIT_HIGH);
    //afgcd
  }
}
//if(val == 8){
//  for(u8 i = 0; i < 8; i++){
//    digitalWrite(seg_1bit[i] , ONEBIT_HIGH);
//  } 
//}


void short_tone(){   
  tone(SOUND_PIN, TONE_FREQ, SHORT_TONE_DUR);
  #ifdef DEBUG
  Serial.println("short_tone");
  #endif

}

void short_short_tone(){
  tone(SOUND_PIN, TONE_FREQ, SHORT_SHORT_TONE_DUR);
  #ifdef DEBUG
  Serial.println("short_short_tone");
  #endif
}

void long_tone(){   
  tone(SOUND_PIN, TONE_FREQ, LONG_TONE_DUR);
  #ifdef DEBUG
  Serial.println("long_tone");
  #endif
}


void display_btn_strip(u8 btn_number, u8 height=LED_STRIP_ROWS){
static u32 color;
  if ((btn_number%5) == 0) color = 0xff0000; //мб прописать формулу в ИФе
      else if (btn_number%5 == 1) color = 0xffff00;
        else if (btn_number%5 == 2) color = 0x00ff00;
          else if (btn_number%5 == 3) color = 0x00ffff;
            else if (btn_number%5 == 4) color = 0x0000ff;
              else color = 0xffffff;
    if ( height == 0){
        strip_1.setPixelColor(2*btn_number, 0x000000);
        strip_1.setPixelColor(2*btn_number + 1, 0x000000);
        strip_2.setPixelColor(2*btn_number, 0x000000);
        strip_2.setPixelColor(2*btn_number + 1, 0x000000);
        strip_3.setPixelColor(2*btn_number, 0x000000);
        strip_3.setPixelColor(2*btn_number + 1, 0x000000);
        strip_4.setPixelColor(2*btn_number, 0x000000);
        strip_4.setPixelColor(2*btn_number + 1, 0x000000);
    }          
    if ( height >= 1){
    strip_1.setPixelColor(2*btn_number, color);
    strip_1.setPixelColor(2*btn_number + 1, color);
      if ( height >= 2){
      strip_2.setPixelColor(2*btn_number, color);
      strip_2.setPixelColor(2*btn_number + 1, color);
        if ( height >= 3){
        strip_3.setPixelColor(2*btn_number, color);
        strip_3.setPixelColor(2*btn_number + 1, color);
          if ( height >= 4){
          strip_4.setPixelColor(2*btn_number, color);
          strip_4.setPixelColor(2*btn_number + 1, color);
        //else ; надо ли бобавлять исключения для 0 высоты чтобы очистить столбец или сделать это по другому, но зачем если есть прекрасный led_strip_display(0, 0);
          }
        }
      } 
    }
}

//????
//u8 AllowQueue mb flag
//u8 StopQueue
//u8 PetrifyQueue +
//u8 ReadQueue ?? что оно делает

void printQueueStats() {
  
  Serial.println("Items in queue now:      " + String(ButtonsQueue.item_count()));
  Serial.println("Queue actual max items:  " + String(ButtonsQueue.maxQueueSize()));
  Serial.println("Queue empty:  " + String(ButtonsQueue.isEmpty()));
  Serial.println("Queue full:  " + String(ButtonsQueue.isFull()));
//  for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
//    Serial.print( ButtonsQueue.getHead());
//    ButtonsQueue.dequeue();
//  }
//  Serial.println();
//    PetrifyQueue();
}

void PetrifyQueue(){
  for(u8 i = 0; i < BUTTONS_QUANTITY; i++){

    ButtonsQueue.dequeue();
    btn_buffer[i] = 1;
    buttons_state[i] = 1;
    //очистка ламп игроков
    static_lamp(i, !false);
  }

  #ifdef DEBUG
  Serial.println( "Q petrified");
  #endif
}

void ReadQueueToStatic(){   //debug
    for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
    if((buttons_state[i] != btn_buffer[i]) && btn_buffer[i] == 1){
      //занести в буфер и в очередь
      btn_buffer[i] = 0;
      ButtonsQueue.enqueue(i + 1);
      led_strip_display(0,0);
      static_btn_strip(i, true);
      static_lamp(i, !true);
    }
  }
}

void ReadQueue(){   //debug
    for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
    if((buttons_state[i] != btn_buffer[i]) && btn_buffer[i] == 1){
      //занести в буфер и в очередь
      btn_buffer[i] = 0;
      ButtonsQueue.enqueue(i + 1);
    }
  }
}

  
  // функция очищает все лампы игроков
void clear_lamps(){ 
  for (u8 i = 0; i < BUTTONS_QUANTITY; ++i)
  {
    static_lamp(i, !false);

  }
}

void DebugFunction(){
    printQueueStats();
    Serial.println("btns: ");
    for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
      Serial.print(buttons_state[i]);
    }
    Serial.println();
    Serial.println("blink_buffer: ");
    for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
      Serial.print(blink_buffer[i]);
    }
    Serial.println();
}

//функция которая принимает true/false чтоб начать 
//минание, потом принимает номер кнопки которойнадо начать мигать

void blink_btn_strip(u8 btn_number, bool state){
  if(state){
    //enable blinking      
    blink_buffer[btn_number] = 1;    

  }
  else{
    //disable blinking
    blink_buffer[btn_number] = 0;
    static_btn_strip(btn_number, false); 
    static_lamp(btn_number, true);   
  }
}

//same for static burning
void static_btn_strip(u8 btn_number, bool state){
  if(state){
    //enable burning
    display_btn_strip(btn_number); //height 4
  }

  else{
    //disable blinking
    display_btn_strip(btn_number, 0); //height 0
  }
}


// void blink_lamp(u8 btn_number, bool state=false){
//   if(state){
//     //enable blinking      for (u8 i = 0; i < BUTTONS_QUANTITY; ++i)
//     blink_buffer[btn_number] = 1;    

//   }
//   else{
//     //disable blinking
//     blink_buffer[btn_number] = 0;
//     static_btn_strip(btn_number, false);    
//   }
// }



void static_lamp(u8 btn_number, bool state){ //bool vale inverted for sync
  if(!state){
  //enable burning
    digitalWrite(led_pins[btn_number], 1); 
  }

  else{
    //disable blinking
    digitalWrite(led_pins[btn_number], 0); 
  }
}

void led_strip_show(){
    strip_1.show(); 
    strip_2.show(); 
    strip_3.show();
    strip_4.show();
}


// ReadQueueToBlink();
// void ReadQueueToBlink_WS(){
//   for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
//     if((buttons_state[i] != btn_buffer[i]) && btn_buffer[i] == 1){
//       //занести в буфер и в очередь
//       btn_buffer[i] = 0;
//       ButtonsQueue.enqueue(i + 1);
//       WS_buffer[ButtonsQueue.getHead() - 1] = 2;

//       // led_strip_display(0,0);

//       // blink_btn_strip(i, true);
//       // static_lamp(i, !true);
//     }
//   }
// }