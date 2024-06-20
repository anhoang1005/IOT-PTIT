#include "DHT.h"            
const int DHTPIN = D2;      
const int DHTTYPE = DHT11;  
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(115200);
  dht.begin();       
}
void loop() {
  float h = dht.readHumidity();    
  float t = dht.readTemperature(); 
  Serial.print("Nhiet do C: ");
  Serial.println(t);            
  Serial.print("Do am: ");
  Serial.println(h);            
  delay(2000);                     
}