/*****************************************
* SerialTFT Driver for M5LCD
* Copyright (C), 2020, @tomorrow56 (a.k.a. ThousanDIY)
*****************************************/

#include "SerialTFT.h"

SerialTFT::SerialTFT(){
}

SerialTFT::~SerialTFT(){
}

int16_t SerialTFT::height(){
  return HEIGHT;
}

int16_t SerialTFT::width(){
  return WIDTH;
}

void SerialTFT::begin(int baud){
  Serial2.begin(baud);
  Serial2.flush();
  delay(50);
}

void SerialTFT::setBrightness(int8_t brightness){
  Serial2.println("M5.Lcd.setBrightness(" + String(brightness) + ")");
}

void SerialTFT::drawPixel(int16_t x, int16_t y, uint16_t color){
  Serial2.println("M5.Lcd.drawPixel(" + String(x) + "," + String(y) + "," + String(color, HEX) + ")");
  delay(comInterval / 4);
}

void SerialTFT::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color){
  Serial2.println("M5.Lcd.drawLine(" + String(x0) + "," + String(y0) + "," + String(x1) + "," + String(y1) + "," + String(color, HEX) + ")");
  delay(comInterval / 4);
}

void SerialTFT::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color){
  Serial2.println("M5.Lcd.drawRect(" + String(x) + "," + String(y) + "," + String(w) + "," + String(h) + "," + String(color, HEX) + ")");
  delay(comInterval / 2);
}

void SerialTFT::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color){
  Serial2.println("M5.Lcd.fillRect(" + String(x) + "," + String(y) + "," + String(w) + "," + String(h) + "," + String(color, HEX) + ")");
  delay(comInterval);
}

void SerialTFT::fillScreen(uint16_t color){
  Serial2.println("M5.Lcd.fillScreen(" + String(color, HEX) + ")");
  delay(comInterval);
}

void SerialTFT::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color){
  Serial2.println("M5.Lcd.drawCircle(" + String(x0) + "," + String(y0) + "," + String(r) + "," + String(color, HEX) + ")");
  delay(comInterval / 2);
}

void SerialTFT::drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color){
  Serial2.println("M5.Lcd.drawCircleHelper(" + String(x0) + "," + String(y0) + "," + String(r) + "," + String(cornername) + "," + String(color, HEX) + ")");
  delay(comInterval / 2);
}

void SerialTFT::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color){
  Serial2.println("M5.Lcd.fillCircle(" + String(x0) + "," + String(y0) + "," + String(r) + "," + String(color, HEX) + ")");
  delay(comInterval);
}

void SerialTFT::fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color){
  Serial2.println("M5.Lcd.fillCircleHelper(" + String(x0) + "," + String(y0) + "," + String(r) + "," + String(cornername) + "," + String(delta) + "," + String(color, HEX) + ")");
  delay(comInterval);
}

void SerialTFT::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color){
  Serial2.println("M5.Lcd.drawTriangle(" + String(x0) + "," + String(y0) + "," + String(x1) + "," + String(y1) + "," + String(x2) + "," + String(y2) + "," + String(color, HEX) + ")");
  delay(comInterval / 2);
}

void SerialTFT::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color){
  Serial2.println("M5.Lcd.fillTriangle(" + String(x0) + "," + String(y0) + "," + String(x1) + "," + String(y1) + "," + String(x2) + "," + String(y2) + "," + String(color, HEX) + ")");
  delay(comInterval);
}

void SerialTFT::drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color){
  Serial2.println("M5.Lcd.drawRoundRect(" + String(x0) + "," + String(y0) + "," + String(w) + "," + String(h) + "," + String(radius) + "," + String(color, HEX) + ")");
  delay(comInterval / 2);
}

void SerialTFT::fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color){
  Serial2.println("M5.Lcd.fillRoundRect(" + String(x0) + "," + String(y0) + "," + String(w) + "," + String(h) + "," + String(radius) + "," + String(color, HEX) + ")");
  delay(comInterval);
}

void SerialTFT::drawChar(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg, uint8_t size){
  Serial2.println("M5.Lcd.drawChar(" + String(x) + "," + String(y) + "," + String(c) + "," + String(color, HEX) + "," + String(bg, HEX) + "," + String(size) + ")");
  delay(comInterval / 2);
}

void SerialTFT::setCursor(uint16_t x0, uint16_t y0){
  Serial2.println("M5.Lcd.setCursor(" + String(x0) + "," + String(y0) + ")");
  delay(comInterval / 4);
}

