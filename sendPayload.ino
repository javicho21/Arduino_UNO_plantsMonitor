void sendPayload(String deviceName, String sensorName, String sensorType, String sensorUnit, String readTime, String reading,String messageType){
  stringPayload = deviceName;
  stringPayload += ",";

  stringPayload += sensorName;
  stringPayload += ",";

  stringPayload += sensorType;
  stringPayload += ",";
  

  stringPayload += sensorUnit;
  stringPayload += ",";

  stringPayload += readTime;
  stringPayload += ",";

  stringPayload += reading;
  stringPayload += ",";

  stringPayload += messageType;
  stringPayload += ",\n";

  for (int i=0 ; i < 100 ; i++){  //
    payload[i]= 0x00;
  }
  
  for (int i=0 ; i < stringPayload.length() ; i++){
    payload[i]= stringPayload.charAt(i);
  }

//delay(2000);
Serial.print(stringPayload);  //send payload as CSV to ESP8266

}
