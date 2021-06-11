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
	if (myTimer.isReady()) Serial.println(test_state); //view current state
	if (debugBtn.isSingle()) test_state++; //listing modes
	if (resetBtn.isSingle()) test_state = TEST_INIT; //reset if sth goes wrong

	switch(test_state)
	{
		case TEST_INIT:
			disp_1bit_7seg(5);
      break;
		case SOUND_TEST:
      
		if(selectBtn.isSingle()) {
			// short_tone();
    
			long_tone();
			// tone(SOUND_PIN, TONE_FREQ, SHORT_TONE_DUR);

			
		}	

		if(selectBtn.isHold()) noTone(SOUND_PIN);
				
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
