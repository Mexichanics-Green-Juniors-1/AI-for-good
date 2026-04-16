/*
    Autor: Mexichanics Green (Jorge)
    Programa: FER-nanda
*/

// Librerías
#include<Arduino.h>
#include<Servo.h>

// Enums
enum State{
    Stop,
    Forward,
    Backward,
    Left,
    Right,
    Sensing,
    ServoChanging
}, ServoHeight{
    Up,
    Down
};
// Variables
State btState = Stop;
ServoHeight ServoState = Up;
HardwareSerial &Bluetooth = Serial1;
int minHeight = 30, maxHeight = 0;
// Pines
uint8_t IN[] = {8, 9, 10, 11};
uint8_t motor = 12, yl = A0;
// Servos
Servo Motor;

// Actualizar State usando BT
State btUpdate(HardwareSerial &btHere){
    char dato = btHere.read();
    switch(dato) {
        case 'S': return(Stop);    break;
        case 'F': return(Forward); break;
        case 'B': return(Backward);break;
        case 'L': return(Left);    break;
        case 'R': return(Right);   break;
        case 'V': return(ServoChanging); break;
        case 'X': return(Sensing); break;
        default: return(Stop); break;
    }
}

void setup(){
    Serial.begin(9600);
    Bluetooth.begin(9600);
    for(uint8_t i = 0; i < 4; i++){
        pinMode(IN[i], OUTPUT);
    }
    Motor.attach(motor);
<<<<<<< HEAD
    Motor.write(maxHeight);
=======
    Motor.write(0);
>>>>>>> origin/dev-main
}

void loop(){
    if(Bluetooth.available()){
        btState = btUpdate(Bluetooth);
    }
    if(ServoState == Up){ // Así ni el servo ni el sensor se dañan porque el robot avanza mientras están ente
        switch(btState){
            case Stop:
                digitalWrite(IN[0], LOW);
                digitalWrite(IN[1], LOW);
                digitalWrite(IN[2], LOW);
                digitalWrite(IN[3], LOW);
            break;
            case Forward:
                digitalWrite(IN[0], HIGH);
                digitalWrite(IN[1], LOW);
                digitalWrite(IN[2], HIGH);
                digitalWrite(IN[3], LOW);
            break;
            case Backward:
                digitalWrite(IN[0], LOW);
                digitalWrite(IN[1], HIGH);
                digitalWrite(IN[2], LOW);
                digitalWrite(IN[3], HIGH);
            break;
            case Left:
                digitalWrite(IN[0], LOW);
                digitalWrite(IN[1], HIGH);
                digitalWrite(IN[2], HIGH);
                digitalWrite(IN[3], LOW);
            break; 
            case Right:
                digitalWrite(IN[0], HIGH);
                digitalWrite(IN[1], LOW);
                digitalWrite(IN[2], LOW);
                digitalWrite(IN[3], HIGH);
            break;
            default:
                Serial.println("Error");
            break;
        }
<<<<<<< HEAD
    } else if(btState == Sensing && ServoState == Down){ // Entonces, si el Servo NO está arriba (Osea, está abajo), va a revisar si está sensando, y en caso de estarlo, sensar
=======
    } else if(btState == Sensing){ // Entonces, si el Servo NO está arriba (Osea, está abajo), va a revisar si está sensando, y en caso de estarlo, sensar
>>>>>>> origin/dev-main
        int lectura = analogRead(yl);
        int humedad = map(lectura, 1023, 0, 0, 100); 
        Bluetooth.print("Humedad detectada: ");
        Bluetooth.print(humedad);
        Bluetooth.println("%");
        btState = Stop;
    }
<<<<<<< HEAD
    if(btState == ServoChanging){
        if(ServoState == Up){
            Motor.write(minHeight);
            ServoState = Down;
            btState = Stop;
        } else{
            Motor.write(maxHeight);
            ServoState = Up;
            btState = Stop;
        }
=======
    if(btState == ServoChanging && ServoState == Up){ // Si el servo está arriba y está cambiando baja, y si está abajo sube
        Motor.write(minHeight);
        ServoState = Down;
        btState = Stop;
    } else if(btState == ServoChanging && ServoState == Down){
       Motor.write(maxHeight);
       ServoState = Up;
       btState = Stop;
>>>>>>> origin/dev-main
    }
    if(ServoState == Down){
        digitalWrite(IN[0], LOW);
        digitalWrite(IN[1], LOW);
        digitalWrite(IN[2], LOW);
        digitalWrite(IN[3], LOW);
    }
<<<<<<< HEAD
}
=======
}
>>>>>>> origin/dev-main
