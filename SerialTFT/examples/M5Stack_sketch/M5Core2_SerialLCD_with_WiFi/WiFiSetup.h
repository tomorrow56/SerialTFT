#ifndef _wifisetup_h
#define _wifisetup_h

/********************************
* for Wifi Connection
*********************************/
#include <WiFi.h>
// https://github.com/zhouhan0126/DNSServer---esp32
#include <DNSServer.h>
// https://github.com/zhouhan0126/WebServer-esp32
#include <WebServer.h>
// https://github.com/zhouhan0126/WIFIMANAGER-ESP32
#include "WiFiManager.h"

#include <WiFiUdp.h>
#include <ArduinoOTA.h>

void AddFeatureString(String &S, const String F);
uint64_t GetChipid();
void WiFiMgrSetup(char WiFiAPname[]);
void OTASetup(char OTAHostname[]);

#endif
