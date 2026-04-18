/*
    Autor: Mexichanics Green (Jorge)
    Programa: FER-nanda RC
*/

#include <Arduino.h>
#include <BluetoothSerial.h>
#include <LiquidCrystal_I2C.h>

// Bluetooth
BluetoothSerial BT;

// LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Joystick (ESP32 ADC1)
uint8_t joyX = 34;
uint8_t joyY = 35;
uint8_t joyButton = 32;

// Botón extra
uint8_t button = 33;

// Umbrales
int thresholdLow = 300;
int thresholdHigh = 700;

// Zona muerta
int deadZoneMin = 400;
int deadZoneMax = 600;

// Estado
char lastSent = 'S';

// Debounce independiente
unsigned long lastBtn1 = 0;
unsigned long lastBtn2 = 0;
const int debounceDelay = 300;

void setup() {
    Serial.begin(115200);

    BT.begin("FER-nanda_RC");

    pinMode(joyButton, INPUT_PULLUP);
    pinMode(button, INPUT_PULLUP);

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("BT RC Ready");
}

void loop() {

    char command = 'S';

    // Botones (prioridad)
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
        else if (x > deadZoneMin && x < deadZoneMax &&
                 y > deadZoneMin && y < deadZoneMax) {
            command = 'S';
        }
    }

    // Envío solo si cambia
    if (command != lastSent) {
        BT.write(command);
        lastSent = command;
    }

    // Recepción
    if (BT.available()) {
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);

        while (BT.available()) {
            lcd.print((char)BT.read());
        }
    }

    delay(50);
}