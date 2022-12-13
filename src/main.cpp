

//////////////////////////主程序////////////////////////////
/**
 *
 * 后续计划
 * 1. 完成SSD1306的显示初始化
 * 2. 探索SSD1306显示数据模式
 * 3. 完成在任意位置绘制一个点
 * 4. 在任意位置绘制图形 包括但不限于矩形、圆角矩形、圆等几何图形
 * 5. 在任意位置显示字符 中文和英文，包括文字的字体、大小、滚动方式等
 * 6. 研究取模软件的使用
 * 7. 研究Esp32的Wifi和蓝牙与外部设备的通信方式
 * 8. 研究手机端与Esp32模块的的通信，包括发送文字和图片等
 * 9. 研究Esp32如何驱动SD卡
 */

#include <Arduino.h>
#include "./iic/iic.h"

int led = 2;

void initSSD1306()
{

  i2cInit(0);
  // int cmdArr[] = {
  //     0xa8,
  //     0xd3,
  //     0x40,
  //     0xa0,
  //     0xc0,
  //     0xda,
  //     0x81,
  //     0xa4,
  //     0xa6,
  //     0xd5,
  //     0x8d,
  //     0xaf};
  // writeSerialCmd(cmdArr, 12);

  /*   writeCmd(0xae);  //set display off

    writeCmd(0xd5); //set dispaly clock divide radio /osc frequency
    writeCmd(0x80); //display clock divide radio /osc frequency

    writeCmd(0xa8); //set multiplex radio
    writeCmd(0x3f); //multiplex radio for 128*64 reset = **111111b

    writeCmd(0xd3); //set display offset
    writeCmd(0x00); //display offset

    writeCmd(0x40); //set display start line

    writeCmd(0x8d); //set change pump
    writeCmd(0x14); //charge pump

    writeCmd(0xa0); //set setment re-map  vs a1
    writeCmd(0xc0); //set com output scan direction  vs c8

    writeCmd(0xda); //set com hardware configuration
    writeCmd(0x02); //com hardware configuration

    writeCmd(0x81); //set contrast
    writeCmd(0xcf); //contrast

    writeCmd(0xd9); //set pre-charge period
    writeCmd(0xf1); //set pre-charge period

    writeCmd(0xdb); //set vcomh deselect level
    writeCmd(0x40); //vcomh deselect level

    writeCmd(0xa4); //set all pixels off
    writeCmd(0xaa6); //set display not inverted
    writeCmd(0xaf);  //set display on
   */

  writeCmd(0xae); // 关显示

  writeCmd(0xd5); // 设置时钟分频和RC振荡器频率
  writeCmd(0x80);

  writeCmd(0xa8); // 设置多路传输比率
  writeCmd(0x3f);

  writeCmd(0xd3); // 设置显示偏移，不偏移 为0
  writeCmd(0x0);

  writeCmd(0x40); // 设置显示开始行

  writeCmd(0x8d); // 启用电荷泵
  writeCmd(0x14);

  writeCmd(0xa1); // 左右方向显示，正常显示

  writeCmd(0xc8); // 上下方向显示，正常显示

  writeCmd(0xda); // 设置引脚的硬件配置
  writeCmd(0x12);

  writeCmd(0x81); // 设置对比度0x81,0xff
  writeCmd(0xff);

  writeCmd(0xd9); // 设置预充电期间的持续时间
  writeCmd(0xf1);

  writeCmd(0xdb); // 调整VCOM调节器的输出
  writeCmd(0x40);

  writeCmd(0xa4); // 根据RAM内容显示

  writeCmd(0xa6); // 设置正常显示0xa6

  writeCmd(0xaf); // 开显示
}

/**
 * OLED清屏
 */
