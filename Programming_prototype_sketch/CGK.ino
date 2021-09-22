//function for game mode 0 - ЧТО ГДЕ КОГДА CGK
void CGK_function(){ //ЧГК -0
    //states of game mode
    static enum {
        CGK_init,
        start_CGK,
        CGK_50,
        CGK_10,
        CGK_5,
        end_CGK,
        null_CGK,
    } CGK_states;
     
    if (!CGK_init_flag) CGK_state = CGK_init;

    //reset state anyway when reset button is pressed
    if (resetBtn.isSingle()){
        CGK_state = end_CGK;  
    }
        
    switch(CGK_state){
        case(CGK_init):
            disp_1bit_7seg(1);  //вывод 1
            #ifdef DEBUG
            Serial.println("CGK");
            #endif
            CGK_init_flag = true; //это значит что инициализация проведена
            
            CGK_state = null_CGK;
            break;

        case null_CGK:
            //wait till game mode cmmence
            if (selectBtn.isSingle()) {
              CGK_state = start_CGK; //ожидание старта режима
              led_strip_display(NUM_LEDS, 0x00ff00);// зажечь зеленым дисплей
              led_strip_show();
            }
            break;

        case start_CGK:
            selectBtn.isSingle();
            short_tone();
            final_countdown(CGK_main_time);
            THE_FINAL_COUNTDOWN = CGK_main_time - 1;
            final_timer = millis();
            CGK_state = CGK_50;
            break;
        
        case(CGK_50):
            selectBtn.isSingle();
            if(millis() - final_timer >= 1000){
                final_timer = millis(); 
                final_countdown(THE_FINAL_COUNTDOWN);
                led_strip_display(2*THE_FINAL_COUNTDOWN/strip_mp, 0x00ff00);//вывести зеленые СД 2*THE_FINAL_COUNTDOWN/strip_mp
                THE_FINAL_COUNTDOWN--;
                if(THE_FINAL_COUNTDOWN < CGK_sub_time){
                    short_tone();
                    CGK_state = CGK_10;
                } 
            }
            break;

        case(CGK_10):
            selectBtn.isSingle();
            if(millis() - final_timer >= 1000){
                final_timer = millis(); 
                final_countdown(THE_FINAL_COUNTDOWN);
                led_strip_display(2*THE_FINAL_COUNTDOWN/strip_mp, 0xffff00); //тож самое токо СД желтые
                THE_FINAL_COUNTDOWN--;
                if(THE_FINAL_COUNTDOWN < CGK_sub_sub_time){
                    short_tone();
                    CGK_state = CGK_5;
                } 
            }
            break;

        case(CGK_5):
            selectBtn.isSingle();
            if(millis() - final_timer >= 1000){
                final_timer = millis(); 
                final_countdown(THE_FINAL_COUNTDOWN);
                led_strip_display(2*THE_FINAL_COUNTDOWN/strip_mp, 0x0000ff); //тож самое токо СД red
                THE_FINAL_COUNTDOWN--;
                short_tone();
                if(THE_FINAL_COUNTDOWN == 255){
                    long_tone();
                    CGK_state = end_CGK;
                }
            }

            break;

        case(end_CGK):
            CGK_state = null_CGK;
            display.clear();
            led_strip_display(0, 0);//clear LED strip
            break;

        default:
            CGK_state = CGK_init;
            break;
    }
}
