#include <EEPROM.h>

void setup() {
  Serial.begin(9600);
  for(int i=0; i<1024; ++i){
    EEPROM.write(i, 0);
  }
}

void loop() {
  String command = Serial.readStringUntil(' ');
  if(command.equals("read")){
    int address = Serial.readStringUntil('\n').toInt();
    int result;
    EEPROM.get(address, result);
    Serial.println(result,DEC);
  }else if(command.equals("write")){
    int address = Serial.readStringUntil(' ').toInt();
    int value = Serial.readStringUntil('\n').toInt();
    EEPROM.write(address, value);
  }
  delay(10);
}
