

void buttonTick(){
  interrupt_state = 1;
    for(u8 i = 0; i < (BUTTONS_QUANTITY); i++){
      buttons_state[i] = digitalRead(button_pins[i]); //опрос через обычные функции пока что button_pins[current_button_pin]                
    } 
}

void menu_buttons_tick(){
   modeBtn.tick(); 
   selectBtn.tick();
   resetBtn.tick();
}

void final_countdown(u16 time_var){ //число секунд, которое надо отобразить
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


void led_strip_display(u16 led_val, u32 led_color){ //функция выводит полоску длиной led_val и цветом led_color если 0 то надо очисттить ленту   
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
//  здесь должна быть функция которая отвечает за однобитный семисегмент

void clean_7seg_1bit(){ //очистить однобитовый семесегмент который подключен без контроллера
  digitalWrite(seg_1bit_pin_A , 0);
  digitalWrite(seg_1bit_pin_B , 0);
  digitalWrite(seg_1bit_pin_C , 0);
  digitalWrite(seg_1bit_pin_G , 0);
  digitalWrite(seg_1bit_pin_E , 0);
  digitalWrite(seg_1bit_pin_D , 0);
  digitalWrite(seg_1bit_pin_F , 0);
  digitalWrite(seg_1bit_pin_DP , 0);
}
