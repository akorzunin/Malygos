//function for game mode 3 СВОЯ ИГРА SWOYA GAME
void SVOYA_GAME_function(){

	static bool SG_falsestart = true, erase_flag = false;
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
				THE_FINAL_COUNTDOWN = SG_MAIN_TIME;
		    	for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
		     		buttons_state[i] = 1;
				}
				SG_state = SG_main;
				short_tone();
			}

			if (SG_falsestart)
			{	
				//если фальстарт включен то тут его надо отслеживать
				//если кнопка игрока нажата, то это фальстарт получается
				//отследить нажание кнопки и обработать
				ReadQueueToBlink();
				if (!ButtonsQueue.isEmpty())
				{																  
					//если очередь НЕ пуста то перейти в БР ответ
					//set time to answer
					THE_FINAL_COUNTDOWN = SG_MAIN_TIME;							  
					SG_state = SG_answer;
					long_tone(); //falsestart
					erase_flag = true;
				}
			}
			if (!SG_falsestart)
			{ 
				ReadQueueToStatic(); //отследить нажание кнопки и обработать
				if (!ButtonsQueue.isEmpty())
				{										
					//если очередь НЕ пуста то перейти в БР ответ
					//set time to answer
					THE_FINAL_COUNTDOWN = SG_MAIN_TIME; 
					SG_state = SG_answer;
					short_tone(); //falsestart
				}
			}

			if (modeBtn.isDouble()) {
		    	SG_falsestart = !SG_falsestart;
		        digitalWrite(seg_1bit_pin_DP , ONEBIT_LOW ^ SG_falsestart);
			}
			// do the same but with hold action
			if (modeBtn.isHold()){
				SG_falsestart = !SG_falsestart;
				digitalWrite(seg_1bit_pin_DP, ONEBIT_LOW ^ SG_falsestart);
				delay(HOLD_TIMEOUT);
			}
			break;

		case SG_main:
			selectBtn.isSingle();
			if (millis() - final_timer >= 1000)
			{
				final_timer = millis();
		    	final_countdown(THE_FINAL_COUNTDOWN);
		        THE_FINAL_COUNTDOWN--;
				if(THE_FINAL_COUNTDOWN == 255){
					SG_state = SG_endgame;
					long_tone();
				}
			}
			if (erase_flag)
			{
				erase_flag = false;
				PetrifyQueue(); //fix
				//clear blink buffer
				for (u8 i = 0; i < BUTTONS_QUANTITY; i++)
				{
					blink_btn_strip(i, false);
				}
			}
			//handle player buttons
			if(ButtonsQueue.isEmpty()) ReadQueueToStatic();	
			if(!ButtonsQueue.isEmpty()){
				static_btn_strip(ButtonsQueue.getHead() - 1, true);
				ButtonsQueue.dequeue();
				short_tone();
				SG_state = SG_answer;
			}
			break;

		case SG_answer:
			if(selectBtn.isSingle()){
				PetrifyQueue(); //fix
				short_short_tone();
				//reset counter
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

		case SG_endgame:
			selectBtn.isSingle(); //clear input 
			display.clear();
			led_strip_display(0, 0);
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
