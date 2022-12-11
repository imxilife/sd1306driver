

#ifndef _IIC_H_
#define _IIC_H_

    void writeByte(int data);
    void writeCmd(int command);
    void writeSerialCmd(int cmds[] ,int size);
    void writeData(int data);
    void i2cInit(int slave);

#endif