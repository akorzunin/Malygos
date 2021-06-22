

void SVOYA_GAME_function(){ 
static bool SG_falsestart=true;

static enum 
{
	SG_init,
	SG_null,
	SG_answer,
	SG_timer,
  	SG_main,
	SG_endgame,
} SG_states;

if(!SWOYA_GAME_init) SG_state = SG_init;
if(resetBtn.isSingle()){
	SG_state = SG_endgame;
}

switch (SG_state){
	case SG_init:
	led_strip_display(0,0);
	disp_1bit_7seg(4);
	SWOYA_GAME_init = true;
	PetrifyQueue();
    digitalWrite(seg_1bit_pin_DP , ONEBIT_LOW ^ SG_falsestart);


	SG_state = SG_null;
	break;

	case SG_null:
	if(selectBtn.isSingle()){
		//start timer
		final_timer = millis();
		//clear input
		selectBtn.isSingle();
		// if(SG_QUEUE_MODE)PetrifyQueue();
		THE_FINAL_COUNTDOWN = SG_MAIN_TIME;
    	for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
     		buttons_state[i] = 1;

		}
		SG_state = SG_main;
		short_tone();
	}
		// обработатьт состояниR включенного фальстарта
	if(!SG_falsestart){ //если нет ФС то можно нажимать когда угодно, до или после нажатия кнопки
		if(ButtonsQueue.isEmpty()) {
		ReadQueueToStatic(); 
		if(!ButtonsQueue.isEmpty()) {
			static_btn_strip(ButtonsQueue.getHead() - 1, true);
		}
		}
	}
    if (modeBtn.isDouble()) {
    	SG_falsestart = !SG_falsestart;
        digitalWrite(seg_1bit_pin_DP , ONEBIT_LOW ^ SG_falsestart);

	}
	break;

	case SG_main:

    if (millis() - final_timer >= 1000){
    	final_timer = millis();
    	final_countdown(THE_FINAL_COUNTDOWN);
        THE_FINAL_COUNTDOWN--;


		if(THE_FINAL_COUNTDOWN == 255){
			SG_state = SG_endgame;
		}
	}
	
	//обработка нажатия кнопки
	if(ButtonsQueue.isEmpty()) ReadQueueToStatic();	
	if(!ButtonsQueue.isEmpty()){
		static_btn_strip(ButtonsQueue.getHead() - 1, true);
		ButtonsQueue.dequeue();
		SG_state = SG_answer;
	}



	break;
	case SG_answer:
	if(selectBtn.isSingle()){
		//сбросить счетчик
		THE_FINAL_COUNTDOWN = SG_MAIN_TIME;
		display.clear();
		led_strip_display(0, 0);
		selectBtn.isSingle(); //clear input 
		for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
	  	blink_btn_strip(i, false);
	  	static_btn_strip(i, false);
	  	static_lamp(i, false);
	  	}
    	final_timer = millis();
		SG_state = SG_main;
	}

	break;
	// case :

	// break;
	// case :

	// break;
	// case :

	// break;
	case SG_endgame:
	long_tone();
	display.clear();
	led_strip_display(0, 0);
	selectBtn.isSingle(); //clear input 
	for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
  	blink_btn_strip(i, false);
  	static_btn_strip(i, false);
  	static_lamp(i, false);
  	}
  	PetrifyQueue();

	SG_state = SG_init;	
	break;

}
}
// if (!SWOYA_GAME_init) {  //инициализация режима
//   #ifdef DEBUG
//   Serial.println("SVOYA_GAME");
//   #endif
//   //вывод 4
//   disp_1bit_7seg(4);
//   SWOYA_GAME_init = true;
// }
// }