void clear()
{
  // writeCmd(0x20); //Page Addressing Mode
  Serial.println("exec clear code...");
  for (int i = 0; i < 8; i++)
  {
    writeCmd(0xb0 + i % 8);
    // Serial.println(i%7);
    //  设置该页列起始低位地址
    writeCmd(0x00);
    // 设置该页列起始高位地址
    writeCmd(0x10);
    // 设置页地址【B0~B7】,每次循环后页地址+1 从Page0~Page7
    // Serial1.println(i%8);
    // Serial.println(0xb0+i%8);
    for (u_int8_t j = 0; j < 127; j++)
    { // 每页127列，SSD1306是逐列扫描，每写满一页，指针切到下一页
      writeData(0x0);
    }
  }
}

/**
 * 填充
 */
void fullScreen()
{
  for (u_int8_t i = 0; i < 8; i++)
  {
    // 从Page0~Page7
    // 设置页地址【B0~B7】,每次循环后页地址+1
    writeCmd(0xb0 + i % 8);
    // 设置该页列起始低位地址
    writeCmd(0x00);
    // 设置该页列起始高位地址
    writeCmd(0x10);
    for (u_int8_t j = 0; j < 127; j++)
    { // 每页127列，SSD1306是逐列扫描，每写满一页，指针切到下一页
      writeData(0xff);
    }
  }
}

/**
 *在任意坐标绘制一个点
 */
void drawPointForXY()
{

  /*   if(x>127||y>63){
      Serial1.println("坐标点不合法...");
      return;
    } */

  writeCmd(0xb0); // 页指针指向0
  for (int i = 0; i < 16; i++)
  {
    writeCmd(0x0 + i); // 列地位地址
    writeCmd(0x10);    // 列高位地址
    writeData(0xff);   // 写入数据1
  }

  for (int i = 0; i < 16; i++)
  {
    writeCmd(0x0 + i); // 列低位地址
    writeCmd(0x11);    // 列高位地址
    writeData(0xff);   // 写入数据1
  }

  for (int i = 0; i < 16; i++)
  {
    writeCmd(0x0 + i); // 列低位地址
    writeCmd(0x12);    // 列高位地址
    writeData(0xff);   // 写入数据1
  }

  for (int i = 0; i < 16; i++)
  {
    writeCmd(0x0 + i); // 列低位地址
    writeCmd(0x17);    // 列高位地址
    writeData(0xff);   // 写入数据1
  }
}

/**
 * @param x rang in [0~127]
 * @param y rang in [0~63]
 * @param val: 1:点亮 0:熄灭
 */
void drawPointWithXY(int x, int y, int val)
{
  if ((x < 0 || x > 127) || (y < 0 || y > 63))
  {
    Serial.println("x,y坐标不合法");
    return;
  }

  // 计算x坐标
  int lowAddr = 0x0 + x % 16;
  int hightAddr = 0x10 + x / 16;
  // 计算y坐标
  int pageIndex = 0xb0 + y / 8;
  int pointY = y % 8;

  int pointVal = 0;
  if (val & 0x01)
  {
    pointVal = 1;
  }
  else
  {
    pointVal = 0;
  }

  writeCmd(pageIndex);
  writeCmd(lowAddr);
  writeCmd(hightAddr);

  writeData(pointVal);
}

void clearFirstRow()
{
  writeCmd(0xb0); // 页指针指向0
  writeCmd(0x0);  // 列地位地址
  writeCmd(0x10); // 列高位地址
  for (int i = 0; i < 128; i++)
  {
    writeData(0x0); // 写入数据1
  }
}

void setup()
{

  Serial.begin(115200);
  pinMode(led, OUTPUT);
  initSSD1306();
  clear();
  clearFirstRow();
  // delay(1);
  // fullScreen();

  // delay(10);

  // clear();

  // clear();

  // drawPointForXY();
}

void loop()
{

  //drawPointForXY();

  drawPointWithXY(0,0,1);
  drawPointWithXY(127,0,1);
  drawPointWithXY(0,63,1);
  drawPointWithXY(127,63,1);

  while (true)
  {
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000);
  }
}