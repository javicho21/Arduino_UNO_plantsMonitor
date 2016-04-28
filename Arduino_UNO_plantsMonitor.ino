//this code monitor sensors and publish data on MQTT using ESP8266 customized firmware

//sensors readings are send to ESP8266 as CSV values

#include "DHT.h"
#include <SparkFunTSL2561.h>
#include <Wire.h>

// Create an SFE_TSL2561 object, here called "light":
SFE_TSL2561 light;
boolean gain;     // Gain setting, 0 = X1, 1 = X16;
unsigned int ms;  // Integration ("shutter") time in milliseconds


String deviceName = "Arduino_3";
String readTime = "POSIX";

#define DHTPIN1 8       // what pin we're connected to DHT 1
#define DHTTYPE DHT22   // define wich type of DHT sensor is used (int this case DHT 22  (AM2302))
DHT dht1(DHTPIN1, DHTTYPE);   //create a object to DHT 1

uint8_t payload[100];
String stringPayload;

#define RELE_1 5
#define RELE_2 6

boolean stateRelay1 = false ;
boolean stateRelay2 = false ;

double relay1StartMillis = 0;
double relay2StartMillis = 0;

int watterPumpONdelay = 5; // define how many seconds watter Pump will be ON when Soil Moisture sensor detect DRY

int LedPin = 13 ; //

//Hardware pin definitions for light sensor
int UVOUT = A1; //Output from the sensor
int REF_3V3 = A0; //3.3V power on the Arduino board

//Hardware pin definitions for soil moisture sensor
int SoilPin = A2; //Output from the sensor


void setup() {  
  pinMode(LedPin,OUTPUT);      //Set the digital pin as output.
  pinMode(RELE_1, OUTPUT);      //Set the digital pin as output.
  pinMode(RELE_2, OUTPUT);      //Set the digital pin as output.
  pinMode(SoilPin, INPUT);      //set up analog pin to be input
  pinMode(UVOUT, INPUT);      //set up analog pin to be input
  pinMode(REF_3V3, INPUT);      //set up analog pin to be input
  Serial.begin(9600);           //set baud rate for the hardware serial port_0 to 9600
  dht1.begin();
  delay(2000);
  light.begin();
  unsigned char ID;
  gain = 0;
  unsigned char time = 2;
  // setTiming() will set the third parameter (ms) to the
  // requested integration time in ms (this will be useful later):
  light.setTiming(gain,time,ms);
  light.setPowerUp();
}

void loop() { //here we go...
  digitalWrite(LedPin,HIGH);
  DHT_read();
  //UV_read();
  LIGHT_read();
  SOIL_MOISTURE_read();
  digitalWrite(LedPin,LOW);
  if (stateRelay1 || stateRelay2){
    checkRelays();
  }
  delay(5000);   //wait 5 seconds
}

