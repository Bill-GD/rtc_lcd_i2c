#ifndef NETWORK
#define NETWORK

#include <WiFi.h>
#include <Wire.h>

struct NetworkInfo {
  String ssid;
  int rssi;
  int channel;
};

NetworkInfo getAvailableNetwork();
void connect(String ssid, int channel);

#endif