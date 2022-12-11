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
void i2cStart() {

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
void i2cStop() {
  
  digitalWrite(SDA_1306, LOW);
  digitalWrite(SCL_1306, LOW);
  
  digitalWrite(SCL_1306, HIGH);
  digitalWrite(SDA_1306, LOW);
  digitalWrite(SDA_1306, HIGH);
  delay(1);
  //digitalWrite(SCL_1306,LOW);

}

void waitAck(){

    digitalWrite(SDA_1306,LOW);  //SDA拉低 释放总线
    digitalWrite(SCL_1306,LOW);
  
    digitalWrite(SCL_1306,HIGH);
    delay(1); 
}

/**
  写入一个字节到iic从机
*/
void writeByte(int data) {

  digitalWrite(SCL_1306,LOW);
  for (int i = 0; i < 8; i++) {
    if (data << i & HIGH_BIT_MASK) {
      digitalWrite(SDA_1306, HIGH);
      digitalWrite(led,HIGH);
      Serial.println(1);
    } else {
      digitalWrite(SDA_1306, LOW);
      digitalWrite(led,LOW);
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
  i2cStart();  //i2c启动
  writeByte(0x78); //写入从机地址和R/W控制位
  waitAck();  //等待从机应答
  writeByte(SD1306_IIC_CMD_MASK); //写入命令掩码
  waitAck();  //等待从机应答
  writeByte(command); //写控制寄存器 
  waitAck(); //等待从机应答
  i2cStop(); //结束i2c通信
}

/**
写入数据
**/
void iicWriteData(int data){
  i2cStart();
  writeByte(0x78); //写入从机地址和R/W控制位
  waitAck();  //等待从机应答
  writeByte(SD1306_IIC_DAT_MASK); //写入数据掩码
  waitAck();  //等待从机应答
  writeByte(data); //写数据
  waitAck(); //等待从机应答
  i2cStop(); //结束i2c通信
  
}


void setup() {
  
  Serial.begin(115200);
  initPIN();
  i2cStart();
  //iicWriteCommand(0xaf);

}

void initSD1306(){
  i2cStart();
  iicWriteCommand(0xa8);
  

}

void loop() {
  



  while(true){
    digitalWrite(led,HIGH);
    delay(1000);
    digitalWrite(led,LOW);
    delay(1000);
  }

}