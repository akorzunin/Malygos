

void BRAIN_RING_function(){ //ЧГК -0
  static u8 BR_current_answer_time;
  static u8 BR_answer_time[] = {20, 15}; //возможные варианты времени ответа
  static bool BR_false_start_flag = true;
  // static u8 THE_FINAL_COUNTDOWN 
  static enum {
    BR_init,
    BR_null,
    BR_timer_50,
    BR_timer_10,
    BR_timer_5,
    BR_answer,
    BR_answer_20_15,
    BR_answer_5,
    BR_endgame,
    BR_false_start,
  } BR_states;

  if (!BR_init_flag) BR_state = BR_init;
  if (resetBtn.isSingle()){
    BR_state = BR_endgame;
    #ifdef DEBUG
    Serial.println("BR_endgame");
    #endif
    // ButtonsQueue.enqueue(2); //debug
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
      
      BR_state = BR_null;
      #ifdef DEBUG
      Serial.println("BR_null");
      #endif
      break;
  
  case BR_null:
        //выбор режима фальстарта
        led_strip_display(0,0); //очистить ленту
        if (modeBtn.isDouble()) BR_false_start_flag = !BR_false_start_flag;
        if (BR_false_start_flag) digitalWrite(seg_1bit_pin_DP , ONEBIT_HIGH);
        else digitalWrite(seg_1bit_pin_DP , ONEBIT_LOW);
        //выбор времени на ответ
        if (resetBtn.isDouble()){ //modeBtn.isTriple()
          BR_current_answer_time++;
          if (BR_current_answer_time > 1) BR_current_answer_time = 0; // 1 это последний элемент массива с вариантами времени на выбор ответа
          display.showNumberDec(BR_answer_time[BR_current_answer_time], false, 2,2);
        }
        if(BR_false_start_flag){ //если фальстарт включен то тут его надо отслеживать
          //если кнопка игрока нажата, то это фальстарт получается
          ReadQueueToStatic();  //отследить нажание кнопки и обработать
          if(!ButtonsQueue.isEmpty()){ //если очередь НЕ пуста то перейти в БР ответ
            THE_FINAL_COUNTDOWN = BR_answer_time[BR_current_answer_time]; //set time to answer
            BR_state = BR_answer_20_15;
            short_tone();
          }
        }
        else {
        // ReadQueueToStatic();  //отследить нажание кнопки и обработать
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
      ReadQueueToStatic();  //отследить нажание кнопки и обработать
      if(!ButtonsQueue.isEmpty()){ //если очередь НЕ пуста то перейти в БР ответ
          BR_state = BR_answer;
          short_tone();
      }      
      if (millis() - final_timer >= 1000){
        final_timer = millis(); 
        final_countdown(THE_FINAL_COUNTDOWN);
        led_strip_display(2*THE_FINAL_COUNTDOWN/strip_mp, 0x00ff00);
        THE_FINAL_COUNTDOWN--;
        
        if (THE_FINAL_COUNTDOWN < BR_sub_time_10) {
          BR_state = BR_timer_10; //TODO прописать дефайны для 50 55 60 (10 5 0)
          #ifdef DEBUG
          Serial.println("BR_timer_55");
          #endif
          short_tone();
        }
      }

      break;
  
  case BR_timer_10:
      ReadQueueToStatic();  //отследить нажание кнопки и обработать
      if(!ButtonsQueue.isEmpty()){ //если очередь НЕ пуста то перейти в БР ответ
          BR_state = BR_answer;
          short_tone();
      }      
      if (millis() - final_timer >= 1000){
        final_timer = millis(); 
        final_countdown(THE_FINAL_COUNTDOWN);
        led_strip_display(2*THE_FINAL_COUNTDOWN/strip_mp, 0xffff00);
        THE_FINAL_COUNTDOWN--;
        
        if (THE_FINAL_COUNTDOWN < BR_sub_time_5) {
          BR_state = BR_timer_5; //TODO прописать дефайны для 50 55 60 (10 5 0)
          #ifdef DEBUG
          Serial.println("BR_timer_60");
          #endif
        }
      }

      break;
  
  case BR_timer_5:
      ReadQueueToStatic();    //отследить нажание кнопки и обработать
      if(!ButtonsQueue.isEmpty()){ //если очередь НЕ пуста то перейти в БР ответ
          BR_state = BR_answer;
          short_tone();
      }   
      if (millis() - final_timer >= 1000){
          final_timer = millis(); 
          final_countdown(THE_FINAL_COUNTDOWN);
          led_strip_display(2*THE_FINAL_COUNTDOWN/strip_mp, 0x0000ff);
          THE_FINAL_COUNTDOWN--;
          short_tone(); //писк каждую секунду в последние 5 с      
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
      led_strip_display(0, 0); //очистить СД ленту

      BR_state = BR_init;
      #ifdef DEBUG
      Serial.println("BR_init");
      #endif 
      break;
   
  case BR_answer:
      // digitalWrite(ButtonsQueue.dequeue(), 1);
      #ifdef DEBUG
      Serial.println("BR_answer");
      #endif
      if(selectBtn.isSingle()) {
        // перейти в режим отсчета 20\15с
        BR_state = BR_answer_20_15;
        THE_FINAL_COUNTDOWN = BR_answer_time[BR_current_answer_time]; //set time to answer

      }
      
      break;
  
  case BR_answer_20_15:
        if (millis() - final_timer >= 1000){
          final_timer = millis(); 
          final_countdown(THE_FINAL_COUNTDOWN);
          led_strip_display(2*THE_FINAL_COUNTDOWN/strip_mp, 0xff00ff);
          THE_FINAL_COUNTDOWN--;
          // short_tone(); //писк каждую секунду в последние 5 с      
          if (THE_FINAL_COUNTDOWN <= BR_sub_time_5) {
            BR_state = BR_endgame; //TODO прописать дефайны для 50 55 60 (10 5 0) + что-то слишком много копипасты кода надо это вынести в отдельную функцию мб или токо -- фт = миллис вынести
            #ifdef DEBUG
            Serial.println("BR_endgame");
            #endif         
          }
        }
        if(selectBtn.isSingle()) THE_FINAL_COUNTDOWN = BR_answer_time[BR_current_answer_time];

      break; 

  case BR_answer_5:
        if (millis() - final_timer >= 1000){
          final_timer = millis(); 
          final_countdown(THE_FINAL_COUNTDOWN);
          led_strip_display(2*THE_FINAL_COUNTDOWN/strip_mp, 0x0000ff);
          THE_FINAL_COUNTDOWN--;
          short_tone(); //писк каждую секунду в последние 5 с      
          if (THE_FINAL_COUNTDOWN <= 0) {
            BR_state = BR_endgame; //TODO прописать дефайны для 50 55 60 (10 5 0) + что-то слишком много копипасты кода надо это вынести в отдельную функцию мб или токо -- фт = миллис вынести
            #ifdef DEBUG
            Serial.println("BR_endgame");
            #endif         
        }
        }
        if(selectBtn.isSingle()) THE_FINAL_COUNTDOWN = BR_answer_time[BR_current_answer_time];      

      break;  
  default:

  break;
  
  }

}
