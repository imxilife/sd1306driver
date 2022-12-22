
#include<Arduino.h>
#include<string.h>

using namespace std;

/**
 * 底层图形驱动类
 * 定义图形绘制的能力接口
 * graphics display interface
*/
class GDI{

    public:
        virtual void drawPonit(int x ,int y, int val);
        virtual void drawLine(int startX, int startY,int endX,int endY);
        virtual void drawHLine(int startX, int startY, int endX, int endY);
        virtual void drawVLine(int startX, int startY, int endX, int endY);
        virtual void drawRect(int startX ,int startY, int width, int height);
        virtual void drawRoundRect(int start X, int startY, int width ,int height, int radius);
        virtual void drawCircle(int startX,int startY, int radius);
        virtual void drawOval();
        virtual void drawBitmap(int bitmap[][]);
        virtual void drawText(String value);

};

