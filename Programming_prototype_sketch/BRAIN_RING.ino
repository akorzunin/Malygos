

void BRAIN_RING_function(){ //ЧГК -0
 if( !BRAIN_RING_init){     //инициализация режима
  Serial.println("BRAIN_RING"); 
  //вывод 2
  disp_1bit_7seg(2);
  BRAIN_RING_init = true;
 }
}
