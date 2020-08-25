

void CGK_function(){ //ЧГК -0
  if(!CGK_init){
                //потом переписать инициализацию как отделюную функцию для всех режимов мб даже класс сделать
    digitalWrite(seg_1bit[1] , 1);
    digitalWrite(seg_1bit[2] , 1);   
    CGK_state = n0ll_CGK; //почему оно называется так странно TODO переименовать это 
    CGK_init = true; //это значит что инициализация проведена
  }  
  //if (myTimer.isReady()) Serial.println("CGK" + String(CGK_state));
if (resetBtn.isSingle()) CGK_state = end_CGK;  
if (modeBtn.isSingle()) Serial.println("CGK"); 
if (selectBtn.isDouble()) {
  CGK_state = start_CGK; //мб переписать потом под свич кейс
  tone(SOUND_PIN, 500, 100); //заменить потом на стандартизированные сигналы
  THE_FINAL_COUNTDOWN = CGK_main_time;
  CGK_state = CGK_50;
  final_timer = millis(); 
}

if(CGK_state == CGK_50 && (millis() - final_timer >= 1000)){
  final_timer = millis(); 
  final_countdown(THE_FINAL_COUNTDOWN);
  led_strip_display(2*THE_FINAL_COUNTDOWN/strip_mp, 0x00ff00);//вывести зеленые СД 2*THE_FINAL_COUNTDOWN/strip_mp
  THE_FINAL_COUNTDOWN--;
  if(THE_FINAL_COUNTDOWN <= CGK_sub_time){
    tone(SOUND_PIN, 500, 100);
    CGK_state = CGK_10;
  }
}

if((CGK_state == CGK_10) && (millis() - final_timer >= 1000)){
  final_timer = millis(); 
  final_countdown(THE_FINAL_COUNTDOWN);
  led_strip_display(2*THE_FINAL_COUNTDOWN/strip_mp, 0xffff00); //тож самое токо СД желтые
  THE_FINAL_COUNTDOWN--;
  if(THE_FINAL_COUNTDOWN == 0){
    tone(SOUND_PIN, 500, 1000);
    CGK_state = end_CGK;
  }
}


if (CGK_state == end_CGK) {
  CGK_state = n0ll_CGK;//ничего не делать в этом режме
  display.clear();
  led_strip_display(0, 0);//вызвать очистку СД ленты
}
}
