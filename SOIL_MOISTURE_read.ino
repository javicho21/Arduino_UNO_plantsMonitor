void SOIL_MOISTURE_read(){

/* Connection pins:
Arduino     Soil Moisture Sensor YL-69
  A2             Analog output
  5V               VCC
  GND              GND
*/

  int sample = analogRead(SoilPin); //take a sample
  String SoilMoistureResult ;
  
  if(sample >= 1000) {
    SoilMoistureResult = "DISCONECTED";
    //Serial.println("Sensor is not in the Soil or DISCONNECTED");
  }
  if(sample < 1000 && sample >= 600) { 
    SoilMoistureResult = "DRY";
    //Serial.println("Soil is DRY");

    if (!stateRelay1){
      activate_relay_1(); //power on watter pump
    }
  }
  if(sample < 600 && sample >= 370) {
    SoilMoistureResult = "HUMID";
    //Serial.println("Soil is HUMID"); 
  }
  if(sample < 370) {
    SoilMoistureResult = "SENSOR_in_WATER";
    //Serial.println("Sensor in WATER");
  }
  delay(50);

  sendPayload(deviceName,"SoilMoistureSensor","SoilMoisture","H",readTime,String(sample),"M");
  
  sendPayload(deviceName,"SoilMoistureSensor","SoilMoisture","H",readTime,SoilMoistureResult,"E");
  
  
}

