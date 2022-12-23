#include <Arduino.h>
#include <math.h>
#include <string>
#include "Canvas.h"

const int ANGLE_0 = 0;
const int ANGLE_90 = 90;
const int ANGLE_180 = 180;
const int ANGLE_270 = 270;
const int ANGLE_360 = 360;

/**
 * @brief 画点
 *
 */
/* void Canvas::drawPoint(int x, int y, int val)
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

  writeData(pointVal << pointY);
} */

/**
 * @brief 绘制线
 * 两点式求直线方程
 * @param x1
 * @param y1 起点坐标
 * @param x2
 * @param y2 终点坐标
 */
Canvas::Canvas()
{
}
Canvas::~Canvas()
{
  Serial1.printf("release canvas resource...");
}
void Canvas::drawPoint(int x, int y, int val)
{
  Serial.println("must be implement by sub class...");
}

/**
 * @brief 绘制一条直线  根据两点式求解直线方程
 *  这个方程必须满足斜率k不为0，即x1≠x2 且 y1≠y2
 * @param startX 起始点x坐标
 * @param startY 起始点y坐标
 * @param endX   终止点x坐标
 * @param endY   终止点y坐标
 */
void Canvas::drawLine(int startX, int startY, int endX, int endY)
{

  Serial.println("draw line...");

  if (startX == endX || endY == startY)
  {
    Serial.println("起始点横或纵坐标相等的情况下不适用两点式");
    if (startX == endX)
    {
      drawHLine(startX, startY, abs(endX - startX));
    }
    else
    {
      drawVLine(startX, startY, abs(endY - startY));
    }
    return;
  }

  // 确定x的方向
  int xDirection = endX - startX > 0 ? 1 : 0;
  int array[xDirection ? endX + 1 : startX + 1];
  // 确定x的取值范围

  int arrayLength = sizeof(array) / 4;

  if (xDirection)
  {
    array[0] = startX;
    array[sizeof(array) - 1] = endX;
  }
  else
  {
    array[0] = endX;
    array[sizeof(array) - 1] = startX;
  }
  // Serial.println(arrayLength);
  for (size_t i = 1; i <= arrayLength - 1; i++)
  {
    array[i] = xDirection ? startX + i : endX + i;
  }

  // int xy[size][size];

  // Serial.println("start print...");

  int x, y;
  int x2x1 = (endX - startX);
  int y2y1 = (endY - startY);

  for (size_t j = 0; j < arrayLength; j++)
  {
    if (j == 0)
    {
      drawPoint(startX, startY, 0x01);
    }
    else if (j == arrayLength - 1)
    {
      drawPoint(endX, endY, 0x01);
    }
    else
    {
      y = (array[j] - startX) * y2y1 / x2x1 + startY;
      drawPoint(array[j], y, 0x01);
      Serial.println(y);
    }
  }
}

/**
 * @brief 绘制横线
 * @param startX 起始点X坐标
 * @param startY 起始点Y坐标
 * @param length 横向长度
 */
void Canvas::drawHLine(int startX, int startY, int length)
{
  // int endX = startX + length;
  // int endY = startY;
  // drawLine(startX, startY, endX, endY);
  if (length < 0)
  {
    Serial.println("length must be positive");
    return;
  }

  for (size_t i = 0; i < length; i++)
  {
    drawPoint(startX + i, startY, 0x01);
  }
}

/**
 * @brief 绘制竖线
 * @param height 竖向长度
 */
void Canvas::drawVLine(int startX, int startY, int height)
{
  // int endX = startX;
  // int endY = startY + height;
  if (height < 0)
  {
    Serial.println("height must be positive...");
    return;
  }

  for (size_t i = 0; i < height; i++)
  {
    int offset = (1 << ((startY + i) % 8)) - 1;
    if (offset == 0)
    {
      offset = 0;
    }
    Serial.println(offset);
    drawPoint(startX, startY + i, offset);
  }
}

/**
 * @brief 绘制圆 圆上任意点横坐标 x = cosα*r y=sinα*r
 * 注意 计算出的x，y坐标是以左上角作为坐标原点，实际的画布应该是偏移了圆心的坐标单位
 *
 */
void Canvas::drawCircle(int startX, int startY, int radius)
{
  double x = 0;
  double y = 0;
  for (size_t i = 0; i < 360; i++)
  {

    if (i >= ANGLE_0 && i <= ANGLE_90)
    {
      x = startX + round(cos(i) * radius);
      y = startY - round(sin(i) * radius);
    }
    else if (i > ANGLE_90 && i <= ANGLE_180)
    {
      x = startX - round(cos(i) * radius);
      y = startY - round(sin(i) * radius);
    }
    else if (i > ANGLE_180 && i <= ANGLE_270)
    {
      x = startX - round(cos(i) * radius);
      y = startY + round(sin(i) * radius);
    }
    else if (i > ANGLE_270 && i <= ANGLE_360)
    {
      x = startX + round(cos(i) * radius);
      y = startY + round(sin(i) * radius);
    }
    else
    {
      Serial.println("all not match...");
    }
    drawPoint(x, y, 0x01);
  }
}

/**
 * @brief 绘制矩形
 *
 */
void Canvas::drawRect(int startX, int startY, int width, int height)
{
  drawHLine(startX, startY, width);
  drawHLine(startX, startY + height, width);
  drawVLine(startX, startY, height);
  drawVLine(startX + width, startY, height);
}

/**
 * @brief 绘制圆角矩形
 *
 */
void Canvas::drawRoundRect(int startX, int startY, int width, int height, int radius)
{

  // 上线
  drawHLine(startX + radius, startY, width - radius);
  // 左线
  drawVLine(startX, startY + radius, height - radius);

  // 下线
  drawHLine(startX + radius, startY + height, width - radius);
  // 右线
  drawVLine(startX + width, startY + radius, height - radius);
}

/**
 * @brief 绘制椭圆
 *
 */
void Canvas::drawOval() {}

/* void Canvas::drawLineWithSlopeInterceptForm()
{
  float x, y;

  float xx1, yy1, xx2, yy2;
  xx1 = x1;
  yy1 = y1;
  xx2 = x2;
  yy2 = y2;

  if (x1 == x2)
  {
    Serial.println("x1≠x2");
    return;
  }

  // 计算斜率
  float k = (yy2 - yy1) / (xx2 - xx1);

  Serial.print("斜率k:");
  Serial.println(k);

  int direction = x2 - x1 > 0 ? 1 : 0;
  float array[abs(x2 - x1) + 1];
  int arrayLen = sizeof(array) / 4;
  Serial.println(arrayLen);

  for (size_t i = 0; i < arrayLen; i++)
  {
    if (i == 0 || i == (arrayLen - 1))
    {
      if (i == 0)
      {
        array[0] = direction ? xx1 : xx2;
        drawPointWithXY(array[0], y1, 0x01);
      }
      else
      {
        array[arrayLen - 1] = direction ? xx2 : xx1;
        drawPointWithXY(array[arrayLen - 1], y2, 0x01);
      }
    }
    else
    {
      array[i] = direction ? xx1 + i : xx2 + i;
      y = round(k * array[i]);
      drawPointWithXY(array[i], y, 0x01);
    }
  }

  for (size_t i = 0; i < arrayLen; i++)
  {
    y = round(k * array[i]);
    Serial.print("x=");
    Serial.print(array[i]);
    Serial.print(" | ");
    Serial.print("y=");
    Serial.print(y);
    Serial.println(",");
  }
}*/

void Canvas::drawBitmap(int bitmap[8][128])
{
}

void Canvas::drawText(std::string str)
{
}
