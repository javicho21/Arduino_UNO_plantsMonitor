void activate_relay_1(){  
  digitalWrite(RELE_1,HIGH);
  stateRelay1 = true ;
  relay1StartMillis = millis();
}

void activate_relay_2(){
  digitalWrite(RELE_2,HIGH);
}

void deactivate_relay_1(){
  digitalWrite(RELE_1,LOW);
}

void deactivate_relay_2(){
  digitalWrite(RELE_2,LOW);
}


void checkRelays(){
  if ((millis() - relay1StartMillis) >= (watterPumpONdelay*1000)){
    digitalWrite(RELE_1,LOW);
    stateRelay1 = false ;
  } 
}



