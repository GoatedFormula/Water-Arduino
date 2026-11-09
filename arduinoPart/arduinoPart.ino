#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waiting...");
}

void loop() {
  if (Serial.available() > 0) {
    String song = Serial.readStringUntil('\n');
    song.trim();

    if (song.length() > 0) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("NOW PLAYING:");

      lcd.setCursor(0, 1);
      lcd.print(song.substring(0, 16));
    }
  }
}