#include <WiFi.h>
#include <HTTPClient.h>

// Ganti dengan SSID & password WiFi kamu
const char* ssid = "SSID";
const char* password = "PASSWORD";

// Endpoint tujuan
const char* serverUrl = "https://xxxxxxxxxxxxx.supabase.co/rest/v1/absensi";
const char* apikey = "sb_secret_xxxxxxxxxxxxxxxxxxxxxxx";

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

    // Tambahkan header
    http.addHeader("Content-Type", "application/json");
    http.addHeader("apikey", apikey);

    // Data JSON untuk dikirim
    String requestBody = "{\"kode_rfid\":\"1234\"}";

    Serial.printf("Kirim data ke server: %s\n", serverUrl);
    // Kirim request POST
    int httpResponseCode = http.POST(requestBody);

    // Baca respon
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

  delay(20000); // kirim tiap 20 detik
}
