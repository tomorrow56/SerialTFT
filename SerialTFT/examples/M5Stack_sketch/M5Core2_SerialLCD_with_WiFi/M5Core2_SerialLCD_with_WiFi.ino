#include <M5Core2.h>
// #include "M5StackUpdater.h"
#include "M5Lcd.h"
#include "WiFiSetup.h"
#include <HTTPClient.h>
//#include <ArduinoJson.h>

//#define debug
#define useOTA

char WiFiAPPrefix[] = "M5Core2-";
char WiFiAPname[256];

#ifdef useOTA
  char OTAHostPrefix[]= "M5Core2OTA-";
  char OTAHostname[256];
#endif

IPAddress ipadr;
boolean wifiStart = false;

/********************************
* for Wifi Service config
*********************************/
File myFile;
String cfgFile = "/M5core2wifi.cfg";

// IFTTT key and event triggers are  
const char* host_ifttt = "maker.ifttt.com";  // IFTTT Server URL
String makerKey = ""; // MakerKey of Webhooks
String Event[3];
String makerEvent;
String iftttData[3];

// Google static map
String mapkey = "";
String host_staticmap = "https://maps.googleapis.com/maps/api/staticmap?";
float lat, lng;
int accuracy;

// https://developers.google.com/maps/documentation/maps-static/start
// zoom level of Map
// 1: World
// 5: Landmass/continent
// 10: City
// 15: Streets
// 20: Buildings
int zoom = 12;

// Map type: roadmap, satellite, hybrid, terrain
String maptype = "hybrid";

uint8_t buff[320 * 220] = { 0 };

#define RST_PIN 19

void setup() {
//void M5Core2::begin(bool LCDEnable, bool SDEnable, bool SerialEnable, bool I2CEnable)
  M5.begin(true, true, true, true);

/*
  if(digitalRead(BUTTON_A_PIN) == 0){                // SD Update
     updateFromFS(SD);
     ESP.restart();
  }
*/

  // read IFTTT config from SD
  loadConfig(cfgFile);

//  Serial.begin(115200);
  Serial.println("M5SerialLCD Start...");
  displayStatus("M5SerialLCD Start...", GREEN);
  
  // Serial2.begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert)
  Serial2.begin(921600, SERIAL_8N1, 13, 14);

  // Reset Spresense
  pinMode(RST_PIN, OUTPUT);
  resetSpresense();
}

String readChar = "";
 
void loop() {
  M5.update();

  if(M5.BtnA.wasPressed()){
    Serial.println("M5.BtnA.wasPressed");
    Serial2.println("M5.BtnA.wasPressed");
    if(wifiStart == false){
      // Wifi and OTA setup
      uint64_t Chipid = GetChipid();
      sprintf(WiFiAPname, "%s%04X", WiFiAPPrefix, (uint16_t)Chipid);

      M5.Lcd.setTextSize(2);
      M5.Lcd.fillScreen(TFT_BLACK);
      M5.Lcd.setTextColor(CYAN);
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.printf("AP: %s\n", WiFiAPname);
      M5.Lcd.println("IP: 192.168.4.1");

      WiFiMgrSetup(WiFiAPname);

      displayStatus("Wifi Connected!", GREEN);
      displayStatus("SSID:" + (String)WiFi.SSID(), GREEN);
      ipadr = WiFi.localIP();
      displayStatus("IP adrs: " + (String)ipadr[0] + "." + (String)ipadr[1] + "." + (String)ipadr[2] + "." + (String)ipadr[3], GREEN);

      #ifdef useOTA
        sprintf(OTAHostname, "%s%04X", OTAHostPrefix, (uint16_t)Chipid);
        OTASetup(OTAHostname);
        displayStatus("OTA: " + (String)OTAHostname, GREEN);
      #endif

      wifiStart = true;
      delay(1000);
    }else{
      displayStatus("WiFi & OTA is enabled", GREEN);
      displayStatus("SSID:" + (String)WiFi.SSID(), GREEN);
      displayStatus("IP adrs: " + (String)ipadr[0] + "." + (String)ipadr[1] + "." + (String)ipadr[2] + "." + (String)ipadr[3], GREEN);

      #ifdef useOTA
        displayStatus("OTA: " + (String)OTAHostname, GREEN);
      #endif
    }
  }
  
  if(M5.BtnB.wasPressed()){
    Serial.println("M5.BtnB.wasPressed");
    Serial2.println("M5.BtnB.wasPressed");
  }

  if(M5.BtnC.wasPressed()){
    Serial.println("M5.BtnC.wasPressed");
    Serial2.println("M5.BtnC.wasPressed");
    resetSpresense();
  }

  if(wifiStart == true){
    #ifdef useOTA
      ArduinoOTA.handle();
    #endif
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
      /*****************
      * Draw LCD
      *****************/
      if(readChar.startsWith("M5.Lcd.")){
        LcdString(readChar.substring(7));
      }
      if(readChar.startsWith("M5.map(")){
        #ifdef debug
          M5.Lcd.println(readChar);
        #endif
        if(wifiStart == false){
          displayStatus("Press BtnA to start Wi-Fi", RED);
        }else{
          MapString(readChar.substring(7));
          displayMap();
          delay(10000);
        }
      }
      /*****************
      * Draw Google Map
      *****************/
      if(readChar.startsWith("M5.map(")){
        #ifdef debug
          M5.Lcd.println(readChar);
        #endif
        if(wifiStart == false){
          displayStatus("Press BtnA to start Wi-Fi", RED);
        }else{
          MapString(readChar.substring(7));
          displayMap();
          delay(10000);
        }
      }
      /*****************
      * Send IFTTT
      *****************/
      if(readChar.startsWith("M5.IFTTT(")){
        #ifdef debug
          M5.Lcd.println(readChar);
        #endif
        if(wifiStart == false){
          displayStatus("Press BtnA to start Wi-Fi", RED);
        }else{
          displayStatus("Send data to IFTTT", GREEN);
          iftttString(readChar.substring(9));
          sendIFTTT(makerEvent, iftttData[0], iftttData[1], iftttData[2]);
          delay(10000);
        }
      }
      readChar = "";
    }
  }
}

