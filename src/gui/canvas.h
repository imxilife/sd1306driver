
#ifndef CANVAS_H_
#define CANVAS_H_


#include<string>

/**
 * 定义底层图形绘制能力
 * 不同的驱动芯片需要实现各自的drawPonit函数
 */
class Canvas
{

public:
    Canvas();
    virtual ~Canvas();
    virtual void drawPoint(int x, int y, int val);
    void drawLine(int startX, int startY, int endX, int endY);
    void drawHLine(int startX, int startY,int length);
    void drawVLine(int startX, int startY,int height);
    void drawCircle(int startX, int startY, int radius);
    void drawOval();
    //void drawRect(int left,int top, int right, int bottom);
    void drawRect(int startX, int startY ,int width ,int height);
    void drawRoundRect(int startX ,int startY ,int width ,int height ,int radius);
    void drawBitmap(int bitmap[8][128]);
    void drawText(std::string str);
};

#endif