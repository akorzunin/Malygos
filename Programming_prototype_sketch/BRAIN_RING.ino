

void BRAIN_RING_function(){ //ЧГК -0
 if( !BRAIN_RING_init){
  Serial.println("BRAIN_RING"); 
  //abged
  digitalWrite(seg_1bit_pin_A , 1);
  digitalWrite(seg_1bit_pin_B , 1);
  digitalWrite(seg_1bit_pin_G , 1);
  digitalWrite(seg_1bit_pin_E , 1);
  digitalWrite(seg_1bit_pin_D , 1);
  BRAIN_RING_init = true;
 }
}
