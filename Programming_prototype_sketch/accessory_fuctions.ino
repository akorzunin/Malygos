

void buttonTick(){ //функция прерыввания по опросу кнопок игроков
  interrupt_state = 1;
    for(u8 i = 0; i < (BUTTONS_QUANTITY); i++){
      buttons_state[i] = digitalRead(button_pins[i]);               
    } 
}

void menu_buttons_tick(){ //опрос кнопок меню
   modeBtn.tick(); 
   selectBtn.tick();
   resetBtn.tick();
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
//  }
  }


void led_strip_display(u16 led_val, u32 led_color){ //функция выводит полоску длиной led_val и цветом led_color если 0,0 то очищает ленту   
    strip_1.clear();
    strip_2.clear();
    strip_3.clear();
  if(led_val != 0){
  for (int i = 0; i < led_val; i++ ) {    
    strip_1.setPixelColor(i, led_color);            
    strip_2.setPixelColor(i, led_color);    
    strip_3.setPixelColor(i, led_color);     
    }    
  }
  strip_1.show(); 
  strip_2.show(); 
  strip_3.show(); 
}
void disp_1bit_7seg(u8 val){    //функция которая отвечает за однобитный семисегмент
if(val == 0){
  for(u8 i = 0; i < 8; i++){
    digitalWrite(seg_1bit[i] , 0);
  }
//  digitalWrite(seg_1bit_pin_A , 0); 0
//  digitalWrite(seg_1bit_pin_B , 0); 1
//  digitalWrite(seg_1bit_pin_C , 0); 2
//  digitalWrite(seg_1bit_pin_G , 0); 3 
//  digitalWrite(seg_1bit_pin_E , 0); 4
//  digitalWrite(seg_1bit_pin_D , 0); 5
//  digitalWrite(seg_1bit_pin_F , 0); 6
//  digitalWrite(seg_1bit_pin_DP , 0); 7
}

if(val == 1){
  digitalWrite(seg_1bit[1] , 1);
  digitalWrite(seg_1bit[2] , 1);  
}

if(val == 2){
  digitalWrite(seg_1bit_pin_A , 1);
  digitalWrite(seg_1bit_pin_B , 1);
  digitalWrite(seg_1bit_pin_G , 1);
  digitalWrite(seg_1bit_pin_E , 1);
  digitalWrite(seg_1bit_pin_D , 1);
}

if(val == 3){
  digitalWrite(seg_1bit_pin_A , 1);
  digitalWrite(seg_1bit_pin_B , 1);
  digitalWrite(seg_1bit_pin_G , 1);
  digitalWrite(seg_1bit_pin_C , 1);
  digitalWrite(seg_1bit_pin_D , 1);
}

if(val == 4){
  digitalWrite(seg_1bit_pin_F , 1);
  digitalWrite(seg_1bit_pin_B , 1);
  digitalWrite(seg_1bit_pin_G , 1);
  digitalWrite(seg_1bit_pin_C , 1);
}
}

void short_tone(){   
  tone(SOUND_PIN, TONE_FREQ, SHORT_TONE_DUR);
}

void long_tone(){   
  tone(SOUND_PIN, TONE_FREQ, LONG_TONE_DUR);
}

//TODO доработать либо обойтись двумя верхними функциями (short и long)
void rising_tone(){   
  tone(SOUND_PIN, TONE_FREQ, SHORT_TONE_DUR);
  tone(SOUND_PIN, 2*TONE_FREQ, SHORT_TONE_DUR);
  tone(SOUND_PIN, 3*TONE_FREQ, SHORT_TONE_DUR);
}

void falling_tone(){   
  tone(SOUND_PIN, 3*TONE_FREQ, SHORT_TONE_DUR);
  tone(SOUND_PIN, 2*TONE_FREQ, SHORT_TONE_DUR);
  tone(SOUND_PIN, TONE_FREQ, SHORT_TONE_DUR);
}






  
