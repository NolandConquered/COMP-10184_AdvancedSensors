// I, Nolan Carter, student number 000817341, certify that this material is my original work.
// No other person's work has been used without due acknowledgement and neither have I made my work available to anyone else.
 
// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 

// will store temp sensor address
DeviceAddress tempSensor;

boolean found = true;
void getTemp(){
  float fTemp; 
  String judgement;
  
  while(found){
    if (DS18B20.getAddress(tempSensor, 0)) {
    found = true;
    // ask DS18B20 for the current temperature 
    DS18B20.requestTemperatures(); 
    // fetch the temperature.  We only have 1 sensor, so the index is 0. 
    fTemp = DS18B20.getTempCByIndex(0);

    if (fTemp < 10){ judgement = ", or Cold!"; } 
    else if (fTemp < 15){ judgement = ", or Cool"; }
    else if (fTemp < 25){ judgement = ", or Perfect"; }
    else if (fTemp < 30){ judgement = ", or Warm"; }
    else if (fTemp < 35){ judgement = ", or Hot"; }
    else{ judgement = ", or Too Hot!"; }
 
    // print the temp to the USB serial monitor 
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius" + judgement); 
 
    // wait 2s (2000ms) before doing this again 
    delay(5000);
    }
    else {
      if (found)
      {
        Serial.println("No DS18B20 temperature sensors are installed");
        found = false;
      }
    }
  }
}
 
void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200);

  Serial.println();
  Serial.println("Temperature Application"); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 

  if(DS18B20.getAddress(tempSensor,0)) {
    Serial.print("Found DS18B20 with address: ");
    for (uint8_t i = 0; i < 8; i++) {
      if (tempSensor[i] < 16) Serial.print("0");
        Serial.print(tempSensor[i], HEX);
    } 
  } else {
    Serial.println("No DS18B20 temperature sensors are installed");
    found = false;
  }
  Serial.println();
  getTemp();
} 

void loop(){
}
