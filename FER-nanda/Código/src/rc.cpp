/*
    Autor: Mexichanics Green (Jorge)
    Programa: FER-nanda RC
*/

#include <Arduino.h>
#include <BluetoothSerial.h>
#include <LiquidCrystal_I2C.h>

BluetoothSerial BT;

LiquidCrystal_I2C lcd(0x27, 16, 2);

const uint8_t joyX = 34;
const uint8_t joyY = 35;
const uint8_t joyButton = 32;

const uint8_t button = 33;

const int thresholdLow = 300;
const int thresholdHigh = 700;
const int deadZoneMin = 400;
const int deadZoneMax = 600;

char lastSent = 'S';

unsigned long lastBtn1 = 0;
unsigned long lastBtn2 = 0;
const int debounceDelay = 250;

void setup() {
    Serial.begin(115200);

    BT.begin("FER-nanda_RC", true);

    pinMode(joyButton, INPUT_PULLUP);
    pinMode(button, INPUT_PULLUP);

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("RC Ready");
}

void loop() {

    char command = 'S';

    if (!digitalRead(button) && millis() - lastBtn1 > debounceDelay) {
        command = 'X';
        lastBtn1 = millis();
    }
    else if (!digitalRead(joyButton) && millis() - lastBtn2 > debounceDelay) {
        command = 'V';
        lastBtn2 = millis();
    }
    else {
        int x = analogRead(joyX);
        int y = analogRead(joyY);

        if (y > thresholdHigh) command = 'F';
        else if (y < thresholdLow) command = 'B';
        else if (x > thresholdHigh) command = 'R';
        else if (x < thresholdLow) command = 'L';
        else command = 'S';
    }

    if (command != lastSent) {
        BT.write(command);
        lastSent = command;
    }

    String msg = "";

    while (BT.available()) {
        msg += (char)BT.read();
    }

    if (msg.length() > 0) {
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print(msg);
    }

    delay(40);
}