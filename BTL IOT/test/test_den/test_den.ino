void setup() {
  Serial.begin(115200);
  pinMode(D2, OUTPUT);  
  pinMode(D1, OUTPUT);
}

void loop() {
  digitalWrite(D2, HIGH); 
  digitalWrite(D1, LOW);  
  delay(1000);   

  digitalWrite(D2, LOW);  
  digitalWrite(D1, HIGH);
  delay(1000);
}