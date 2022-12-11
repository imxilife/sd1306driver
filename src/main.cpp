

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



void setup() {
  
  Serial.begin(115200);
  pinMode(led,OUTPUT);
  i2cInit(0); //0表示使用默认的从机地址
  writeCmd(0xaf);  //af 开显示  ae关显示

}



void loop() {

  while(true){
    digitalWrite(led,HIGH);
    delay(1000);
    digitalWrite(led,LOW);
    delay(1000);
  }

}