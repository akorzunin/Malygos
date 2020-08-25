

void SVOYA_GAME_function(){ //ЧГК -0
if (!SWOYA_GAME_init) {
  Serial.println("SVOYA_GAME");
  digitalWrite(seg_1bit_pin_F , 1);
  digitalWrite(seg_1bit_pin_B , 1);
  digitalWrite(seg_1bit_pin_G , 1);
  digitalWrite(seg_1bit_pin_C , 1);
  SWOYA_GAME_init = true;
}
}
