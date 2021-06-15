//
void test_mode(){
	static enum 
	{
		TEST_INIT,
		SOUND_TEST,
		BUTTON_TEST,
		LED_STRIP_TEST,
		INTERRUPT_TEST,
		
	} test_;




	//testing mode
	// if (myTimer.isReady()) Serial.println(test_state); //view current state
	if (debugBtn.isSingle()) Serial.println("test_state"); //listing modes
	// if (resetBtn.isSingle()) test_state = TEST_INIT; //reset if sth goes wrong

	switch(test_state)
	{
		case TEST_INIT:
			disp_1bit_7seg(5);
			if(selectBtn.isSingle()){
				for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
			
// buttons_state массив с состояниями кнопок
					Serial.print(btn_buffer[i]);	

				}	
				Serial.println("#");
			}

			//процедура заполнения очереди
			for(u8 i = 0; i < BUTTONS_QUANTITY; i++){
				if((buttons_state[i] != btn_buffer[i]) && btn_buffer[i] == 1){
					//занести в буфер и в очередь
					btn_buffer[i] = 0;
					ButtonsQueue.enqueue(i + 1);
					//for static
					// static_btn_strip(i, true);
					//for blinking
					blink_btn_strip(i, true);


				}
			}
			if(selectBtn.isDouble()) printQueueStats() ;
			if (resetBtn.isSingle()){

				//достать из очереди по одному
				//for static
				// static_btn_strip(ButtonsQueue.getHead() - 1, false);
				//for blink
				blink_btn_strip(ButtonsQueue.getHead() - 1, false);
				Serial.println("Removed:" + String(ButtonsQueue.dequeue()));
				printQueueStats();
			}
			if(resetBtn.isDouble()) PetrifyQueue();


      break;
		case SOUND_TEST:
      
		if(selectBtn.isSingle()) {
			// short_tone();
    
			long_tone();
			// tone(SOUND_PIN, TONE_FREQ, SHORT_TONE_DUR);

			
		}
				
		break;

		case BUTTON_TEST:

		break;

		case LED_STRIP_TEST:
		//paste code from site

		break;

		case INTERRUPT_TEST:

		break;
	}
}
