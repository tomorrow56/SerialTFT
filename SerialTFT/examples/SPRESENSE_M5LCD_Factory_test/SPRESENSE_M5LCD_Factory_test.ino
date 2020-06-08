#include <LowPower.h>

#include <Wire.h>
#include "SerialTFT.h"

#include "DHT12.h"
#include "Seeed_BMP280.h"

#define PUSH_SHORT 1  //count of remove chattering
uint8_t count_low = 0;
#define RST_PIN 19

SerialTFT tft = SerialTFT();

DHT12 dht12;          //Preset scale CELSIUS and ID 0x5c.
BMP280 bmp280;

float pressure;
float temp;
float dht12_temp;
float dht12_humidity;

uint16_t AIN4;
uint16_t AIN5;

uint8_t X_pitch = 12;
uint8_t Y_pitch = 18;

uint16_t AIN4_MAX = 999; // ADC Value when 3.3V input
uint16_t AIN5_MAX = 1007; // ADC Value when 3.3V input

float AIN4_V;
float AIN5_V;


void setup() {
  Serial.begin(115200);
  Wire.begin();
  Serial.println("SPRESENSE-M5LCD Factory Test");

  // Initialize LowPower library
  LowPower.begin();

  pinMode(RST_PIN, INPUT);

  tft.begin(921600);
  tft.setRotation(1);

  tft.setTextSize(2);

  tft.setCursor(0, 10);
  tft.setTextColor(BLUE, WHITE);
  tft.println("SPRESENSE Grove Test");
  delay(500);

  tft.setTextSize(2);

  if(!bmp280.init()){
    Serial.println("BMP280 Device error!");
  }

  tft.fillScreen(BLACK);

  tft.setTextColor(GREEN);
  tft.setCursor(0, 10);
  tft.print("Temp_BMP280: ");
  tft.setCursor(0, 10 + Y_pitch * 1);
  tft.print("Temp_DHT12 : ");
  tft.setCursor(0, 10 + Y_pitch * 2);
  tft.print("Pressure   : ");
  tft.setCursor(0, 10 + Y_pitch * 3);
  tft.print("Humidity   : ");

  tft.setTextColor(RED);
  tft.setCursor(0, 10 + Y_pitch * 5);
  tft.print("AIN4       : ");
  tft.setCursor(0, 10 + Y_pitch * 6);
  tft.print("AIN5       : ");

  tft.setTextColor(WHITE, BLACK);

}

void loop() {

  //Scan RESET_PIN check
  if(digitalRead(RST_PIN) == LOW){  // remove chattering
    if(count_low <= PUSH_SHORT){
      count_low ++;
    }
  }else{
    count_low = 0;
  }

  if(count_low == PUSH_SHORT){
    Serial.print("Reboot...");
    tft.fillScreen(BLACK);
    tft.setCursor(0, 10);
    tft.print("Reboot...");
    delay(200);
    LowPower.reboot();
  }

  pressure = bmp280.getPressure();
  temp = bmp280.getTemperature();
  dht12_temp = dht12.readTemperature();
  dht12_humidity = dht12.readHumidity();

  Serial.print("Temp(BMP280): ");
  Serial.print(temp);
  Serial.println(" C"); // The unit for  Celsius because original arduino don't support speical symbols
  tft.setCursor(X_pitch * 13, 10);
  tft.print("      C");
  tft.setCursor(X_pitch * 13, 10);
  tft.print(String(temp));

  Serial.print("Temp(DHT12) : ");
  Serial.print(dht12_temp);
  Serial.println(" C"); // The unit for  Celsius because original arduino don't support speical symbols
  tft.setCursor(X_pitch * 13, 10 + Y_pitch * 1);
  tft.println("      C");
  tft.setCursor(X_pitch * 13, 10 + Y_pitch * 1);
  tft.print(String(dht12_temp));

  Serial.print("Pressure: ");
  Serial.print(pressure / 100);
  Serial.println(" hPa");
  tft.setCursor(X_pitch * 13, 10 + Y_pitch * 2);
  tft.print("       hPa");
  tft.setCursor(X_pitch * 13, 10 + Y_pitch * 2);
  tft.print(String(pressure / 100));

  Serial.print("Humidity: ");
  Serial.print(dht12_humidity);
  Serial.println(" %RH");
  tft.setCursor(X_pitch * 13, 10 + Y_pitch * 3);
  tft.print("      %RH");
  tft.setCursor(X_pitch * 13, 10 + Y_pitch * 3);
  tft.print(String(dht12_humidity));

  Serial.println("\n");

  AIN4 = analogRead(A2);
  AIN5 = analogRead(A3);
  AIN4_V = 3.3 * ((float)AIN4/AIN4_MAX);
  AIN5_V = 3.3 * ((float)AIN5/AIN5_MAX);
  
  Serial.println("AIN4=" + String(AIN4));
  Serial.println("AIN5=" + String(AIN5));
  tft.setCursor(X_pitch * 13, 10 + Y_pitch * 5);
  tft.print("     V");
  tft.setCursor(X_pitch * 13, 10 + Y_pitch * 5);
  tft.print(String(AIN4_V));
  tft.setCursor(X_pitch * 13, 10 + Y_pitch * 6);
  tft.print("     V");
  tft.setCursor(X_pitch * 13, 10 + Y_pitch * 6);
  tft.println(String(AIN5_V));

  delay(100);

}
