

class CanvasPlus : public GDI
{

public:

    void drawPonit(int x,int y){

    }

    void drawLine(int startX, int startY, int endX, int endY)
    {
        // 根据两点式求解直线方程

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

        Serial.println("start print...");

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
    
    void drawHLine(int startX, int startY, int endX, int endY){

    }
    void drawVLine(int startX, int startY, int endX, int endY){

    }
    void drawRect(int startX, int startY, int width, int height){

    }
    void drawRoundRect(int start X, int startY, int width, int height, int radius){

    }
    void drawCircle(int startX, int startY, int radius){

    }
    void drawOval(){

    }
    void drawBitmap(int bitmap[][]){

    }
    void drawText(String value){

    }
};