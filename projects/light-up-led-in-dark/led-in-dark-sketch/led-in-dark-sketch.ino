int sensorPin = A0;   
int ledPin = 13;     
int sensorValue = 0; 

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  if ( sensorValue < 25 ) {
   digitalWrite(ledPin, HIGH);
  } else {
   digitalWrite(ledPin, LOW); 
  }
  delay(30);
}
