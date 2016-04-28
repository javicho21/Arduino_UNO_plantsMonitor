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

  /* exemples of how data are send to ESP8266
  PlantsMonitor,DHT1,Humidity,%,POSIX,27.30,M,/n
  PlantsMonitor,DHT1,Temperature,F,POSIX,90.68,M,/n
  PlantsMonitor,UVsensor,UV,mw/cm^2,POSIX,-6.79,M,/n
  PlantsMonitor,SoilMoistureSensor,SoilMoisture,H,POSIX,534,M,/n
  PlantsMonitor,SoilMoistureSensor,SoilMoisture,state,POSIX,HUMID,E,/n
  */


}
