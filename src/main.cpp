

//////////////////////////主程序////////////////////////////

#include <Arduino.h>
#include "./iic/iic.h"

int led = 2;



void setup() {
  
  Serial.begin(115200);
  pinMode(led,OUTPUT);
  i2cInit(0); //0表示使用默认的从机地址
  writeCmd(0xae);  //af 开显示  ae关显示

}



void loop() {

  while(true){
    digitalWrite(led,HIGH);
    delay(1000);
    digitalWrite(led,LOW);
    delay(1000);
  }

}