// #########################################################################
// Support functions
// #########################################################################
// Reset Spresense
void resetSpresense(){
  Serial.println("Reset SPRESENSE...");
  displayStatus("Reset SPRESENSE...", WHITE);
  digitalWrite(RST_PIN, LOW);
  delay(500);  
  digitalWrite(RST_PIN, HIGH);
  M5.Lcd.fillScreen(BLACK);
}

void displayStatus(String state, uint16_t color){
  M5.Lcd.setTextSize(2);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(color);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println(state);
  delay(500);
}

// #########################################################################
// load Service config from SD
// #########################################################################
void loadConfig(String cfgFile){

  String readLineDummy[100];
  String readLine = "";

  String eventDummy;
  String dataDummy;

  int i = 0;
  int lineCount;

  // open the file for reading:
  myFile = SD.open(cfgFile);

  if (myFile) {
    Serial.println(cfgFile + ":");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      readLine.concat(char(myFile.read()));
      if(readLine.endsWith("\n")){
        readLineDummy[i] = readLine.substring(0, readLine.indexOf("\n", 0) - 1);
        readLine = "";
        i++;
      }
    }
    lineCount = i;
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening " + cfgFile);
    M5.Lcd.setTextColor(TFT_RED, TFT_BLACK);
    M5.Lcd.setCursor(10, 25);
    M5.Lcd.print("error opening " + cfgFile);
  }

  for(i = 0; i < lineCount; i++){
    if(readLineDummy[i].length() > 0){
      eventDummy = readLineDummy[i].substring(0, readLineDummy[i].indexOf("=", 0) - 1);
      eventDummy.trim();
      dataDummy = readLineDummy[i].substring(readLineDummy[i].indexOf("=", 0) + 1, readLineDummy[i].length());
      dataDummy.replace("\"","");
      dataDummy.replace("'","");
      dataDummy.trim();

      if(eventDummy == "makerKey"){
        makerKey = dataDummy;
        Serial.println("makerKey = " + makerKey);
      }

      if(eventDummy == "Event0"){
        Event[0] = dataDummy;
        Serial.println("Event0 = " + Event[0]);
      }

      if(eventDummy == "Event1"){
        Event[1] = dataDummy;
        Serial.println("Event1 = " + Event[1]);
      }

      if(eventDummy == "Event2"){
        Event[2] = dataDummy;
        Serial.println("Event2 = " + Event[2]);
      }

      if(eventDummy == "mapkey"){
        mapkey = dataDummy;
        Serial.println("mapkey = " + mapkey);
      }

    }
  }
}

