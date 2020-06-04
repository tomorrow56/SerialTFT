# SerialTFT Driver for M5LCD
 Copyright (C), 2020, @tomorrow56 (a.k.a. ThousanDIY)

# Supported command
    int16_t height();
    int16_t width();

    void begin(int baud);
    void setBrightness(int8_t brightness);
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void fillScreen(uint16_t color);
    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,uint16_t color);
    void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,int16_t delta, uint16_t color);
    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
    void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
    void drawChar(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg, uint8_t size);
    void setCursor(uint16_t x0, uint16_t y0);
    void setTextColor(uint16_t color);
    void setTextColor(uint16_t color, uint16_t backgroundcolor);
    void setTextSize(uint8_t size);
    void setTextWrap(boolean w);
    void print(String text);
    void println(String text);
    void println();


    void drawCentreString(String text, int dX, int poY, int font);
    void drawRightString(String text, int dX, int poY, int font);


    void progressBar(int x, int y, int w, int h, uint8_t val);
    void qrcode(String text, uint16_t x, uint16_t y, uint8_t width, uint8_t version); // version: 2(32byte), 5(106byte), 15(520byte)

    void setRotation(int angle);
    uint16_t color565(uint8_t r, uint8_t g, uint8_t b);
    uint8_t color16to8(uint16_t c);
    uint16_t color8to16(uint8_t color);

    void drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color);
    void drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color);

