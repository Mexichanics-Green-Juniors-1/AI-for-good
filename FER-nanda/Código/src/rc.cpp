/*
    Autor: Mexichanics Green (Jorge)
    Programa: FER-nanda RC
*/

// Librerías
#include <Arduino.h>
#include <BluetoothSerial.h>
#include <LiquidCrystal_I2C.h>

// Bluetooth
BluetoothSerial BT;
uint8_t address[] = {0x00,0x23,0x11,0x01,0x23,0xB0};
char lastSent = 'S';

// Pantalla
LiquidCrystal_I2C lcd(0x27,16,2);

// Pines
const uint8_t joyX = 34;
const uint8_t joyY = 35;
const uint8_t joyButton = 32;
const uint8_t button = 33;

// Umbrales
const int thresholdLow = 300;
const int thresholdHigh = 700;

// Variables
unsigned long lastBtn1 = 0;
unsigned long lastBtn2 = 0;
const int debounceDelay = 250;

void setup(){
    Serial.begin(115200);
    if(!BT.begin("FER-nanda_RC",true)){
        Serial.println("Error BT");
        return;
    }
    Serial.println("Conectando a HC-06...");
    if(BT.connect(address)){
        Serial.println("Conectado");
    } else{
        Serial.println("No conectado");
    }
    pinMode(joyButton, INPUT_PULLUP);
    pinMode(button, INPUT_PULLUP);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("RC Ready");
}

void loop(){
    if(!BT.connected()){
        Serial.println("Reconectando...");
        if(BT.connect(address)){
            Serial.println("Reconectado");
        } else{
            Serial.println("Fallo reconexion");
        }
        delay(2000);
        return;
    }
    char command = 'S';
    if(!digitalRead(button) && millis() - lastBtn1 > debounceDelay){
        command = 'X';
        lastBtn1 = millis();
    } else if(!digitalRead(joyButton) && millis() - lastBtn2 > debounceDelay){
        command = 'V';
        lastBtn2 = millis();
    } else{
        int x = analogRead(joyX);
        int y = analogRead(joyY);
        if(y > thresholdHigh) command = 'F';
        else if(y < thresholdLow) command = 'B';
        else if(x > thresholdHigh) command = 'R';
        else if(x < thresholdLow) command = 'L';
        else command = 'S';
    }
    if(command != lastSent){
        BT.write(command);
        lastSent = command;
    }
    char msg[33];
    int i = 0;
    while(BT.available() && i < 32){
        msg[i++] = BT.read();
    }
    msg[i] = '\0';
    if(i > 0){
        lcd.setCursor(0,1);
        lcd.print(msg);
        lcd.print("                ");
    }
    delay(40);
}