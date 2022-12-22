

#ifndef IIC_H_
#define IIC_H_

namespace i2c
{

    class IIC
    {

    private:
        void i2cStart();
        void i2cStop();
        void waitAck();

    public:
        IIC();
        ~IIC();
        void writeByte(int data);
        void writeCmd(int command);
        void writeSerialCmd(int cmds[], int size);
        void writeData(int data);
        void i2cInit(int slave);
    }

};

#endif