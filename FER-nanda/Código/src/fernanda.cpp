/*
    Autor: Mexichanics Green (Jorge)
    Programa: FER-nanda
*/

#include <Arduino.h>
#include <Servo.h>

enum State {
    Stop,
    Forward,
    Backward,
    Left,
    Right,
    Sensing,
    ServoChanging
};

enum ServoHeight {
    Up,
    Down
};

State btState = Stop;
ServoHeight ServoState = Up;

HardwareSerial &Bluetooth = Serial1;

const int minHeight = 30;
const int maxHeight = 0;

uint8_t IN[] = {8, 9, 10, 11};
uint8_t motorPin = 12;
uint8_t yl = A0;

Servo Motor;

State btUpdate(HardwareSerial &btHere) {
    if (!btHere.available()) return Stop;

    char dato = btHere.read();

    switch (dato) {
        case 'S': return Stop;
        case 'F': return Forward;
        case 'B': return Backward;
        case 'L': return Left;
        case 'R': return Right;
        case 'V': return ServoChanging;
        case 'X': return Sensing;
        default: return Stop;
    }
}

void setup() {
    Serial.begin(9600);
    Bluetooth.begin(9600);

    for (uint8_t i = 0; i < 4; i++) {
        pinMode(IN[i], OUTPUT);
    }

    Motor.attach(motorPin);
    Motor.write(maxHeight);
}

void loop() {

    btState = btUpdate(Bluetooth);

    // ---------------- MOVIMIENTO ----------------
    if (ServoState == Up) {

        if (btState == Stop) {
            digitalWrite(IN[0], LOW);
            digitalWrite(IN[1], LOW);
            digitalWrite(IN[2], LOW);
            digitalWrite(IN[3], LOW);
        }

        else if (btState == Forward) {
            digitalWrite(IN[0], HIGH);
            digitalWrite(IN[1], LOW);
            digitalWrite(IN[2], HIGH);
            digitalWrite(IN[3], LOW);
        }

        else if (btState == Backward) {
            digitalWrite(IN[0], LOW);
            digitalWrite(IN[1], HIGH);
            digitalWrite(IN[2], LOW);
            digitalWrite(IN[3], HIGH);
        }

        else if (btState == Left) {
            digitalWrite(IN[0], LOW);
            digitalWrite(IN[1], HIGH);
            digitalWrite(IN[2], HIGH);
            digitalWrite(IN[3], LOW);
        }

        else if (btState == Right) {
            digitalWrite(IN[0], HIGH);
            digitalWrite(IN[1], LOW);
            digitalWrite(IN[2], LOW);
            digitalWrite(IN[3], HIGH);
        }

        else {
            digitalWrite(IN[0], LOW);
            digitalWrite(IN[1], LOW);
            digitalWrite(IN[2], LOW);
            digitalWrite(IN[3], LOW);
        }
    }

    // ---------------- SENSOR ----------------
    else if (btState == Sensing && ServoState == Down) {

        int lectura = analogRead(yl);
        int humedad = map(lectura, 1023, 0, 0, 100);

        Bluetooth.print("Humedad: ");
        Bluetooth.print(humedad);
        Bluetooth.println("%");

        btState = Stop;
    }

    // ---------------- SERVO ----------------
    if (btState == ServoChanging) {

        if (ServoState == Up) {
            Motor.write(minHeight);
            ServoState = Down;
        }
        else {
            Motor.write(maxHeight);
            ServoState = Up;
        }

        btState = Stop;
    }

    // seguridad motor apagado si está abajo
    if (ServoState == Down) {
        digitalWrite(IN[0], LOW);
        digitalWrite(IN[1], LOW);
        digitalWrite(IN[2], LOW);
        digitalWrite(IN[3], LOW);
    }
}