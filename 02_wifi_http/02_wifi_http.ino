#include <WiFi.h>
#include <HTTPClient.h>

// Ganti dengan SSID & password WiFi kamu
const char* ssid = "SSID";
const char* password = "PASSWORD";

// Endpoint tujuan
const char* serverUrl = "http://httpbin.org/get";

void setup() {
  Serial.begin(9600);

  // Koneksi ke WiFi
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Terhubung");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverUrl);

    Serial.printf("Request: %s\n", serverUrl);
    // Kirim request GET
    int httpResponseCode = http.GET();

    // Baca respons
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response Code: " + String(httpResponseCode));
      Serial.println("Response: " + response);
    } else {
      Serial.println("Error, kode: " + String(httpResponseCode));
    }

    http.end();
  } else {
    Serial.println("WiFi tidak terhubung");
  }

  delay(10000); // kirim tiap 10 detik
}
