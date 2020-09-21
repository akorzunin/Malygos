

void W_KILLER_function(){ 
if (!W_KILLER_init){ //инициализация режима
  #ifdef DEBUG
  Serial.println("W_KILLER");
  #endif
  //вывод 3
  disp_1bit_7seg(3);
  
  W_KILLER_init = true; 
}
}
