#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <LiquidCrystal.h>

// LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Joystick
uint8_t joyX = 34;
uint8_t joyY = 35;
uint8_t joyBtn = 32;

// Botón extra
uint8_t btnSense = 33;

// Umbrales calibrables
int deadZoneMin = 400;
int deadZoneMax = 600;

int thresholdLow = 300;
int thresholdHigh = 700;

int debounceDelay = 200;
int loopDelay = 50;

// Dirección MAC del receptor (CAMBIA ESTO)
uint8_t receiverMAC[] = {0x24, 0x6F, 0x28, 0xXX, 0xXX, 0xXX};

// Estado
char lastSent = 'S';

// Estructura de datos
typedef struct {
    char command;
} Message;

Message msg;

// Callback (opcional)
void onSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Envio: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "OK" : "Fallo");
}

void setup(){
    Serial.begin(115200);

    pinMode(joyBtn, INPUT_PULLUP);
    pinMode(btnSense, INPUT_PULLUP);

    lcd.begin(16, 2);
    lcd.print("RC ESP32");

    WiFi.mode(WIFI_STA);

    if(esp_now_init() != ESP_OK){
        Serial.println("Error ESP-NOW");
        return;
    }

    esp_now_register_send_cb(onSent);

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, receiverMAC, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if(esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Error peer");
        return;
    }
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

    // Prioridad
    if(!digitalRead(btnSense)){
        command = 'X';
        delay(debounceDelay);
    }
    else if(!digitalRead(joyBtn)){
        command = 'V';
        delay(debounceDelay);
    }

    // Enviar
    if(command != lastSent){
        msg.command = command;
        esp_now_send(receiverMAC, (uint8_t *) &msg, sizeof(msg));
        lastSent = command;
    }

    delay(loopDelay);
}