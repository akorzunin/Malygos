void W_SHOOTER_function(){ 
static u8 WS_buffer[BUTTONS_QUANTITY] = {}; //array with states of each player 0 - noting 1 - static ligth 2 - blink
static bool WS_blink_flag;
static enum 
{
	WS_init,
	WS_null,
	WS_queue,
  	WS_main,
	WS_endgame,
} WS_states;

if(!W_SHOOTER_init) WS_state = WS_init;
if(resetBtn.isSingle()) {
	WS_state = WS_endgame;
}

switch (WS_state) {
	case WS_init:
	led_strip_display(0,0);
	disp_1bit_7seg(3);
	W_SHOOTER_init = true;
	PetrifyQueue();

	WS_state = WS_null;
	break;

	case WS_null:
	// if(selectBtn.isSingle()){
		WS_state = WS_main;
		short_tone();
		digitalWrite(seg_1bit_pin_DP , ONEBIT_HIGH); //отметить хоть как-то что режим начат
		PetrifyQueue();
		selectBtn.isSingle();
		#ifdef DEBUG
		Serial.println("WS_main");
		#endif
	// }
	break;

	case WS_main:
	// занесение в очередь
	if (ButtonsQueue.isEmpty()) {
    	//если очередь пуста то первая кнопка заностися с постоянным горением	
    	ReadQueue();
    	WS_buffer[ButtonsQueue.getHead() - 1] = 1;
    	
	}
	else {
        //опрос кнопок игроков
	  	for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
		    if((buttons_state[i] != btn_buffer[i]) && btn_buffer[i] == 1){
		      //занести в буфер и в очередь
		      btn_buffer[i] = 0;
		      ButtonsQueue.enqueue(i + 1);
		      WS_buffer[i] = 2;

		      // led_strip_display(0,0);

		      // blink_btn_strip(i, true);
		      // static_lamp(i, true);
		    }
  	    }
	}

	if(selectBtn.isSingle()){
		// dequeue one btn
		// очистить дисплей и отобразить там акуальные данные
		// горит на постоянку теперь другая кнопка
		// та кнопка которую выбросили не может быть еще раз занесена в очередь
		// если очередь пуста то надо выти в окно
		// blink_btn_strip(ButtonsQueue.getHead(), false);
		WS_buffer[ButtonsQueue.getHead() - 1] = 0;
        ButtonsQueue.dequeue();
        if(ButtonsQueue.isEmpty()) {
            WS_state = WS_endgame;
        }	
        else WS_buffer[ButtonsQueue.getHead() - 1] = 1; //поменять состяоние для кнопки которая стала последней в очереди
	}

    if (millis() - final_timer >= WS_REFRESH_TIME){
        final_timer = millis(); 
        for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
            if(WS_buffer[i] == 0){ //потушить столб на СД ленте и лампу игрока
                static_btn_strip(i, false);
                static_lamp(i, false);
                blink_btn_strip(i, false);//stop blinking

            }
            if(WS_buffer[i] == 1){ //просто горит столб на СД ленте и лампа игрока
                static_btn_strip(i, true);
                static_lamp(i, true);
                if(blink_buffer[i]){
                	blink_btn_strip(i, false);
                }
    
            }
            if(WS_buffer[i] == 2){ //мигает столб на СД ленте и лампа игрока
                // WS_blink_flag = !WS_blink_flag;
                // if(WS_blink_flag){
                //     static_btn_strip(i, true);
                //     static_lamp(i, true);
                // }
                // else{
                //     static_btn_strip(i, false);
                //     static_lamp(i, false);
                // }
                blink_btn_strip(i, true);
                // static_btn_strip(i, true);
                // static_lamp(i, true);
            }
        }




    }
	#ifdef DEBUG
	if (debugBtn.isSingle()){
		DebugFunction();
	    for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
	      Serial.print(WS_buffer[i]);
	    }
	    Serial.println();


	}
	#endif

	break;

	case WS_endgame:
	long_tone();
	display.clear();
	led_strip_display(0, 0);
	WS_state = WS_init;
	selectBtn.isSingle(); //clear input 
	digitalWrite(seg_1bit_pin_DP , ONEBIT_LOW);
  	for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
  	blink_btn_strip(i, false);
  	static_btn_strip(i, false);
  	static_lamp(i, false);
  	WS_buffer[i] = 0;
  	}
	PetrifyQueue();
	break;


}
}


// if (!W_SHOOTER_init){ //инициализация режима
//   #ifdef DEBUG
//   Serial.println("W_SHOOTER");
//   #endif
//   //вывод 3
//   disp_1bit_7seg(3);
  
//   W_SHOOTER_init = true; 
// }
// }
