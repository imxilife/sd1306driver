

#include <Arduino.h>
#include "./iic/iic.h"
#include "canvas.hpp"

namespace Gui
{

  /**
   * @brief 画点
   *
   */
   void Canvas::drawPoint(int x, int y, int val)
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
  }

  /**
   * @brief 绘制线
   * 两点式求直线方程
   * @param x1
   * @param y1 起点坐标
   * @param x2
   * @param y2 终点坐标
   */
   void Canvas::drawLine(int x1, int y1, int x2, int y2)
  {

    // 根据两点式求解直线方程

    // 确定x的方向
    int xDirection = x2 - x1 > 0 ? 1 : 0;
    int array[xDirection ? x2 + 1 : x1 + 1];
    // 确定x的取值范围

    int arrayLength = sizeof(array) / 4;

    if (xDirection)
    {
      array[0] = x1;
      array[sizeof(array) - 1] = x2;
    }
    else
    {
      array[0] = x2;
      array[sizeof(array) - 1] = x1;
    }
    // Serial.println(arrayLength);
    for (size_t i = 1; i <= arrayLength - 1; i++)
    {
      array[i] = xDirection ? x1 + i : x2 + i;
    }

    // int xy[size][size];

    Serial.println("start print...");

    int x, y;
    int x2x1 = (x2 - x1);
    int y2y1 = (y2 - y1);

    for (size_t j = 0; j < arrayLength; j++)
    {
      if (j == 0)
      {
        drawPoint(x1, y1, 0x01);
      }
      else if (j == arrayLength - 1)
      {
        drawPoint(x2, y2, 0x01);
      }
      else
      {
        y = (array[j] - x1) * y2y1 / x2x1 + y1;
        drawPoint(array[j], y, 0x01);
        Serial.println(y);
      }
    }
  }

  /**
   * @brief 绘制横线
   *
   */
   void Canvas::drawHLine(int x1,int y1,int x2, int y2)
  {
      
  }

  /**
   * @brief 绘制竖线
   *
   */
   void Canvas::drawVLine()
  {
  }

  /**
   * @brief 绘制圆
   *
   */
   void Canvas::drawCircle()
  {
  }

  /**
   * @brief 绘制矩形
   *
   */
   void Canvas::drawRect()
  {
  }

  /**
   * @brief 绘制圆角矩形
   *
   */
   void Canvas::drawRoundRect()
  {
  }

  /**
   * @brief 绘制椭圆
   *
   */
   void Canvas::drawOval()
  {
  }

   void Canvas::drawLineWithSlopeInterceptForm()
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
  }

  Gui::Canvas::Canvas()
  {
  }
  Canvas::~Canvas()
  {
  }
}