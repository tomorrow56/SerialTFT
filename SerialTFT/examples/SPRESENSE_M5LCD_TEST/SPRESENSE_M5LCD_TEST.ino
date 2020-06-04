#include "SerialTFT.h"

SerialTFT lcd = SerialTFT();

void setup() {
  lcd.begin(921600);

  Serial.begin(115200);
  Serial.println("SPRESENSE-M5LCD Test");
  lcd.fillScreen(BLACK);
  lcd.qrcode("http://192.168.4.1", 10, 10, 200, 5);

}

int FSM = 0;

void loop() {
  delay(500);
  Serial.println(FSM);
  lcd.setBrightness(FSM * 20 + 10);
  lcd.setTextSize(2);
  lcd.setCursor(FSM * 5, FSM * 20);
  lcd.setTextColor(BLACK, GREEN);
  lcd.fillScreen(BLUE);
//  lcd.drawPixel(300, 20, RED);
//  lcd.drawLine(0, 0, 320, 240, GREENYELLOW);
//  lcd.drawLine(0, 240, 320, 0, ORANGE);
//  lcd.drawCircle(100, 100, 50, GREEN);
//  lcd.fillCircle(200, 200, 50, 0xFC9F);
//  lcd.fillCircleHelper(100, 100, 50, 1, 10, 0xFC9F);
//  lcd.drawTriangle(40, 10, 20, 40, 60, 40, RED);
//  lcd.fillTriangle(40, 10, 20, 40, 60, 40, 0xFC9F);
//  lcd.drawRoundRect(50, 50, 100, 50, 20, RED);
//  lcd.fillRoundRect(50, 50, 100, 50, 10, 0xFC9F);
  lcd.drawChar(random(10, 300), random(10, 220), 'M', RED, 0xFC9F, 5);
  lcd.drawChar(random(10, 300), random(10, 220), '5', BLUE, 0xFC9F, 4);
  lcd.drawChar(random(10, 300), random(10, 220), 'S', GREEN, RED, 3);
//  lcd.drawCircleHelper(100, 100, 30, 1, RED);
//  lcd.drawCircleHelper(100, 100, 30, 2, GREEN);
//  lcd.drawCircleHelper(100, 100, 30, 4, BLACK);
//  lcd.drawCircleHelper(100, 100, 30, 8, WHITE);
//  lcd.drawRect(20, 20, 100, 100, 0x7BEF);
//  lcd.fillRect(125, 20, 100, 100, GREEN);
//  lcd.setTextWrap(true);
//  lcd.drawCentreString("Cetering Test", 160, 120, 1);
//  lcd.drawRightString("Anchering Test", 160, 180, 1);
//  lcd.progressBar(10, 200, 200, 20, FSM * 10);
  lcd.print("SPRESENSE");
  lcd.println(" M5LCD Test");
  FSM++;
  if(FSM > 10){
    FSM = 0;
  }
}
