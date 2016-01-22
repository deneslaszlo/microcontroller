void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
  digitalWrite(13, HIGH);
}

void loop() {
  Serial.println(digitalRead(12));
  delay(500);

}
