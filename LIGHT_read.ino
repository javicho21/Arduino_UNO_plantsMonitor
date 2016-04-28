/*
Hardware connections:

3V3 to 3.3V
GND to GND

(WARNING: do not connect 3V3 to 5V
or the sensor will be damaged!)

You will also need to connect the I2C pins (SCL and SDA) to your Arduino.
The pins are different on different Arduinos:

                    SDA    SCL
Any Arduino         "SDA"  "SCL"
Uno, Redboard, Pro  A4     A5
Mega2560, Due       20     21
Leonardo            2      3

You do not need to connect the INT (interrupt) pin
for basic operation.

Operation:
*/

void LIGHT_read(){
  // Wait between measurements before retrieving the result
  // (You can also configure the sensor to issue an interrupt
  // when measurements are complete)
  
  // This sketch uses the TSL2561's built-in integration timer.
  // You can also perform your own manual integration timing
  // by setting "time" to 3 (manual) in setTiming(),
  // then performing a manualStart() and a manualStop() as in the below
  // commented statements:
  
  // ms = 1000;
  // light.manualStart();
  delay(ms);
  // light.manualStop();
  
  // Once integration is complete, we'll retrieve the data.
  
  // There are two light sensors on the device, one for visible light
  // and one for infrared. Both sensors are needed for lux calculations.
  
  // Retrieve the data from the device:

  unsigned int data0, data1;
  
  if (light.getData(data0,data1))
  {
    // getData() returned true, communication was successful
    // To calculate lux, pass all your settings and readings
    // to the getLux() function.
    
    // The getLux() function will return 1 if the calculation
    // was successful, or 0 if one or both of the sensors was
    // saturated (too much light). If this happens, you can
    // reduce the integration time and/or gain.
    // For more information see the hookup guide at:https://learn.sparkfun.com/tutorials/tsl2561-luminosity-sensor-hookup-guide?_ga=1.29122940.1562665140.1449065444
    double lux;    // Resulting lux value
    boolean good;  // True if neither sensor is saturated
    
    // Perform lux calculation:

    good = light.getLux(gain,ms,data0,data1,lux);
    
    // Print out the results:
    //Serial.print(" lux: ");
    //Serial.print(lux);

    sendPayload(deviceName,"LIGHTsensor","Light","lux",readTime,String(lux),"M");

    if (good) Serial.println(" (good)"); else Serial.println(" (BAD)");
  }
  else
  {
    // getData() returned false because of an I2C error, inform the user.

    byte error = light.getError();
    printError(error);
  }

}

void printError(byte error)
  // If there's an I2C error, this function will
  // print out an explanation.
{
  //Serial.print("I2C error: ");
  //Serial.print(error,DEC);
  //Serial.print(", ");

  /*
  switch(error)
  {
    case 0:
      Serial.println("success");
      break;
    case 1:
      Serial.println("data too long for transmit buffer");
      break;
    case 2:
      Serial.println("received NACK on address (disconnected?)");
      break;
    case 3:
      Serial.println("received NACK on data");
      break;
    case 4:
      Serial.println("other error");
      break;
    default:
      Serial.println("unknown error");
  }
  */
}

