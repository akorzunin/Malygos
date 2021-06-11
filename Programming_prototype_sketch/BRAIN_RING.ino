

void BRAIN_RING_function(){ //ЧГК -0
  static u8 BR_current_answer_time;
  static u8 BR_answer_time[] = {15, 20}; //возможные варианты времени ответа
  static bool BR_false_start_flag;
  // static u8 THE_FINAL_COUNTDOWN 
  static enum {
    BR_init,
    BR_null,
    BR_timer_50,
    BR_timer_55,
    BR_timer_60,
    BR_answer,
    BR_endgame,
    BR_false_start,
  } BR_states;

  if (!BR_init_flag) BR_state = BR_init;
  if (resetBtn.isSingle()){
    BR_state = BR_endgame;
    #ifdef DEBUG
    Serial.println("BR_endgame");
    #endif
    ButtonsQueue.enqueue(2); //debug
  }
//  if(!ButtonsQueue.isEmpty() && ((BR_state == BR_timer_50) || (BR_state == BR_timer_55) || (BR_state == BR_timer_60))) {
    if(!ButtonsQueue.isEmpty() && ((BR_state == BR_timer_50) )) {
    BR_state = BR_answer; //если очередь не пуста, то  надо дать человеку ответить
    #ifdef DEBUG
    Serial.println("BR_answer");
    #endif  
  }
  switch (BR_state) {
  case BR_init:
      #ifdef DEBUG
      Serial.println("BRAIN_RING"); 
      #endif
      led_strip_display(0,0); //очистить ленту
      disp_1bit_7seg(2);
      BR_init_flag = true; //если перещлт на этот режим с другой страницы то флаг обнулится, те все что до етого написано будет выполнено при смене режима
      display.showNumberDec(BR_answer_time[BR_current_answer_time], false, 2,2);
      THE_FINAL_COUNTDOWN = BR_main_time; // !!!одна минута на основной цикл если никто не нажмет на кнопку
      PetrifyQueue();
      for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
      buttons_state[i] = 1;  
      leds_state[i] = 0;            
      }
      
      BR_state = BR_null;
      #ifdef DEBUG
      Serial.println("BR_null");
      #endif
      break;
  
  case BR_null:
        //выбор режима фальстарта
        led_strip_display(0,0); //очистить ленту
        if (modeBtn.isDouble()) BR_false_start_flag = !BR_false_start_flag;
        if (BR_false_start_flag == true) digitalWrite(seg_1bit_pin_DP , 1);
        else digitalWrite(seg_1bit_pin_DP , 0);
        //выбор времени на ответ
        if (resetBtn.isSingle()){ //modeBtn.isTriple()
          BR_current_answer_time++;
          if (BR_current_answer_time > 1) BR_current_answer_time = 0; // 1 это последний элемент массива с вариантами времени на выбор ответа
          display.showNumberDec(BR_answer_time[BR_current_answer_time], false, 2,2);
        }
      
        //запуск режима
        if (selectBtn.isSingle()) {
          BR_state = BR_timer_50;
          #ifdef DEBUG
          Serial.println("BR_timer_50");
          #endif
        }
      
        break;
  
  case BR_timer_50:
      ReadQueue();  //отследить нажание кнопки и обработать
      if (millis() - final_timer >= 1000){
        final_timer = millis(); 
        final_countdown(THE_FINAL_COUNTDOWN);
        THE_FINAL_COUNTDOWN--;
        
        if (THE_FINAL_COUNTDOWN < BR_sub_time_10) {
          BR_state = BR_timer_55; //TODO прописать дефайны для 50 55 60 (10 5 0)
          #ifdef DEBUG
          Serial.println("BR_timer_55");
          #endif
          short_tone();
          #ifdef DEBUG
          Serial.println("short_tone");
          #endif    
        }
      }
    //если таймер вышел  BR_state = BR_timer_55;
      break; 
  
  case BR_timer_55:
      ReadQueue();  //отследить нажание кнопки и обработать
      if (millis() - final_timer >= 1000){
        final_timer = millis(); 
        final_countdown(THE_FINAL_COUNTDOWN);
        THE_FINAL_COUNTDOWN--;
        
        if (THE_FINAL_COUNTDOWN < BR_sub_time_5) {
          BR_state = BR_timer_60; //TODO прописать дефайны для 50 55 60 (10 5 0)
          #ifdef DEBUG
          Serial.println("BR_timer_60");
          #endif
        }
      }

  break;
  
  case BR_timer_60:
      ReadQueue();    //отследить нажание кнопки и обработать
      if (millis() - final_timer >= 1000){
          final_timer = millis(); 
          final_countdown(THE_FINAL_COUNTDOWN);
          THE_FINAL_COUNTDOWN--;
          short_tone();
          #ifdef DEBUG
          Serial.println("short_tone");
          #endif
          
          if (THE_FINAL_COUNTDOWN <= 0) {
            BR_state = BR_endgame; //TODO прописать дефайны для 50 55 60 (10 5 0) + что-то слишком много копипасты кода надо это вынести в отдельную функцию мб или токо -- фт = миллис вынести
            #ifdef DEBUG
            Serial.println("BR_endgame");
            #endif         
          }
        }
      break;
  
  case BR_endgame:
      long_tone();
      display.clear();
      Serial.println("long_tone");
      //очистить ленту еще надо
      BR_state = BR_null;
      #ifdef DEBUG
      Serial.println("BR_null");
      #endif 
      break;
   
  case BR_answer:
      digitalWrite(ButtonsQueue.dequeue(), 1);
      if(selectBtn.isSingle()) {
        if(THE_FINAL_COUNTDOWN <= 0) {
          BR_state = BR_timer_60; //TODO дописать для возврата в другие состояния при другом занчении таймера
            #ifdef DEBUG
            Serial.println("BR_timer_60");
            #endif 
        }
        else {BR_state = BR_endgame;
              #ifdef DEBUG
              Serial.println("BR_endgame");
              #endif 
        }
      }
      
      break;
  
  case BR_false_start:

      break; 
  
  default:

  break;
  }
}