void SerialTFT::setTextColor(uint16_t color){
  Serial2.println("M5.Lcd.setTextColor(" + String(color, HEX) + ")");
  delay(comInterval / 4);
}

void SerialTFT::setTextColor(uint16_t color, uint16_t backgroundcolor){
  Serial2.println("M5.Lcd.setTextColor(" + String(color, HEX) + "," + String(backgroundcolor, HEX) + ")");
  delay(comInterval / 4);
}

void SerialTFT::setTextSize(uint8_t size){
  Serial2.println("M5.Lcd.setTextSize(" + String(size) + ")");
  delay(comInterval / 4);
}

void SerialTFT::setTextWrap(boolean w){
  Serial2.println("M5.Lcd.setTextWrap(" + String(w) + ")");
  delay(comInterval / 4);
}

//  void SerialTFT::printf();

void SerialTFT::print(String text){
  Serial2.println("M5.Lcd.print(\"" + text + "\")");
  delay(comInterval / 2);
}

void SerialTFT::println(String text){
  Serial2.println("M5.Lcd.println(\"" + text + "\")");
  delay(comInterval / 2);
}

void SerialTFT::println(){
  Serial2.println("M5.Lcd.println(\"\")");
  delay(comInterval / 2);
}

void SerialTFT::drawCentreString(String text, int dX, int poY, int font){
  Serial2.println("M5.Lcd.drawCentreString(\"" + text + "\"," + String(dX) + "," + String(poY) + "," + String(font) + ")");
  delay(comInterval / 4);
}

void SerialTFT::drawRightString(String text, int dX, int poY, int font){
  Serial2.println("M5.Lcd.drawRightString(\"" + text + "\"," + String(dX) + "," + String(poY) + "," + String(font) + ")");
  delay(comInterval / 4);
}

//    void SerialTFT::drawJpgFile(fs::FS &fs, const char *path, uint16_t x, uint16_t y);
//    void SerialTFT::drawBmpFile(fs::FS &fs, const char *path, uint16_t x, uint16_t y);

void SerialTFT::progressBar(int x, int y, int w, int h, uint8_t val){
  Serial2.println("M5.Lcd.progressBar(" + String(x) + "," + String(y) + "," + String(w) + "," + String(h) + "," + String(val) + ")");
  delay(comInterval / 2);
}

void SerialTFT::qrcode(String text, uint16_t x, uint16_t y, uint8_t width, uint8_t version){
  Serial2.println("M5.Lcd.qrcode(\"" + text + "\"," + String(x) + "," + String(y) + "," + String(width) + "," + String(version) + ")");
  delay(comInterval * 2);
}


void SerialTFT::setRotation(int angle){
  Serial2.println("M5.Lcd.setRotation(" + String(angle) + ")");
}


/***************************************************************************************
** Function name:           color565
** Description:             convert three 8 bit RGB levels to a 16 bit colour value
***************************************************************************************/
uint16_t SerialTFT::color565(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}


/***************************************************************************************
** Function name:           color16to8
** Description:             convert 16 bit colour to an 8 bit 332 RGB colour value
***************************************************************************************/
uint8_t SerialTFT::color16to8(uint16_t c)
{
  return ((c & 0xE000)>>8) | ((c & 0x0700)>>6) | ((c & 0x0018)>>3);
}


/***************************************************************************************
** Function name:           color8to16
** Description:             convert 8 bit colour to a 16 bit 565 colour value
***************************************************************************************/
uint16_t SerialTFT::color8to16(uint8_t color)
{
  uint8_t  blue[] = {0, 11, 21, 31}; // blue 2 to 5 bit colour lookup table
  uint16_t color16 = 0;

  //        =====Green=====     ===============Red==============
  color16  = (color & 0x1C)<<6 | (color & 0xC0)<<5 | (color & 0xE0)<<8;
  //        =====Green=====    =======Blue======
  color16 |= (color & 0x1C)<<3 | blue[color & 0x03];

  return color16;
}


void SerialTFT::drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color)
{
  Serial2.println("M5.Lcd.drawFastHLine(" + String(x) + "," + String(y) + "," + String(w) + "," + String(color, HEX) + ")");
  delay(comInterval / 4);
}


void SerialTFT::drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color)
{
  Serial2.println("M5.Lcd.drawFastVLine(" + String(x) + "," + String(y) + "," + String(h) + "," + String(color, HEX) + ")");
  delay(comInterval / 4);
}

