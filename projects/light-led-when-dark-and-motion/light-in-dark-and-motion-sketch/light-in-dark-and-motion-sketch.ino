int sensorPin = A0;
int motionPin = 2;
int ledPin = 12;    
int powerPin = 4;
int potMeterPin = A1;

 
int sleepTimeInMs = 500; 
int lightTreshold = 25;
int lightTimer = 0;
int lightUpInMs = 5000;
int motionTimer = 0;
int motionMemory = 5000;
boolean isMotionNow;
boolean isDarkNow;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(powerPin, OUTPUT);
  pinMode(motionPin, INPUT);
  Serial.begin(9600);
}

void loop(){
  updateLightTreshold();
  readMotionAndDark(); 
  //debugSensors(); 
  setupTimerForLight();
  reduceTimers();
  lightAccordingToTimer();
  sleepWithPowerblocking();
}

void updateLightTreshold(){     
  lightTreshold = readPotMeterValue();
}

int readPotMeterValue(){
  return analogRead(potMeterPin);
}

void readMotionAndDark(){
  isMotionNow = isMotion();
  isDarkNow = isDark();
}

boolean isDark() {
  return analogRead(sensorPin) < lightTreshold;
}

boolean isMotion(){
  return digitalRead(motionPin) == HIGH;
}

void debugSensors(){
  Serial.print("Light sensor: ");
  Serial.print(analogRead(sensorPin));
  Serial.print(" Poti: ");
  Serial.print(analogRead(potMeterPin));
  Serial.print(" Motion sensor: ");
  Serial.println(digitalRead(motionPin));
}

void setupTimerForLight() {
  if (isMotionNow && isDarkNow){
    increaseLightTimer();
    clearMotionTimer();
  } else if (isMotionNow && !isDarkNow){
    clearTimer();
    increaseMotionTimer();
  } else if(!isMotionNow && isDarkNow && motionTimer > 0){
    increaseLightTimer();
  }else if(!isDarkNow){
    clearTimer();
  }
}

void increaseLightTimer(){
  lightTimer = lightUpInMs;
}

void clearMotionTimer(){
  motionTimer = 0;
}

void clearTimer(){
  lightTimer = 0;
}

void increaseMotionTimer(){
  motionTimer = motionMemory;
}

void lightAccordingToTimer(){
  if (lightTimer > 0) {
    digitalWrite(ledPin, HIGH);
    clearMotionTimer();
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void reduceTimers(){
  reduceLightTimer();
  reduceMotionTimer();
}

void reduceLightTimer(){
  lightTimer = lightTimer - sleepTimeInMs;
  if (lightTimer < 0){
    lightTimer = 0;
  }
}

void reduceMotionTimer(){
  motionTimer = motionTimer - sleepTimeInMs;
  if (motionTimer < 0){
    motionTimer = 0;
  }
}

void sleepWithPowerblocking(){
  powerOffSensors();
  delay(sleepTimeInMs);
  powerOnSensors();
}

void powerOnSensors(){
  digitalWrite(powerPin, HIGH);
}

void powerOffSensors(){
  digitalWrite(powerPin, LOW);
}
