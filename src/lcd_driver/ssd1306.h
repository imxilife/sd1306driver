
#ifndef SSD1306_H_
#define SSD1306_H_

namespace lcdDriver
{
    class SSD1306{

        private:
            
        public:
            SSD1306();
            virtual ~SSD1306();
            void initSSD1306() ;
            void clearScreen() ;
            void fillScreen() ;
            void clearFirstRow();
    };

}

#endif
