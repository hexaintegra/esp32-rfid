#include <Wire.h>
#include <hd44780.h>                       // main class
#include <hd44780ioClass/hd44780_I2Cexp.h> // I2C expander class

hd44780_I2Cexp lcd; // auto detect PCF8574 backpack

void setup() {
  
  Serial.begin(9600);
  
  // default i2c (21=SDA, 22=SCL di ESP32)
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
  delay(5000);
}

void loop() {
  Serial.println("Looping...");
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Hello, World!");
  delay(3000);
  // clears the display to print new message
  lcd.clear();
  // set cursor to first column, second row
  lcd.setCursor(0,1);
  lcd.print("Selamat Datang!");
  delay(3000);
  lcd.clear(); 
}
