/* 
 The ML8511 UV Sensor outputs an analog signal in relation to the amount of UV light it detects.

 //https://learn.sparkfun.com/tutorials/ml8511-uv-sensor-hookup-guide?_ga=1.32857470.1562665140.1449065444
 
 Connect the following ML8511 breakout board to Arduino:
 3.3V = 3.3V
 OUT = A1
 GND = GND
 EN = 3.3V
 3.3V = A0
 
*/
void UV_read(){
  int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);
  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float outputVoltage = 3.3 / refLevel * uvLevel;
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level from 0 to 15
  sendPayload(deviceName,"UVsensor","UV","mw/cm^2",readTime,String(uvIntensity),"M");
  delay(100);
}


//Takes an average of readings on a given pin
//Returns the average
int averageAnalogRead(int pinToRead){
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 
  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;
  return(runningValue);  
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
