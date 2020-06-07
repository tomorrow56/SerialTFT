#include <Wire.h>
#include "SerialTFT.h"

#include "DHT12.h"
#include "Seeed_BMP280.h"

SerialTFT tft = SerialTFT();

DHT12 dht12;          //Preset scale CELSIUS and ID 0x5c.
BMP280 bmp280;

float pressure;
float temp;
float dht12_temp;
float dht12_humidity;

uint16_t AIN4;
uint16_t AIN5;

uint16_t AIN4_MAX = 999; // ADC Value when 3.3V input
uint16_t AIN5_MAX = 1007; // ADC Value when 3.3V input

float AIN4_V;
float AIN5_V;


void setup() {
  Serial.begin(115200);
  Wire.begin();
  Serial.println("SPRESENSE-M5LCD Factory Test");

  tft.begin(921600);
  tft.setRotation(1);

  tft.setTextSize(3);

  tft.setCursor(0, 10);
  tft.setTextColor(BLUE, WHITE);
  tft.println("SPRESENSE Grove Test");
  delay(1000);

  tft.setTextSize(2);

  if(!bmp280.init()){
    Serial.println("BMP280 Device error!");
  }

}

void loop() {

  tft.fillScreen(BLACK);
  tft.setCursor(0, 10);
  tft.setTextColor(GREEN);

  pressure = bmp280.getPressure();
  temp = bmp280.getTemperature();
  dht12_temp = dht12.readTemperature();
  dht12_humidity = dht12.readHumidity();

  Serial.print("Temp(BMP280): ");
  Serial.print(temp);
  Serial.println(" C"); // The unit for  Celsius because original arduino don't support speical symbols
  tft.print("Temp_BMP280: ");
  tft.print(String(temp));
  tft.println(" C");

  Serial.print("Temp(DHT12) : ");
  Serial.print(dht12_temp);
  Serial.println(" C"); // The unit for  Celsius because original arduino don't support speical symbols
  tft.print("Temp_DHT12 : ");
  tft.print(String(dht12_temp));
  tft.println(" C");

  Serial.print("Pressure: ");
  Serial.print(pressure / 100);
  Serial.println(" hPa");
  tft.print("Pressure   : ");
  tft.print(String(pressure / 100));
  tft.println(" hPa");

  Serial.print("Humidity: ");
  Serial.print(dht12_humidity);
  Serial.println(" %RH");
  tft.print("Humidity   : ");
  tft.print(String(dht12_humidity));
  tft.println(" %RH");

  Serial.println("\n");
  tft.println();

  tft.setTextColor(RED);

  AIN4 = analogRead(A2);
  AIN5 = analogRead(A3);
  AIN4_V = 3.3 * ((float)AIN4/AIN4_MAX);
  AIN5_V = 3.3 * ((float)AIN5/AIN5_MAX);
  
  Serial.println("AIN4=" + String(AIN4));
  Serial.println("AIN5=" + String(AIN5));
  tft.println("AIN4= " + String(AIN4_V) + " V");
  tft.println("AIN5= " + String(AIN5_V) + " V");

  delay(1000);

}
