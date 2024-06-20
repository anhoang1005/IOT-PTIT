void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(1, LOW);
  delay(1000);
  digitalWrite(1, HIGH);
  delay(1000);
}
