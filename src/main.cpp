

//////////////////////////主程序////////////////////////////
/**
 *
 * 后续计划
 * 1. 完成SSD1306的显示初始化 【完成】
 * 2. 探索SSD1306显示数据模式 【完成】
 * 3. 完成在任意位置绘制一个点 【完成】
 * 4. 在任意位置绘制图形 包括但不限于矩形、圆角矩形、圆等几何图形 【开发中...】
 * 5. 在任意位置显示字符 中文和英文，包括文字的字体、大小、滚动方式等
 * 6. 研究取模软件的使用
 * 7. 研究Esp32的Wifi和蓝牙与外部设备的通信方式
 * 8. 研究手机端与Esp32模块的的通信，包括发送文字和图片等
 * 9. 研究Esp32如何驱动SD卡
 */

#include <Arduino.h>
#include <math.h>
#include "./lcd_driver/Ssd1306.h"
#include "./gui/Canvas.h"

int led = 2; // for test

Ssd1306 ssd1306;
Canvas* canvas;

void initSSD1306()
{
  ssd1306.initSSD1306();
}

void setup()
{
 
  canvas = new Ssd1306();
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  initSSD1306();
  ssd1306.clearScreen();
}

void loop()
{

  //画点
  //canvas->drawPoint(20,20,0x01);
  //画线
  //canvas->drawLine(0,0,128,64);
  //画圆
  //canvas->drawCircle(64,32,30);
  //画矩形
  //canvas->drawRect(20,20,50,30);
  //画横线
  canvas->drawHLine(20,20,40);
  //画竖线
  //canvas->drawVLine(20,20,40);

  while (true)
  {
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000);
  }
}