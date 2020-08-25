

void W_KILLER_function(){ //ЧГК -0
if (!W_KILLER_init){
  Serial.println("W_KILLER");
  digitalWrite(seg_1bit_pin_A , 1);
  digitalWrite(seg_1bit_pin_B , 1);
  digitalWrite(seg_1bit_pin_G , 1);
  digitalWrite(seg_1bit_pin_C , 1);
  digitalWrite(seg_1bit_pin_D , 1);
  
  W_KILLER_init = true; 
}
}
