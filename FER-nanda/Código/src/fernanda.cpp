/*
    Autor: Mexichanics Green (Jorge)
    Programa: FER-nanda
*/

// Librerías
#include <Arduino.h>
#include <Servo.h>

// Enums
enum State{
    Stop,
    Forward,
    Backward,
    Left,
    Right,
    Sensing,
    ServoChanging
};
enum ServoHeight{
    Up,
    Down
};

// Bluetooth
HardwareSerial &Bluetooth = Serial1;
State btState = Stop;

// Servo
ServoHeight ServoState = Up;
Servo Motor;

// Pines
uint8_t IN[] = {8,9,10,11};
uint8_t motorPin = 12;
uint8_t yl = A0;

// Variables
const int minHeight = 30;
const int maxHeight = 0;
unsigned long lastServoChange = 0;
const int servoDelay = 300;

// Función BT
State btUpdate(HardwareSerial &btHere){
    if(!btHere.available()) return(btState);
    char dato = btHere.read();
    switch(dato){
        case 'S': return(Stop);
        case 'F': return(Forward);
        case 'B': return(Backward);
        case 'L': return(Left);
        case 'R': return(Right);
        case 'V': return(ServoChanging);
        case 'X': return(Sensing);
        default: return(btState);
    }
}

void setup(){
    Serial.begin(9600);
    Bluetooth.begin(9600);
    for(uint8_t i = 0; i < 4; i++){
        pinMode(IN[i], OUTPUT);
    }
    Motor.attach(motorPin);
    Motor.write(maxHeight);
}

void loop(){
    btState = btUpdate(Bluetooth);
    if(btState == ServoChanging && millis() - lastServoChange > servoDelay){
        if(ServoState == Up){
            Motor.write(minHeight);
            ServoState = Down;
        } else{
            Motor.write(maxHeight);
            ServoState = Up;
        }
        lastServoChange = millis();
        btState = Stop;
    }
    if(ServoState == Down){
        digitalWrite(IN[0], LOW);
        digitalWrite(IN[1], LOW);
        digitalWrite(IN[2], LOW);
        digitalWrite(IN[3], LOW);
    } else{
        if(btState == Stop){
            digitalWrite(IN[0], LOW);
            digitalWrite(IN[1], LOW);
            digitalWrite(IN[2], LOW);
            digitalWrite(IN[3], LOW);
        } else if(btState == Forward){
            digitalWrite(IN[0], HIGH);
            digitalWrite(IN[1], LOW);
            digitalWrite(IN[2], HIGH);
            digitalWrite(IN[3], LOW);
        } else if(btState == Backward){
            digitalWrite(IN[0], LOW);
            digitalWrite(IN[1], HIGH);
            digitalWrite(IN[2], LOW);
            digitalWrite(IN[3], HIGH);
        } else if(btState == Left){
            digitalWrite(IN[0], LOW);
            digitalWrite(IN[1], HIGH);
            digitalWrite(IN[2], HIGH);
            digitalWrite(IN[3], LOW);
        } else if(btState == Right){
            digitalWrite(IN[0], HIGH);
            digitalWrite(IN[1], LOW);
            digitalWrite(IN[2], LOW);
            digitalWrite(IN[3], HIGH);
        }
    }
    if(btState == Sensing && ServoState == Down){
        int lectura = analogRead(yl);
        int humedad = map(lectura, 1023, 0, 0, 100);
        Bluetooth.print("Humedad:");
        Bluetooth.print(humedad);
        Bluetooth.println("%");
        btState = Stop;
    }
}