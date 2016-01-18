int ledPin = 3;
int potPin = A0;
int pause = 50;
int brightness = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop() {
  brightness = analogRead(potPin);           
  brightness = map(brightness, 0, 1023, 0, 255);     
  analogWrite(ledPin, brightness);            
  delay(pause);                        
}
