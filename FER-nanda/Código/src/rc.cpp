/*
    Autor: Mexichanics Green (Jorge)
    Programa: FER-nanda RC
*/

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Bluetooth (RX, TX)
SoftwareSerial BT(10, 11);

// Joystick
uint8_t joyX = A0;
uint8_t joyY = A1;
uint8_t joyBtn = 8;

// Botón extra
uint8_t btnSense = 9;

// Umbrales joystick
int deadZoneMin = 400;
int deadZoneMax = 600;

int thresholdLow = 300;
int thresholdHigh = 700;

// Delay debounce
int debounceDelay = 200;

// Delay loop
int loopDelay = 50;

// Estado
char lastSent = 'S';

void setup(){
    Serial.begin(9600);   // opcional debug
    BT.begin(9600);

    pinMode(joyBtn, INPUT_PULLUP);
    pinMode(btnSense, INPUT_PULLUP);

    lcd.begin(16, 2);
    lcd.print("RC Ready");
}

void loop(){
    int x = analogRead(joyX);
    int y = analogRead(joyY);

    char command = 'S';

    // Movimiento
    if(y > thresholdHigh) command = 'F';
    else if(y < thresholdLow) command = 'B';
    else if(x > thresholdHigh) command = 'R';
    else if(x < thresholdLow) command = 'L';
    else if(x > deadZoneMin && x < deadZoneMax && y > deadZoneMin && y < deadZoneMax)
        command = 'S';

    // Prioridad: sensado > servo
    if(!digitalRead(btnSense)){
        command = 'X';
        delay(debounceDelay);
    }
    else if(!digitalRead(joyBtn)){
        command = 'V';
        delay(debounceDelay);
    }

    // Enviar solo si cambia
    if(command != lastSent){
        BT.write(command);
        lastSent = command;
    }

    // Mostrar datos recibidos (sin parpadeo)
    if(BT.available()){
        lcd.setCursor(0, 1); // segunda línea

        while(BT.available()){
            char c = BT.read();
            lcd.print(c);
        }
    }

    delay(loopDelay);
}