

#ifndef IIC_H_
#define IIC_H_

class I2C
{

private:
    void i2cStart();
    void i2cStop();
    void waitAck();

public:
    virtual ~I2C();
    void writeByte(int data);
    void writeCmd(int command);
    void writeSerialCmd(int cmds[], int size);
    void writeData(int data);
    void i2cInit(int slave);
};

#endif