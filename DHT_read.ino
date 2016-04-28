float h, t,f;

void DHT_read() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  //  readTime = String(rtc.getUnixTime(rtc.getTime()));  //preserve read time in POSIX format
  h = dht1.readHumidity();  // Read Humidity
  t = dht1.readTemperature(); // Read temperature as Celsius
  f = dht1.readTemperature(true); // Read temperature as Fahrenheit
  processaDHT("DHT1");
}

void processaDHT(String sensorName) { //mount TAGs and send to MQTT
  String reading ;
  if (isnan(h) || isnan(t) || isnan(f)) { // Check if any reads failed and exit early (to try again).
    reading = "NULL";
  }else{
    reading = String(h);
  }
  sendPayload(deviceName,sensorName,"Humidity","%",readTime,reading,"M");
delay(10);
  if (isnan(h) || isnan(t) || isnan(f)) { // Check if any reads failed and exit early (to try again).
    reading = "NULL";
  }else{
    reading = String(f);
  }
  sendPayload(deviceName,sensorName,"Temperature","F",readTime,reading,"M");
} 

