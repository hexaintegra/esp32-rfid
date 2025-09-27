#include <WiFi.h>
#include <HTTPClient.h>

#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverI2C.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>

#include <Wire.h>
#include <hd44780.h>                       // main class
#include <hd44780ioClass/hd44780_I2Cexp.h> // I2C expander class

// Ganti dengan SSID & password WiFi kamu
const char* ssid = "SSID";
const char* password = "PASSWORD";

// Endpoint tujuan
const char* serverUrl = "https://xxxxxxxxxxxx.supabase.co/rest/v1/absensi";
const char* apikey = "sb_secret_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

hd44780_I2Cexp lcd; // auto detect PCF8574 backpack
MFRC522DriverPinSimple ss_pin(5);

MFRC522DriverSPI driver{ss_pin}; // Create SPI driver
MFRC522 mfrc522{driver};         // Create MFRC522 instance

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  while (!Serial);       // Do nothing if no serial port is opened

  // Koneksi ke WiFi
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Terhubung");

  // Inisialisasi RFID
  Serial.println("Init RFID");
  mfrc522.PCD_Init();    // Init MFRC522 board.
  Serial.println("Done");

  // Inisialisasi LCD
  lcd.begin(16, 2);        // LCD 16x2
  // Nyalakan backlight
  lcd.backlight();
 
  // Pindahkan kursor ke kolom 0 dan baris 0
  // (baris 1)
  lcd.setCursor(0, 0);
 
  // Cetak hellow ke layar
  lcd.print("HELLO WORLD!");
 
  // Pindahkan kursor ke baris berikutnya dan cetak lagi
  lcd.setCursor(0, 1);      
  Serial.println("Tampilkan text dilayar");
  lcd.print("HEXAINTEGRA.COM");
}

void loop() {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards.
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("Card UID: ");
  MFRC522Debug::PrintUID(Serial, (mfrc522.uid));
  Serial.println();

  // Save the UID on a String variable
  String uidString = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      uidString += "0"; 
    }
    uidString += String(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println(uidString);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Absen Berhasil");
  lcd.setCursor(0, 1);
  // print message
  lcd.printf("UID:%s", uidString);
  sendToServer(uidString);

  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ready");
}

void sendToServer(String uid)
{
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverUrl);

    // Tambahkan header
    http.addHeader("Content-Type", "application/json");
    http.addHeader("apikey", apikey);

    // Data JSON untuk dikirim
    String requestBody = "{\"kode_rfid\":\""+uid+"\"}";

    // Kirim request POST
    Serial.println("Kirim UID ke server.");
    int httpResponseCode = http.POST(requestBody);

    // Baca respons
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response Code: " + String(httpResponseCode));
      Serial.println("UID berhasil terkirim");
    } else {
      Serial.println("Error, kode: " + String(httpResponseCode));
    }

    http.end();
  } else {
    Serial.println("WiFi tidak terhubung");
  }
}
