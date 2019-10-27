#include <Arduino.h>
#include <vexMotor.h>

#define FLASHLIGHT 7
#define UPPER_MOTOR_PIN 6
#define LOWER_MOTOR_PIN 5
#define TOP_ENCODER_PIN 4
#define BOTTOM_ENCODER_PIN 3

// TODO: define emergency stop button and light sensor pins

const byte MOTOR_PINS[] = {LOWER_MOTOR_PIN, UPPER_MOTOR_PIN};
vexMotor lowerMotor, upperMotor;
vexMotor motors[] = {lowerMotor, upperMotor};

void moveUp() {
    lowerMotor.write(255);
    upperMotor.write(-255);
}

void moveDown() {
    lowerMotor.write(255);
    upperMotor.write(-255);
}

void setup() {
//    // initiate motors to their respective pins
//    for (uint8_t i = 0; i < (uint8_t) sizeof(motors); i++) {
//        motors[i].attach(MOTOR_PINS[i]);
//    }

    lowerMotor.attach(LOWER_MOTOR_PIN);

    lowerMotor.write(255);


    pinMode(FLASHLIGHT, OUTPUT);
    digitalWrite(FLASHLIGHT, HIGH);

}

void loop() {

}
