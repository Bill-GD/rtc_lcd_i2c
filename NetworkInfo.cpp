#include "NetworkInfo.h"

NetworkInfo getAvailableNetwork() {
  Serial.println("Scanning for open network.");
  int count = WiFi.scanNetworks();
  NetworkInfo res = { "", 0 };
  if (count == 0) return res;

  for (int i = 0; i < count; i++) {
    delay(10);
    if (WiFi.encryptionType(i) != WIFI_AUTH_OPEN) continue;

    res.ssid = WiFi.SSID(i);
    res.rssi = WiFi.RSSI(i);
    res.channel = WiFi.channel(i);
    Serial.println("Found open network: " + res.ssid + " (" + (String)res.rssi + ")");
    break;
  }
  return res;
}

void connect(String ssid, int channel) {
  WiFi.begin(ssid, "", channel);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
  }
}
