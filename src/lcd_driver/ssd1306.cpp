#include <Arduino.h>
#include "./iic/I2c.h"
#include "Ssd1306.h"

I2C i2c;

void Ssd1306::initSSD1306()
{
    Serial.println("init ssd1306 start...");
    i2c.i2cInit(0);
    i2c.writeCmd(0xae); // 关显示

    i2c.writeCmd(0xd5); // 设置时钟分频和RC振荡器频率
    i2c.writeCmd(0x80);

    i2c.writeCmd(0xa8); // 设置多路传输比率
    i2c.writeCmd(0x3f);

    i2c.writeCmd(0xd3); // 设置显示偏移，不偏移 为0
    i2c.writeCmd(0x0);

    i2c.writeCmd(0x40); // 设置显示开始行

    i2c.writeCmd(0x8d); // 启用电荷泵
    i2c.writeCmd(0x14);

    i2c.writeCmd(0xa1); // 左右方向显示，正常显示

    i2c.writeCmd(0xc8); // 上下方向显示，正常显示

    i2c.writeCmd(0xda); // 设置引脚的硬件配置
    i2c.writeCmd(0x12);

    i2c.writeCmd(0x81); // 设置对比度0x81,0xff
    i2c.writeCmd(0xff);

    i2c.writeCmd(0xd9); // 设置预充电期间的持续时间
    i2c.writeCmd(0xf1);

    i2c.writeCmd(0xdb); // 调整VCOM调节器的输出
    i2c.writeCmd(0x40);

    i2c.writeCmd(0xa4); // 根据RAM内容显示

    i2c.writeCmd(0xa6); // 设置正常显示0xa6

    i2c.writeCmd(0xaf); // 开显示

    Serial.println("init ssd1306 end...");
}

Ssd1306::~Ssd1306()
{
    Serial.println("release resource...");
}

void Ssd1306::clearScreen()
{
    Serial.println("clear screen...");
    // writeCmd(0x20); //Page Addressing Mode
    Serial.println("exec clear code...");
    for (int i = 0; i < 8; i++)
    {
        i2c.writeCmd(0xb0 + i % 8);
        // Serial.println(i%7);
        //  设置该页列起始低位地址
        i2c.writeCmd(0x00);
        // 设置该页列起始高位地址
        i2c.writeCmd(0x10);
        // 设置页地址【B0~B7】,每次循环后页地址+1 从Page0~Page7
        // Serial1.println(i%8);
        // Serial.println(0xb0+i%8);
        for (u_int8_t j = 0; j < 127; j++)
        { // 每页127列，SSD1306是逐列扫描，每写满一页，指针切到下一页
            i2c.writeData(0x0);
        }
    }
}

void Ssd1306::fillScreen()
{
    Serial.println("fill screen...");
    for (u_int8_t i = 0; i < 8; i++)
    {
        // 从Page0~Page7
        // 设置页地址【B0~B7】,每次循环后页地址+1
        i2c.writeCmd(0xb0 + i % 8);
        // 设置该页列起始低位地址
        i2c.writeCmd(0x00);
        // 设置该页列起始高位地址
        i2c.writeCmd(0x10);
        for (u_int8_t j = 0; j < 127; j++)
        { // 每页127列，SSD1306是逐列扫描，每写满一页，指针切到下一页
            i2c.writeData(0xff);
        }
    }
}

void Ssd1306::clearFirstRow()
{
    i2c.writeCmd(0xb0); // 页指针指向0
    i2c.writeCmd(0x0);  // 列地位地址
    i2c.writeCmd(0x10); // 列高位地址
    for (int i = 0; i < 128; i++)
    {
        i2c.writeData(0x0); // 写入数据1
    }
}

void Ssd1306::drawPoint(int x, int y, int val)
{

    // Serial.println("ssd1306 implement draw point function...");
    if (x < 0 || x > 127)
    {
        Serial.print("x=");
        Serial.print(x);
        Serial.println("y坐标不合法");
        return;
    }
    if (y < 0 || y > 63)
    {
        Serial.print("|y=");
        Serial.print(y);
        Serial.println();
        Serial.println("y坐标不合法");
        return;
    }

    // 计算x坐标
    int lowAddr = 0x0 + x % 16;
    int hightAddr = 0x10 + x / 16;
    // 计算y坐标
    int pageIndex = 0xb0 + y / 8;
    int pointY = y % 8;

    int pointVal = 0;

    int vv = val & 0xff;
    i2c.writeCmd(pageIndex);
    i2c.writeCmd(lowAddr);
    i2c.writeCmd(hightAddr);
    if (vv == 0x01)
    {
        i2c.writeData(vv << pointY);
    }
    else
    {
        i2c.writeData(vv);
    }
}
