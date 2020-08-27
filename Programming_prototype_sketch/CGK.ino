

void CGK_function(){ //ЧГК -0
  if(!CGK_init){  //инициализация режима
                //TODO потом переписать инициализацию как отделюную функцию для всех режимов мб даже класс сделать
    //вывод 1
    disp_1bit_7seg(1); 
    CGK_state = null_CGK; //почему оно называется так странно TODO переименовать это 
    CGK_init = true; //это значит что инициализация проведена
  }  
  //if (myTimer.isReady()) Serial.println("CGK" + String(CGK_state));
if (resetBtn.isSingle()) CGK_state = end_CGK;  
if (modeBtn.isSingle()) Serial.println("CGK"); 
if (selectBtn.isDouble()) {
  CGK_state = start_CGK; //мб переписать потом под свич кейс
  short_tone();
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
    short_tone();
//    tone(SOUND_PIN, 500, 100);
    CGK_state = CGK_10;
  }
}

if((CGK_state == CGK_10) && (millis() - final_timer >= 1000)){
  final_timer = millis(); 
  final_countdown(THE_FINAL_COUNTDOWN);
  led_strip_display(2*THE_FINAL_COUNTDOWN/strip_mp, 0xffff00); //тож самое токо СД желтые
  THE_FINAL_COUNTDOWN--;
  if(THE_FINAL_COUNTDOWN == 0){
    long_tone();
    CGK_state = end_CGK;
  }
}


if (CGK_state == end_CGK) {
  CGK_state = null_CGK;//ничего не делать в этом режме
  display.clear();
  led_strip_display(0, 0);//вызвать очистку СД ленты
}
}
