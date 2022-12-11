
#include <Arduino.h>

int sd1306_tr_write =  0x0;
int sd1306_tr_read = 0x1;
//#define SD1306_IIC_TR_READ 0x1;
//#define SD1306_IIC_CMD_MASK (0<<6);
//#define SD1306_IIC_DAT_MASK (1<<6);

int SD1306_IIC_CMD_MASK = 0;
int SD1306_IIC_DAT_MASK = 0x40;

int led = 2;

int SDA_1306 = 21;
int SCL_1306 = 22;
int HIGH_BIT_MASK = 0x80;


void initPIN() {

  pinMode(SCL_1306, OUTPUT);  //两个管脚都设置为输出模式
  pinMode(SDA_1306, OUTPUT);
  pinMode(led,OUTPUT);
}

/**
 启动IIC通信
 SCL 在高电平期间 SDA从高到低的跳变 完成IIC的启动
**/
void i2cCStart() {

  digitalWrite(SCL_1306, LOW); //先将总线释放
  digitalWrite(SDA_1306, LOW);
  //delay(1);
  digitalWrite(SCL_1306, HIGH); //拉高SCL
  digitalWrite(SDA_1306, HIGH); //SDA HIGH ->LOW 触发起始信号
  digitalWrite(SDA_1306, LOW);
  delay(1);
  //digitalWrite(SCL_1306, LOW); //iic 启动完成，拉低SCL
}

/**
  停止IIC通信
**/
void i2cCStop() {
  
  digitalWrite(SDA_1306, LOW);
  digitalWrite(SCL_1306, LOW);
  
  digitalWrite(SCL_1306, HIGH);
  digitalWrite(SDA_1306, LOW);
  digitalWrite(SDA_1306, HIGH);
  delay(1);
  //digitalWrite(SCL_1306,LOW);

}

void waitCAck(){

    digitalWrite(SDA_1306,LOW);  //SDA拉低 释放总线
    digitalWrite(SCL_1306,LOW);
  
    digitalWrite(SCL_1306,HIGH);
    delay(1); 
}

/**
  写入一个字节到iic从机
*/
void writeCByte(int data) {

  digitalWrite(SCL_1306,LOW);
  for (int i = 0; i < 8; i++) {
    if (data << i & HIGH_BIT_MASK) {
      digitalWrite(SDA_1306, HIGH);
      //digitalWrite(led,HIGH);
      Serial.println(1);
    } else {
      digitalWrite(SDA_1306, LOW);
      //digitalWrite(led,LOW);
      Serial.println(0);
    }
    digitalWrite(SCL_1306, HIGH);  //SCL高平期间，保持数据 即SDA写入
    digitalWrite(SCL_1306,LOW);
    //delay(1);
  }
  Serial.println("write finished...");
}

/**
写入命令
**/
void iicWriteCommand(int command){
  i2cCStart();  //i2c启动
  writeCByte(0x78); //写入从机地址和R/W控制位
  waitCAck();  //等待从机应答
  writeCByte(SD1306_IIC_CMD_MASK); //写入命令掩码
  waitCAck();  //等待从机应答
  writeCByte(command); //写控制寄存器 
  waitCAck(); //等待从机应答
  i2cCStop(); //结束i2c通信
}

/**
写入数据
**/
void iicWriteData(int data){
  i2cCStart();
  writeCByte(0x78); //写入从机地址和R/W控制位
  waitCAck();  //等待从机应答
  writeCByte(SD1306_IIC_DAT_MASK); //写入数据掩码
  waitCAck();  //等待从机应答
  writeCByte(data); //写数据
  waitCAck(); //等待从机应答
  i2cCStop(); //结束i2c通信
  
}


void setup() {
  
  Serial.begin(115200);
  initPIN();
  //i2cCStart();
  iicWriteCommand(0xae);
  iicWriteCommand(0x00);
  iicWriteCommand(0xb0);
  iicWriteCommand(0x81);
  iicWriteCommand(0xc8);
  iicWriteCommand(0xd5);
  iicWriteCommand(0xd8);
  iicWriteCommand(0xd9);
  iicWriteCommand(0xda);
  iicWriteCommand(0xdb);
  iicWriteCommand(0x8d);
  iicWriteCommand(0xaf);

}

void initSD1306(){
  i2cCStart();
  iicWriteCommand(0xa8);
}

void loop() {
  



  while(true){
    digitalWrite(led,HIGH);
    delay(500);
    digitalWrite(led,LOW);
    delay(500);
  }

}



///////////////////////////////////////////////////////////////////

/**#include <Arduino.h>
#include "./iic/iic.h"

int led = 2;



void setup() {
  
  Serial.begin(115200);
  pinMode(led,OUTPUT);
  //i2cInit(0); //0表示使用默认的从机地址
  //writeCmd(0xaf);  //ae 开显示  af关显示

}



void loop() {
  
  i2cInit(0);
  writeCmd(0xaf);

  while(true){
    digitalWrite(led,HIGH);
    delay(1000);
    digitalWrite(led,LOW);
    delay(1000);
  }

}**/