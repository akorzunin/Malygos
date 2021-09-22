//function for game mode 4 TEST MODE
void test_mode(){
	static enum 
	{
		TEST_INIT,
		TEST_NULL,
		TEST_MODE_1,
		TEST_MODE_2,

		// SOUND_TEST,
		// BUTTON_TEST,
		// LED_STRIP_TEST,
		// INTERRUPT_TEST,
		
	} test_;

	if (debugBtn.isSingle()) Serial.println("test_state"); //listing modes
	if(!test_mode_init_flag) test_state = TEST_INIT;

	switch(test_state)
	{
		case TEST_INIT:
			disp_1bit_7seg(5);
			led_strip_display(0,0);
			#ifdef DEBUG
            Serial.println("TEST_MODE");
			#endif
			test_mode_init_flag = true;
			test_state = TEST_NULL;

    	break;
		case TEST_NULL:
			if (selectBtn.isSingle()){
				test_state = TEST_MODE_1;
			}
			if (resetBtn.isSingle()){
				test_state = TEST_MODE_2;
			}

		break;
		case TEST_MODE_1:
			rainbowCycle(20);
			test_state = TEST_INIT;
		break;		
		case TEST_MODE_2:
			Fire(30,255,40);
			test_state = TEST_INIT;

		break;
			// case TEST_MODE_1:

			// break;
			// case TEST_MODE_1:

			// break;


	}
}



byte * Wheel(byte WheelPos) {
  static byte c[3];
 
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}

void setPixel(int Pixel, byte red, byte green, byte blue) {

   strip_1.setPixelColor(Pixel, strip_1.Color(red, green, blue));
   strip_2.setPixelColor(Pixel, strip_2.Color(red, green, blue));
   strip_3.setPixelColor(Pixel, strip_3.Color(red, green, blue));
   strip_4.setPixelColor(Pixel, strip_4.Color(red, green, blue));
}

void setPixel_n(int Pixel, byte red, byte green, byte blue, u8 strip_num)
{

	if (strip_num == 1)
		strip_1.setPixelColor(Pixel, strip_1.Color(red, green, blue));
	if (strip_num == 2)
		strip_2.setPixelColor(Pixel, strip_2.Color(red, green, blue));
	if (strip_num == 3)
		strip_3.setPixelColor(Pixel, strip_3.Color(red, green, blue));
	if (strip_num == 4)
		strip_4.setPixelColor(Pixel, strip_4.Color(red, green, blue));
}

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    // if(test_mode_timer.isReady()){
		for(i=0; i< NUM_LEDS; i++) {
		c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
		setPixel(i, *c, *(c+1), *(c+2));
		}
		strip_1.show();
		strip_2.show();
		strip_3.show();
		strip_4.show();
	menu_buttons_tick();
    delay(SpeedDelay);
	if (selectBtn.isSingle()) {
		break;
	}
	// }
  }
	// test_mode_timer.start();
}

void Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[NUM_LEDS][4];
  int cooldown;
	while(1){
		// if(test_mode_timer.isReady()){
			for (u8 n = 1; n < 5; n++)
			{
				/* code */
			
			
				// Step 1.  Cool down every cell a little
				for( int i = 0; i < NUM_LEDS; i++) {
					cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);

					if(cooldown>heat[i][n]) {
					heat[i][n]=0;
					} else {
					heat[i][n]=heat[i][n]-cooldown;
					}
				}

				// Step 2.  Heat from each cell drifts 'up' and diffuses a little
				for( int k= NUM_LEDS - 1; k >= 2; k--) {
					heat[k][n] = (heat[k - 1][n] + heat[k - 2][n] + heat[k - 2][n]) / 3;
				}

				// Step 3.  Randomly ignite new 'sparks' near the bottom
				if( random(255) < Sparking ) {
					int y = random(7);
					heat[y][n] = heat[y][n] + random(160,255);
					//heat[y] = random(160,255);
				}

				// Step 4.  Convert heat to LED colors
				for( int j = 0; j < NUM_LEDS; j++) {
					setPixelHeatColor(j, heat[j][n], n);
	
				}
			}
			strip_1.show();
			strip_2.show();
			strip_3.show();
			strip_4.show();
		menu_buttons_tick();
		delay(SpeedDelay);
		if (selectBtn.isSingle())
		{
			break;
		}
	}
}

void setPixelHeatColor (int Pixel, byte temperature, u8 strip_num) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
	  setPixel_n(Pixel, 255, 255, heatramp, strip_num);
  } else if( t192 > 0x40 ) {             // middle
	  setPixel_n(Pixel, 255, heatramp, 0, strip_num);
  } else {                               // coolest
	  setPixel_n(Pixel, heatramp, 0, 0, strip_num);
  }
}

