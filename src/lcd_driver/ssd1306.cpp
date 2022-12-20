
#include <Arduino.h>
#include "./iic/iic.h"
#include "./gui/canvas.hpp"

namespace LcdDriver
{

    LcdDriver::SSD1306::SSD1306()
    {
        Serial.println("call ssd1306 construct...")
    }

    void SSD1306::initSSD1306()
    {
        IIC::i2cInit(0);
        IIC::writeCmd(0xae); // 关显示

        IIC::writeCmd(0xd5); // 设置时钟分频和RC振荡器频率
        IIC::writeCmd(0x80);

        IIC::writeCmd(0xa8); // 设置多路传输比率
        IIC::writeCmd(0x3f);

        IIC::writeCmd(0xd3); // 设置显示偏移，不偏移 为0
        IIC::writeCmd(0x0);

        IIC::writeCmd(0x40); // 设置显示开始行

        IIC::writeCmd(0x8d); // 启用电荷泵
        IIC::writeCmd(0x14);

        IIC::writeCmd(0xa1); // 左右方向显示，正常显示

        IIC::writeCmd(0xc8); // 上下方向显示，正常显示

        IIC::writeCmd(0xda); // 设置引脚的硬件配置
        IIC::writeCmd(0x12);

        IIC::writeCmd(0x81); // 设置对比度0x81,0xff
        IIC::writeCmd(0xff);

        IIC::writeCmd(0xd9); // 设置预充电期间的持续时间
        IIC::writeCmd(0xf1);

        IIC::writeCmd(0xdb); // 调整VCOM调节器的输出
        IIC::writeCmd(0x40);

        IIC::writeCmd(0xa4); // 根据RAM内容显示

        IIC::writeCmd(0xa6); // 设置正常显示0xa6

        IIC::writeCmd(0xaf); // 开显示

        Serial.println("init ssd1306 finished...");
    }

    SSD1306::~SSD1306()
    {
        Serial.println("release resource...")
    }

    void SSD1306::clearScreen()
    {
        Serial.println("clear screen...")
            // writeCmd(0x20); //Page Addressing Mode
            Serial.println("exec clear code...");
        for (int i = 0; i < 8; i++)
        {
            IIC::writeCmd(0xb0 + i % 8);
            // Serial.println(i%7);
            //  设置该页列起始低位地址
            IIC::writeCmd(0x00);
            // 设置该页列起始高位地址
            IIC::writeCmd(0x10);
            // 设置页地址【B0~B7】,每次循环后页地址+1 从Page0~Page7
            // Serial1.println(i%8);
            // Serial.println(0xb0+i%8);
            for (u_int8_t j = 0; j < 127; j++)
            { // 每页127列，SSD1306是逐列扫描，每写满一页，指针切到下一页
                IIC::writeData(0x0);
            }
        }
    }

    void SSD1306::fillScreen()
    {
        Serial.println("fill screen...") for (u_int8_t i = 0; i < 8; i++)
        {
            // 从Page0~Page7
            // 设置页地址【B0~B7】,每次循环后页地址+1
            IIC::writeCmd(0xb0 + i % 8);
            // 设置该页列起始低位地址
            IIC::writeCmd(0x00);
            // 设置该页列起始高位地址
            IIC::writeCmd(0x10);
            for (u_int8_t j = 0; j < 127; j++)
            { // 每页127列，SSD1306是逐列扫描，每写满一页，指针切到下一页
                IIC::writeData(0xff);
            }
        }
    }

    void SSD1306::clearFirstRow()
    {
        IIC::writeCmd(0xb0); // 页指针指向0
        IIC::writeCmd(0x0);  // 列地位地址
        IIC::writeCmd(0x10); // 列高位地址
        for (int i = 0; i < 128; i++)
        {
            IIC::writeData(0x0); // 写入数据1
        }
    }
}
