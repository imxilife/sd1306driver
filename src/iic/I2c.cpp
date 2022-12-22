
#include <Arduino.h>
#include "I2c.h"

//TODO 后续这些字段定义成外部传入
#define HIGH_BIT_MASK 0x80
#define DATA_TR_WRITE 0x0
#define DATA_TR_READ 0x1
// 每次写入指令或者数据前，先需要写入1byte控制字节，用户告诉从机接下来是读还是写操作
#define SD1306_IIC_CMD_MASK (0 << 6)
#define SD1306_IIC_DAT_MASK (1 << 6)

int slaveAddr = 0x78; //作为构造函数的参数从外部传入

int sda = 21;  //作为构造函数的参数从外部传入
int scl = 22;  //同上

/**
 * @brief I2c初始化
 * @param slave IIC设备地址
*/
void I2C::i2cInit(int slave)
{
    if (slave != 0)
    {
        slaveAddr = slave;
    }
    // Serial.println(slaveAddr);
    pinMode(sda, OUTPUT);
    pinMode(scl, OUTPUT);
}

/**
 * @brief i2c的启动时序
*/
void I2C::i2cStart()
{

    digitalWrite(scl, LOW);
    digitalWrite(sda, LOW);

    digitalWrite(scl, HIGH);
    digitalWrite(sda, HIGH);
    digitalWrite(sda, LOW);
    delay(1);

    // Serial.println("i2c start...");
}

/**
 * @brief i2c停止时序
*/
void I2C::i2cStop()
{

    digitalWrite(scl, LOW);
    digitalWrite(sda, LOW);

    digitalWrite(scl, HIGH);
    digitalWrite(sda, LOW);
    digitalWrite(sda, HIGH);
    delay(1);

    // Serial.println("i2c stop...");
}

/**
 * @brief i2c应答时序
*/
void I2C::waitAck()
{

    digitalWrite(scl, LOW);
    digitalWrite(sda, LOW); // sda pull down for release iic bus

    digitalWrite(scl, HIGH);
    delay(1);

    // Serial.println("i2c slave ack...");
}

I2C::~I2C()
{
    Serial.println("release iic instance...");
}

/**
 * @brief i2c写入一个字节
 * @param data 1byte
*/
void I2C::writeByte(int data)
{
    digitalWrite(scl, LOW);
    for (uint8_t i = 0; i < 8; i++)
    {
        if (data << i & HIGH_BIT_MASK)
        {
            digitalWrite(sda, HIGH);
            //Serial1.println(1);
        }
        else
        {
            digitalWrite(sda, LOW);
            //Serial1.println(0);
        }
        digitalWrite(scl, HIGH);
        digitalWrite(scl, LOW);
    }
    // Serial1.println("one byte write finished...");
}

/**
 * @brief 往i2c设备写入指令
 * @param cmd 指令 1byte
 */
void I2C::writeCmd(int command)
{
    i2cStart();
    writeByte(slaveAddr);
    waitAck();
    writeByte(SD1306_IIC_CMD_MASK);
    waitAck();
    writeByte(command);
    waitAck();
    i2cStop();
}

/**
 * @brief 向i2c设备发送数据
 *
 * @param data 1byte
 */
void I2C::writeData(int data)
{

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
 * @brief 向i2c设备发送指令
 * 
*/
void I2C::writeSerialCmd(int cmds[], int size)
{

    i2cStart();
    writeByte(slaveAddr);
    waitAck();
    writeByte(SD1306_IIC_CMD_MASK);
    waitAck();
    for (size_t i = 0; i < size; i++)
    {
        int cmd = cmds[i];
        writeByte(cmd);
        waitAck();
    }
}