// #########################################################################
// send trigger and data to IFTTT
// #########################################################################
  void iftttString(String drawCommand){
  String outChar = "";
  char* result[4];
  size_t result_size;

  outChar = extractString(drawCommand);
  outChar.trim();

  result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
  Serial.println("");
  Serial.println("result_size: " + String(result_size));
  for (size_t i = 0; i < result_size; i++){
    Serial.println(result[i]);
  }

  makerEvent = Event[atoi(result[0])];
  iftttData[0] = result[1];
  iftttData[1] = result[2];
  iftttData[2] = result[3];
  
  #ifdef debug
    M5.Lcd.print("event =");
    M5.Lcd.println(makerEvent);
    M5.Lcd.print("value1 =");
    M5.Lcd.println(iftttData[0]);
    M5.Lcd.print("value2 =");
    M5.Lcd.println(iftttData[1]);
    M5.Lcd.print("value3 =");
    M5.Lcd.println(iftttData[2]);
  #endif
}

void sendIFTTT(String event, String value1, String value2, String value3){

  Serial.println("\nStarting connection to IFTTT...");

  WiFiClient client;

  if(!client.connect(host_ifttt, 80)){
    Serial.println("Connection failed!");
    return;
  }else{
    Serial.println("Connected to " + String(host_ifttt));

    // Make a HTTP request:
    String url = "/trigger/" + event + "/with/key/" + makerKey;
    url += "?value1=" + value1 + "&value2=" + value2 + "&value3=" + value3;

    client.println("POST " + url + " HTTP/1.1");
    client.print("Host: ");
    client.println(host_ifttt);

    Serial.println(url);
    delay(100);

    client.println("Connection: close");
    client.println();

    Serial.print("Waiting for response ");
    int count = 0;
    while (!client.available()){
      delay(50); //
      Serial.print(".");
      count++;
      if (count > 20 * 20){ // about 20s
        Serial.println("(send) failed!");
        return;
      }
    }

    // read incoming bytes from the server
    while (client.available()){
      char c = client.read();
      Serial.write(c);
    }

    // if the server's disconnected, stop the client:
    if (!client.connected()){
      Serial.println();
      Serial.println("disconnecting from IFTTT.");
      client.stop();
    }
  }
  
  client.stop();
  Serial.println("closing connection");
  Serial.println("");
}


// #########################################################################
// send location and get map data from Google Map
// #########################################################################
void MapString(String drawCommand){

  String outChar = "";
  char* result[4];
  size_t result_size;

  outChar = extractString(drawCommand);
  outChar.trim();

  result_size = splitString((char*)outChar.c_str(), ",", result, SIZE_OF_ARRAY(result));
  Serial.println("");
  Serial.println("result_size: " + String(result_size));
  for (size_t i = 0; i < result_size; i++){
    Serial.println(result[i]);
  }

  lat = String(result[0]).toFloat();
  lng = String(result[1]).toFloat();
  zoom = atoi(result[2]);
  maptype = result[3];
  
  #ifdef debug
    M5.Lcd.print("lat =");
    M5.Lcd.println(lat);
    M5.Lcd.print("log =");
    M5.Lcd.println(lng);
    M5.Lcd.print("zoom =");
    M5.Lcd.println(zoom);
    M5.Lcd.print("maptype =");
    M5.Lcd.println(maptype);
  #endif
}

void displayMap(){

  char pos[32];
  sprintf(pos, "%f,%f", lat, lng);
  String query = "center=" + String(pos) 
                        + "&size=320x220&maptype=" + maptype + "&zoom=" + String(zoom) + "&format=jpg-baseline"
                        + "&markers=size:mid|color:red|label:A|" + String(pos)
                        + "&key=" + mapkey;
  String url = host_staticmap + query;

  HTTPClient http;
  http.begin(url);

  sprintf(pos, "Lat:%.4f Lon:%.4f", lat, lng);
  displayStatus((String)pos, WHITE);

  int status_code = http.GET();
  if (status_code == 200) {
    int len = http.getSize();
    Serial.printf("[HTTP] size: %d\n", len);
    if (len > 0) {
      WiFiClient * stream = http.getStreamPtr();
      Serial.printf("[HTTP] strm ptr: %x\n", stream);
      // read all data from server
      uint8_t* p = buff;
      int l = len;
      while (http.connected() && (l > 0 || len == -1)) {
        // get available data size
        size_t size = stream->available();
        if (size) {
          int s = ((size > sizeof(buff)) ? sizeof(buff) : size);
          int c = stream->readBytes(p, s);
          p += c;
          Serial.printf("[HTTP] read: %d\n", c);
          if (l > 0) {
            l -= c;
          }
        }
      }
    }
    Serial.println("");
    Serial.println("[HTTP] connection closed.");
    M5.Lcd.drawJpg(buff, len, 0, 20);
    
  } else {
    Serial.println("[HTTP] Failed");
  }
  http.end();
}
