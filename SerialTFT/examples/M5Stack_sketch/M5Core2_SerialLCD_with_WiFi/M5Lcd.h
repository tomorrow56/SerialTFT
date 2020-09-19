#ifndef _m5lcd_h
#define _m5lcd_h

#include <M5Core2.h>

#define SIZE_OF_ARRAY(array)    (sizeof(array)/sizeof(array[0]))

/********************************************
* M5.LCD function
*    M5.lcd.setBrightness(uint8_t brightness);
*    M5.Lcd.drawPixel(int16_t x, int16_t y, uint16_t color);
*    M5.Lcd.drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
*    M5.Lcd.drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
*    M5.Lcd.fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
*    M5.Lcd.fillScreen(uint16_t color);
*    M5.Lcd.drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
*    M5.Lcd.drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,uint16_t color);
*    M5.Lcd.fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
*    M5.Lcd.fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,int16_t delta, uint16_t color);
*    M5.Lcd.drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
*    M5.Lcd.fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
*    M5.Lcd.drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
*    M5.Lcd.fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
x    M5.Lcd.drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);
x    M5.Lcd.drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w, int16_t h),
*    M5.Lcd.drawChar(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg, uint8_t size);
*    M5.Lcd.setCursor(uint16_t x0, uint16_t y0);
*    M5.Lcd.setTextColor(uint16_t color);
*    M5.Lcd.setTextColor(uint16_t color, uint16_t backgroundcolor);
*    M5.Lcd.setTextSize(uint8_t size);
*    M5.Lcd.setTextWrap(boolean w);
x    M5.Lcd.printf();
*    M5.Lcd.print();
*    M5.Lcd.println();
*    M5.Lcd.drawCentreString(const char *string, int dX, int poY, int font);
*    M5.Lcd.drawRightString(const char *string, int dX, int poY, int font);
x    M5.Lcd.drawJpg(const uint8_t *jpg_data, size_t jpg_len, uint16_t x, uint16_t y);
x    M5.Lcd.drawJpgFile(fs::FS &fs, const char *path, uint16_t x, uint16_t y);
x    M5.Lcd.drawBmpFile(fs::FS &fs, const char *path, uint16_t x, uint16_t y);
*    M5.Lcd.progressBar(int x, int y, int w, int h, uint8_t val);
x    M5.Lcd.qrcode(const char *string, uint16_t x, uint16_t y, uint8_t width, uint8_t version);
*    M5.Lcd.qrcode(const String &string, uint16_t x, uint16_t y, uint8_t width, uint8_t version);

*    M5.Lcd.setRotation(int angle);
*    M5.Lcd.drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color);
*    M5.Lcd.drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color);
*********************************************/

void LcdString(String drawCommand);
String extractString(String drawCommand);
String extractStringP(String drawCommand);
uint8_t splitString(char* s, const char* separator, char** result, size_t result_size);

/*******************************************************/
// #define TFT_BLACK       0x0000      /*   0,   0,   0 */
// #define TFT_NAVY        0x000F      /*   0,   0, 128 */
// #define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
// #define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
// #define TFT_MAROON      0x7800      /* 128,   0,   0 */
// #define TFT_PURPLE      0x780F      /* 128,   0, 128 */
// #define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
// #define TFT_LIGHTGREY   0xC618      /* 192, 192, 192 */
// #define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
// #define TFT_BLUE        0x001F      /*   0,   0, 255 */
// #define TFT_GREEN       0x07E0      /*   0, 255,   0 */
// #define TFT_CYAN        0x07FF      /*   0, 255, 255 */
// #define TFT_RED         0xF800      /* 255,   0,   0 */
// #define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
// #define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
// #define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
// #define TFT_ORANGE      0xFDA0      /* 255, 180,   0 */
// #define TFT_GREENYELLOW 0xB7E0      /* 180, 255,   0 */
// #define TFT_PINK        0xFC9F

// #define BLACK               0x0000      /*   0,   0,   0 */
// #define NAVY                0x000F      /*   0,   0, 128 */
// #define DARKGREEN           0x03E0      /*   0, 128,   0 */
// #define DARKCYAN            0x03EF      /*   0, 128, 128 */
// #define MAROON              0x7800      /* 128,   0,   0 */
// #define PURPLE              0x780F      /* 128,   0, 128 */
// #define OLIVE               0x7BE0      /* 128, 128,   0 */
// #define LIGHTGREY           0xC618      /* 192, 192, 192 */
// #define DARKGREY            0x7BEF      /* 128, 128, 128 */
// #define BLUE                0x001F      /*   0,   0, 255 */
// #define GREEN               0x07E0      /*   0, 255,   0 */
// #define CYAN                0x07FF      /*   0, 255, 255 */
// #define RED                 0xF800      /* 255,   0,   0 */
// #define MAGENTA             0xF81F      /* 255,   0, 255 */
// #define YELLOW              0xFFE0      /* 255, 255,   0 */
// #define WHITE               0xFFFF      /* 255, 255, 255 */
// #define ORANGE              0xFD20      /* 255, 165,   0 */
// #define GREENYELLOW         0xAFE5      /* 173, 255,  47 */
// #define PINK                0xF81F
/*******************************************************/
uint16_t String2Color(String outChar);

#endif
