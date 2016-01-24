int rightLightSensorPin = A0;
int leftLightSensorPin = A1;
int rightMotorPin = 3;
int leftMotorPin = 5;
int standByLedPin = 13;
int actionLedPin = 12;

int powerBlockPin = 8;

int rightLight = 0;
int leftLight = 0;

int gearNumber = 10;
int minSpeed = 85;
int maxSpeed = 200;

int lightThreshold = 200;

int sleepTimeInMs = 500;

void setup() {
  pinMode(rightMotorPin, OUTPUT);
  pinMode(leftMotorPin, OUTPUT);
  pinMode(standByLedPin, OUTPUT);
  pinMode(actionLedPin, OUTPUT);
  pinMode(powerBlockPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  readLightValues();
  zeroLightValuesUnderThreshold();
  scaleLightValues();
  runMotors();
  updateFeedbackLeds();
  sleepWithPowerBlocking();
}

void readLightValues(){
  rightLight = readRightSensor();
  leftLight = readLeftSensor();
}

int readRightSensor(){
  return analogRead(rightLightSensorPin);
}

int readLeftSensor(){
  return analogRead(leftLightSensorPin);
}

void zeroLightValuesUnderThreshold(){
  if(rightLight < lightThreshold){
    rightLight = 0;
  }
  if(leftLight < lightThreshold){
    leftLight = 0;
  }
}

void scaleLightValues(){
  if (rightLight != leftLight != 0){
    rightLight = map(rightLight, 0, 1023, 0, gearNumber);
    rightLight = map(rightLight, 0, gearNumber, minSpeed, maxSpeed);
    leftLight = map(leftLight, 0, 1023, 0, gearNumber);
    leftLight = map(leftLight, 0, gearNumber, minSpeed, maxSpeed);
    
  Serial.print("Left motor:");
  Serial.print(leftLight);
  Serial.print(" Right motor:");
  Serial.println(rightLight);
  }
}

void runMotors(){
  analogWrite(rightMotorPin, leftLight);
  analogWrite(leftMotorPin, rightLight);
}

void updateFeedbackLeds(){
  if(rightLight == leftLight == 0){
    switchFeedbackLedsToStandBy();
  } else {
    switchFeedbackLedsToAction();
  }
}

void switchFeedbackLedsToAction(){
  digitalWrite(actionLedPin, HIGH);
  digitalWrite(standByLedPin, LOW);
}

void switchFeedbackLedsToStandBy(){
  digitalWrite(actionLedPin, LOW);
  digitalWrite(standByLedPin, HIGH);
}

void sleepWithPowerBlocking(){
  digitalWrite(powerBlockPin, LOW);
  delay(sleepTimeInMs);
  digitalWrite(powerBlockPin, HIGH);
}

