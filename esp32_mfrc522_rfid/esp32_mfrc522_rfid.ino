#include <iostream>
#include <string>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define buzzerPin 15

String tagID = "";

LiquidCrystal_I2C lcd(0x27, 16, 4);

void setup() {
  Serial.begin(115200);

  lcd.begin();
  lcd.backlight();

  lcd.setCursor(2, 1);
  lcd.print("Initializing");

  lcd.setCursor(-3, 2);
  lcd.print("Please wait...");

  delay(1000);

  initIOs();
  initRFID();

  lcd.clear();

}

void loop() {

  if (isRFIDDetected()) {
    Serial.println(tagID);
    lcd.clear();
    displayRFID(tagID);
  }

  displayReadMode();

}

void displayReadMode() {
  lcd.setCursor(0, 1);
  lcd.print("Tap to read");
}

void displayRFID(String uid) {
  lcd.setCursor(-4, 2);
  lcd.print("RFID: " + uid);
}

void initIOs() {
  pinMode(buzzerPin, OUTPUT);
}

void buzzerBeep(int delayMS) {
  digitalWrite(buzzerPin, HIGH);
  delay(delayMS);
  digitalWrite(buzzerPin, LOW);
}
