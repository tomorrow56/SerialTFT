#include <M5Stack.h>
#include "M5StackUpdater.h"

#define SIZE_OF_ARRAY(array)    (sizeof(array)/sizeof(array[0]))

//#define debug

#define RST_PIN 13

void setup() {
  M5.begin();

  if(digitalRead(BUTTON_A_PIN) == 0){                // SD Update
     updateFromFS(SD);
     ESP.restart();
  }

//  Serial.begin(115200);
  Serial.println("Hello!");
  M5.Lcd.println("Hello!");
  
  // Serial2.begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert)
  Serial2.begin(921600, SERIAL_8N1, 16, 17);

  // Reset Spresense
  pinMode(RST_PIN, OUTPUT);
  digitalWrite(RST_PIN, LOW);
  delay(500);  
  digitalWrite(RST_PIN, HIGH);

}

String readChar = "";
 
void loop() {
  M5.update();

  if(M5.BtnC.wasPressed()){
    Serial.println("Reset SPRESENSE...");
    digitalWrite(RST_PIN, LOW);
  }

  if(M5.BtnC.wasReleased()){
    digitalWrite(RST_PIN, HIGH);
  }

  if(Serial2.available()) {
    int ch = Serial2.read();
    #ifdef debug
      Serial.write(ch);
    #endif
    if(ch == 0x0a){
    }else{
      readChar = readChar + (char)ch;
    }
    if(ch == 0x0d){
      if(readChar.startsWith("M5.Lcd.")){
        LcdString(readChar.substring(7));
      }
      readChar = "";
    }
  }
}

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
    M5.Lcd.drawJpgFile(fs::FS &fs, const char *path, uint16_t x, uint16_t y);
    M5.Lcd.drawBmpFile(fs::FS &fs, const char *path, uint16_t x, uint16_t y);
*    M5.Lcd.progressBar(int x, int y, int w, int h, uint8_t val);
x    M5.Lcd.qrcode(const char *string, uint16_t x, uint16_t y, uint8_t width, uint8_t version);
*    M5.Lcd.qrcode(const String &string, uint16_t x, uint16_t y, uint8_t width, uint8_t version);

    M5.Lcd.setRotation(int angle);
    M5.Lcd.drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color);
    M5.Lcd.drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color);
*********************************************/

