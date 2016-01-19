int sensorPinArray[] = {A1, A2, A3, A4};
int sensorCount = 1;
int motionPinArray[] = {2};
int motionSensorCount = 1;
int ledPin = 12;    
int powerPin = 4;
int potMeterPin = A0;

 
int sleepTimeInMs = 100; 
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
  setupMotionPins();
  Serial.begin(9600);
}

void setupMotionPins(){
  for(int i = 0; i< motionSensorCount; i++){
    pinMode(motionPinArray[i], INPUT);
  }
}

void loop(){
  updateLightTreshold();
  readMotionAndDark(); 
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
  boolean dark = true;
  for(int i=0; i< sensorCount; i++){
    boolean darkOnPin = isDarkOnPin(sensorPinArray[i]);
    if(!darkOnPin){
      dark = false;
      break;
    }
  }
  return dark;
}

boolean isDarkOnPin(int pin){
  return analogRead(pin) < lightTreshold;
}

boolean isMotion(){
  boolean motion = false;
  for(int i=0; i<motionSensorCount; i++){
    if(isMotionOnPin(motionPinArray[i])){
      motion = true;
      break;
    }
  }
  return motion;
}

boolean isMotionOnPin(int pin){
  return digitalRead(pin) == HIGH;
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
