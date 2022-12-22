
#ifndef SSD1306_H_
#define SSD1306_H_

#include "./gui/Canvas.h"

class Ssd1306 : public Canvas
{

private:
public:
    virtual ~Ssd1306();
    void initSSD1306();
    void clearScreen();
    void fillScreen();
    void clearFirstRow();
    virtual void drawPoint(int x, int y, int val) override;
};

#endif