void LcdString(String drawCommand){
  String outChar = "";
  if(drawCommand.startsWith("setBrightness(")){
    uint8_t brightness;

    outChar = drawCommand.substring(13);
    outChar.trim();
    brightness = extractString(outChar).toInt();

    M5.Lcd.setBrightness(brightness);

  }else if(drawCommand.startsWith("setRotation(")){
    int angle;

    outChar = drawCommand.substring(11);
    outChar.trim();
    angle = extractString(outChar).toInt();

    M5.Lcd.setRotation(angle);

  }else if(drawCommand.startsWith("drawPixel(")){
    char* result[3];
    size_t result_size;

    uint16_t x;
    uint16_t y;
    uint16_t lcdColor;

    outChar = drawCommand.substring(9);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    x = atoi(result[0]);
    y = atoi(result[1]);
    lcdColor = String2Color((String)result[2]);

    M5.Lcd.drawPixel(x, y, lcdColor);

  }else if(drawCommand.startsWith("drawFastHLine(")){
    char* result[4];
    size_t result_size;

    uint32_t x;
    uint32_t y;
    uint32_t w;
    uint32_t lcdColor;

    outChar = drawCommand.substring(13);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    x = atoi(result[0]);
    y = atoi(result[1]);
    w = atoi(result[2]);
    lcdColor = String2Color((String)result[3]);

    M5.Lcd.drawFastHLine(x, y, w, lcdColor);

  }else if(drawCommand.startsWith("drawFastVLine(")){
    char* result[4];
    size_t result_size;

    uint32_t x;
    uint32_t y;
    uint32_t h;
    uint32_t lcdColor;

    outChar = drawCommand.substring(13);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    x = atoi(result[0]);
    y = atoi(result[1]);
    h = atoi(result[2]);
    lcdColor = String2Color((String)result[3]);

    M5.Lcd.drawFastVLine(x, y, h, lcdColor);

  }else if(drawCommand.startsWith("drawLine(")){
    char* result[5];
    size_t result_size;

    uint16_t x0;
    uint16_t y0;
    uint16_t x1;
    uint16_t y1;
    uint16_t lcdColor;

    outChar = drawCommand.substring(8);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    x0 = atoi(result[0]);
    y0 = atoi(result[1]);
    x1 = atoi(result[2]);
    y1 = atoi(result[3]);
    lcdColor = String2Color((String)result[4]);

    M5.Lcd.drawLine(x0, y0, x1, y1, lcdColor);

  }else if(drawCommand.startsWith("drawRect(")){
    char* result[5];
    size_t result_size;

    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
    uint16_t lcdColor;

    outChar = drawCommand.substring(8);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    x = atoi(result[0]);
    y = atoi(result[1]);
    w = atoi(result[2]);
    h = atoi(result[3]);
    lcdColor = String2Color((String)result[4]);

    M5.Lcd.drawRect(x, y, w, h, lcdColor);

  }else if(drawCommand.startsWith("fillRect(")){
    char* result[5];
    size_t result_size;

    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
    uint16_t lcdColor;

    outChar = drawCommand.substring(8);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    x = atoi(result[0]);
    y = atoi(result[1]);
    w = atoi(result[2]);
    h = atoi(result[3]);
    lcdColor = String2Color((String)result[4]);

    M5.Lcd.fillRect(x, y, w, h, lcdColor);

  }else if(drawCommand.startsWith("fillScreen(")){
    uint16_t lcdColor = 0;

    outChar = drawCommand.substring(10);
    outChar = extractString(outChar);

    M5.Lcd.fillScreen(String2Color(outChar));

  }else if(drawCommand.startsWith("drawCircle(")){
    char* result[4];
    size_t result_size;

    uint16_t x0;
    uint16_t y0;
    uint16_t r;
    uint16_t lcdColor;

    outChar = drawCommand.substring(10);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    x0 = atoi(result[0]);
    y0 = atoi(result[1]);
    r  = atoi(result[2]);
    lcdColor = String2Color((String)result[3]);

    M5.Lcd.drawCircle(x0, y0, r, lcdColor);

  }else if(drawCommand.startsWith("drawCircleHelper(")){
    char* result[5];
    size_t result_size;

    uint16_t x0;
    uint16_t y0;
    uint16_t r;
    uint8_t cornername;
    uint16_t lcdColor;

    outChar = drawCommand.substring(16);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    x0 = atoi(result[0]);
    y0 = atoi(result[1]);
    r  = atoi(result[2]);
    cornername = atoi(result[3]);
    lcdColor = String2Color((String)result[4]);

    M5.Lcd.drawCircleHelper(x0, y0, r, cornername, lcdColor);

  }else if(drawCommand.startsWith("fillCircle(")){
    char* result[4];
    size_t result_size;

    uint16_t x0;
    uint16_t y0;
    uint16_t r;
    uint16_t lcdColor;

    outChar = drawCommand.substring(10);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    x0 = atoi(result[0]);
    y0 = atoi(result[1]);
    r  = atoi(result[2]);
    lcdColor = String2Color((String)result[3]);

    M5.Lcd.fillCircle(x0, y0, r, lcdColor);

  }else if(drawCommand.startsWith("fillCircleHelper(")){
    char* result[6];
    size_t result_size;

    uint16_t x0;
    uint16_t y0;
    uint16_t r;
    uint8_t cornername;
    int16_t delta;
    uint16_t lcdColor;

    outChar = drawCommand.substring(16);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    x0 = atoi(result[0]);
    y0 = atoi(result[1]);
    r  = atoi(result[2]);
    cornername = atoi(result[3]);
    delta = atoi(result[4]);
    lcdColor = String2Color((String)result[5]);

    M5.Lcd.fillCircleHelper(x0, y0, r, cornername, delta, lcdColor);

  }else if(drawCommand.startsWith("drawTriangle(")){
    char* result[7];
    size_t result_size;

    uint16_t x0;
    uint16_t y0;
    uint16_t x1;
    uint16_t y1;
    uint16_t x2;
    uint16_t y2;
    uint16_t lcdColor;

    outChar = drawCommand.substring(12);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    x0 = atoi(result[0]);
    y0 = atoi(result[1]);
    x1 = atoi(result[2]);
    y1 = atoi(result[3]);
    x2 = atoi(result[4]);
    y2 = atoi(result[5]);
    lcdColor = String2Color((String)result[6]);

    M5.Lcd.drawTriangle(x0, y0, x1, y1, x2, y2, lcdColor);

  }else if(drawCommand.startsWith("fillTriangle(")){
    char* result[7];
    size_t result_size;

    uint16_t x0;
    uint16_t y0;
    uint16_t x1;
    uint16_t y1;
    uint16_t x2;
    uint16_t y2;
    uint16_t lcdColor;

    outChar = drawCommand.substring(12);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    x0 = atoi(result[0]);
    y0 = atoi(result[1]);
    x1 = atoi(result[2]);
    y1 = atoi(result[3]);
    x2 = atoi(result[4]);
    y2 = atoi(result[5]);
    lcdColor = String2Color((String)result[6]);

    M5.Lcd.fillTriangle(x0, y0, x1, y1, x2, y2, lcdColor);

  }else if(drawCommand.startsWith("drawRoundRect(")){
    char* result[6];
    size_t result_size;

    uint16_t x0;
    uint16_t y0;
    uint16_t w;
    uint16_t h;
    uint16_t radius;
    uint16_t lcdColor;

    outChar = drawCommand.substring(13);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    x0 = atoi(result[0]);
    y0 = atoi(result[1]);
    w = atoi(result[2]);
    h = atoi(result[3]);
    radius = atoi(result[4]);
    lcdColor = String2Color((String)result[5]);

    M5.Lcd.drawRoundRect(x0, y0, w, h, radius, lcdColor);

  }else if(drawCommand.startsWith("fillRoundRect(")){
    char* result[6];
    size_t result_size;

    uint16_t x0;
    uint16_t y0;
    uint16_t w;
    uint16_t h;
    uint16_t radius;
    uint16_t lcdColor;

    outChar = drawCommand.substring(13);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    x0 = atoi(result[0]);
    y0 = atoi(result[1]);
    w = atoi(result[2]);
    h = atoi(result[3]);
    radius = atoi(result[4]);
    lcdColor = String2Color((String)result[5]);

    M5.Lcd.fillRoundRect(x0, y0, w, h, radius, lcdColor);

  }else if(drawCommand.startsWith("drawChar(")){
    char* result[6];
    size_t result_size;

    uint16_t x;
    uint16_t y;
    char c;
    uint16_t lcdColor;
    uint16_t bg;
    uint8_t size;

    outChar = drawCommand.substring(8);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    x = atoi(result[0]);
    y = atoi(result[1]);
    c = result[2][0];
    lcdColor = String2Color((String)result[3]);
    bg = String2Color((String)result[4]);
    size = atoi(result[5]);

    M5.Lcd.drawChar(x, y, c, lcdColor, bg, size);

  }else if(drawCommand.startsWith("setCursor(")){
    char* result[2];
    size_t result_size;

    int posiX;
    int posiY;

    outChar = drawCommand.substring(9);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    posiX = atoi(result[0]);
    posiY = atoi(result[1]);

    M5.Lcd.setCursor(posiX, posiY);

  }else if(drawCommand.startsWith("setTextColor(")){
    char* result[2];
    size_t result_size;

    uint16_t foreColor;
    uint16_t backColor;

    outChar = drawCommand.substring(12);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    if(result_size == 2){
      foreColor = String2Color((String)result[0]);
      backColor = String2Color((String)result[1]);

      M5.Lcd.setTextColor(foreColor, backColor);
    }else if(result_size == 1){
      foreColor = String2Color(result[0]);
      M5.Lcd.setTextColor(foreColor);
    }else{
    }

  }else if(drawCommand.startsWith("setTextSize(")){
    uint8_t textSize;
    outChar = drawCommand.substring(11);
    outChar.trim();
    textSize = extractString(outChar).toInt();
    M5.Lcd.setTextSize(textSize);

  }else if(drawCommand.startsWith("setTextWrap(")){
    boolean w;
    outChar = drawCommand.substring(11);
    outChar.trim();
    w = extractString(outChar).toInt();
    M5.Lcd.setTextWrap(w);

  }else if(drawCommand.startsWith("println(")){
    outChar = drawCommand.substring(7);
    M5.Lcd.println(extractStringP(outChar));

  }else if(drawCommand.startsWith("print(")){
    outChar = drawCommand.substring(5);
    M5.Lcd.print(extractStringP(outChar));

  }else if(drawCommand.startsWith("drawCentreString(")){
    char* result[4];
    size_t result_size;

    char *string;
    int dX;
    int poY;
    int font;

    outChar = drawCommand.substring(16);
    outChar = extractStringP(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    string = result[0];
    dX = atoi(result[1]);
    poY = atoi(result[2]);
    font = atoi(result[3]);

    M5.Lcd.drawCentreString(string, dX, poY, font);

  }else if(drawCommand.startsWith("drawRightString(")){
    char* result[4];
    size_t result_size;

    char *string;
    int dX;
    int poY;
    int font;

    outChar = drawCommand.substring(15);
    outChar = extractStringP(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    string = result[0];
    dX = atoi(result[1]);
    poY = atoi(result[2]);
    font = atoi(result[3]);

    M5.Lcd.drawRightString(string, dX, poY, font);

  }else if(drawCommand.startsWith("progressBar(")){
    char* result[5];
    size_t result_size;

    int x;
    int y;
    int w;
    int h;
    uint8_t val;

    outChar = drawCommand.substring(11);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    x = atoi(result[0]);
    y = atoi(result[1]);
    w = atoi(result[2]);
    h = atoi(result[3]);
    val = atoi(result[4]);

    M5.Lcd.progressBar(x, y, w, h, val);

  }else if(drawCommand.startsWith("qrcode(")){
    char* result[5];
    size_t result_size;

    String string;
    uint16_t x;
    uint16_t y;
    uint8_t width;
    uint8_t version;  //2(32byte), 5(106byte), 15(520byte)

    outChar = drawCommand.substring(6);
    outChar = extractString(outChar);
    outChar.trim();

    result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
    #ifdef debug
      Serial.println("");
      Serial.println("result_size: " + String(result_size));
      for (size_t i = 0; i < result_size; i++){
        Serial.println(result[i]);
      }
    #endif

    string = String(result[0]);
    x = atoi(result[1]);
    y = atoi(result[2]);
    width = atoi(result[3]);
    version = atoi(result[4]);

    M5.Lcd.qrcode(string, x, y, width, version);

  }
}

/********************************************
* M5.LCD sub function
*********************************************/

String extractString(String drawCommand){
  String outChar = drawCommand;
  outChar.replace("(","");
  outChar.replace(")","");
  outChar.replace(" ","");
  outChar.replace("\"","");
  outChar.replace("'","");
  return outChar;
}

String extractStringP(String drawCommand){
  String outChar = drawCommand;
  outChar.replace("(","");
  outChar.replace(")","");
  outChar.trim();
  outChar.replace("\"","");
  outChar.replace("'","");
  return outChar;
}

uint8_t splitString(char* s, const char* separator, char** result, size_t result_size){
  assert(s != NULL);
  assert(separator != NULL);
  assert(result != NULL);
  assert(result_size > 0);

  size_t s_len = strlen(s);
  size_t start = 0;
  size_t end = 0;
  size_t i = 0;

  do{
    end = start + strcspn(&s[start], separator); 
    s[end] = '\0';

    assert(i < result_size);
    result[i] = &s[start];
    ++i;

    start = end + 1;

  }while (start <= s_len);
  return i;
}


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

uint16_t String2Color(String outChar){
  uint16_t lcdColor;
  outChar.trim();
  if(outChar.startsWith("BLACK")){
    lcdColor = BLACK;
  }else if(outChar.startsWith("NAVY")){
    lcdColor = NAVY;
  }else if(outChar.startsWith("DARKGREEN")){
    lcdColor = DARKGREEN;
  }else if(outChar.startsWith("DARKCYAN")){
    lcdColor = DARKCYAN;
  }else if(outChar.startsWith("MAROON")){
    lcdColor = MAROON;
  }else if(outChar.startsWith("PURPLE")){
    lcdColor = PURPLE;
  }else if(outChar.startsWith("OLIVE")){
    lcdColor = OLIVE;
  }else if(outChar.startsWith("LIGHTGREY")){
    lcdColor = LIGHTGREY;
  }else if(outChar.startsWith("DARKGREY")){
    lcdColor = DARKGREY;
  }else if(outChar.startsWith("BLUE")){
    lcdColor = BLUE;
  }else if(outChar.startsWith("GREENYELLOW")){
    lcdColor = GREENYELLOW;
  }else if(outChar.startsWith("GREEN")){
    lcdColor = GREEN;
  }else if(outChar.startsWith("CYAN")){
    lcdColor = CYAN;
  }else if(outChar.startsWith("RED")){
    lcdColor = RED;
  }else if(outChar.startsWith("MAGENTA")){
    lcdColor = MAGENTA;
  }else if(outChar.startsWith("YELLOW")){
    lcdColor = YELLOW;
  }else if(outChar.startsWith("WHITE")){
    lcdColor = WHITE;
  }else if(outChar.startsWith("ORANGE")){
    lcdColor = ORANGE;
  }else if(outChar.startsWith("PINK")){
    lcdColor = PINK;
  }else if(outChar.startsWith("TFT_BLACK")){
    lcdColor = TFT_BLACK;
  }else if(outChar.startsWith("TFT_NAVY")){
    lcdColor = TFT_NAVY;
  }else if(outChar.startsWith("TFT_DARKGREEN")){
    lcdColor = TFT_DARKGREEN;
  }else if(outChar.startsWith("TFT_DARKCYAN")){
    lcdColor = TFT_DARKCYAN;
  }else if(outChar.startsWith("TFT_MAROON")){
    lcdColor = TFT_MAROON;
  }else if(outChar.startsWith("TFT_PURPLE")){
    lcdColor = TFT_PURPLE;
  }else if(outChar.startsWith("TFT_OLIVE")){
    lcdColor = TFT_OLIVE;
  }else if(outChar.startsWith("TFT_LIGHTGREY")){
    lcdColor = TFT_LIGHTGREY;
  }else if(outChar.startsWith("TFT_DARKGREY")){
    lcdColor = TFT_DARKGREY;
  }else if(outChar.startsWith("TFT_BLUE")){
    lcdColor = TFT_BLUE;
  }else if(outChar.startsWith("TFT_GREENYELLOW")){
    lcdColor = TFT_GREENYELLOW;
  }else if(outChar.startsWith("TFT_GREEN")){
    lcdColor = TFT_GREEN;
  }else if(outChar.startsWith("TFT_CYAN")){
    lcdColor = TFT_CYAN;
  }else if(outChar.startsWith("TFT_RED")){
    lcdColor = TFT_RED;
  }else if(outChar.startsWith("TFT_MAGENTA")){
    lcdColor = TFT_MAGENTA;
  }else if(outChar.startsWith("TFT_YELLOW")){
    lcdColor = TFT_YELLOW;
  }else if(outChar.startsWith("TFT_WHITE")){
    lcdColor = TFT_WHITE;
  }else if(outChar.startsWith("TFT_ORANGE")){
    lcdColor = TFT_ORANGE;
  }else if(outChar.startsWith("TFT_PINK")){
    lcdColor = TFT_PINK;
  }else{
    lcdColor = strtol(outChar.c_str(), NULL, 16);
  }

  return lcdColor;
}

