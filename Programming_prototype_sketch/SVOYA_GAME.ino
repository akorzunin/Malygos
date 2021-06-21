

void SVOYA_GAME_function(){ 


static enum 
{
	SG_init,
	SG_null,
	
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

	SG_state = SG_null;
	break;

	case SG_null:


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
