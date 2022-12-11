
#include<Arduino.h>


#define HIGH_BIT_MASK 0x80
#define DATA_TR_WRITE 0x0
#define DATA_TR_READ 0x1
//每次写入指令或者数据前，先需要写入1byte控制字节，用户告诉从机接下来是读还是写操作
#define SD1306_IIC_CMD_MASK (0<<6) 
#define SD1306_IIC_DAT_MASK (1<<6)

int slaveAddr = 0x78; //for sd1306


int sda = 21;
int scl = 22;


void i2cInit(int slave){
  if(slave!=0){
    slaveAddr = slave;
  }
  Serial.println(slaveAddr);
  pinMode(sda,OUTPUT);
  pinMode(scl,OUTPUT);
}


void i2cStart(){

    digitalWrite(scl,LOW);
    digitalWrite(sda,LOW);

    digitalWrite(scl,HIGH);
    digitalWrite(sda,HIGH);
    digitalWrite(sda,LOW);
    delay(1);

    Serial.println("i2c start...");
    
}

void i2cStop(){

    digitalWrite(scl,LOW);
    digitalWrite(sda,LOW);

    digitalWrite(scl,HIGH);
    digitalWrite(sda,LOW);
    digitalWrite(sda,HIGH);
    delay(1);

    Serial.println("i2c stop...");

}

void waitAck(){

    digitalWrite(scl,LOW);
    digitalWrite(sda,LOW); //sda pull down for release iic bus

    digitalWrite(scl,HIGH);
    delay(1);

    Serial.println("i2c slave ack...");

}


void writeByte(int data){

    digitalWrite(scl,LOW);
    for (uint8_t i = 0; i < 8; i++){
        if(data << i & HIGH_BIT_MASK){
            digitalWrite(sda,HIGH);
            Serial1.println(1);
        }else{
            digitalWrite(sda,LOW);
            Serial1.println(0);
        }
        digitalWrite(scl,HIGH);
        digitalWrite(scl,LOW);
    }
    Serial1.println("one byte write finished...");
}

/**
 * @brief 
 * 写入单条命令
 * @param cmd 指令
 */
void writeCmd(int cmd){
    i2cStart();
    writeByte(slaveAddr);
    waitAck();
    writeByte(SD1306_IIC_CMD_MASK);
    waitAck();
    writeByte(cmd);
    waitAck();
    i2cStop();
}

/**
 * @brief 写入单条数据
 * 
 * @param data 数据
 */
void writeData(int data){

    i2cStart();
    writeByte(slaveAddr);
    waitAck();
    writeByte(SD1306_IIC_DAT_MASK);
    waitAck();
    writeByte(data);
    waitAck();
    i2cStop();

}

/**
 * 连续写入多条命令
 */
void writeSerialCmd(int cmds[],int size){
    i2cStart();
    writeByte(slaveAddr);
    waitAck();
    writeByte(SD1306_IIC_CMD_MASK);
    waitAck();
    for (size_t i = 0; i < size; i++){
        int cmd = cmds[i];
        writeByte(cmd);
        waitAck();
    }
    i2cStop();
}