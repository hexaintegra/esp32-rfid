#include <WiFi.h>

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Mulai scan WiFi...");
  int n = WiFi.scanNetworks();
  Serial.printf("Ditemukan %d network\n", n);
  for (int i = 0; i < n; ++i) {
    String ssid = WiFi.SSID(i);
    int rssi = WiFi.RSSI(i);
    int enc = WiFi.encryptionType(i);
    String encStr;
    switch(enc) {
      case WIFI_AUTH_OPEN: encStr = "OPEN"; break;
      case WIFI_AUTH_WEP: encStr = "WEP"; break;
      case WIFI_AUTH_WPA_PSK: encStr = "WPA-PSK"; break;
      case WIFI_AUTH_WPA2_PSK: encStr = "WPA2-PSK"; break;
      case WIFI_AUTH_WPA_WPA2_PSK: encStr = "WPA/WPA2-PSK"; break;
      case WIFI_AUTH_WPA2_ENTERPRISE: encStr = "WPA2-ENTERPRISE"; break;
      case WIFI_AUTH_WPA3_PSK: encStr = "WPA3-PSK"; break;
      default: encStr = "OTHER";
    }
    Serial.printf("%d: %s (RSSI=%d) Enc=%s\n", i+1, ssid.c_str(), rssi, encStr.c_str());
  }
}

void loop() {
  // tidak perlu
}
