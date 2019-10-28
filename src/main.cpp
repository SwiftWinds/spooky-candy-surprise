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

void moveUp(byte speed = 255) {
    lowerMotor.write(speed);
    upperMotor.write(-speed);
}

void moveDown(byte speed = 255) {
    lowerMotor.write(-speed);
    upperMotor.write(speed);
}

void stop() {
    for (vexMotor motor : motors) {
        motor.write(0);
    }
}

void initMotors() {
    upperMotor.attach(UPPER_MOTOR_PIN);
    lowerMotor.attach(LOWER_MOTOR_PIN);
}

void setup() {
//    // initiate motors to their respective pins
//    for (uint8_t i = 0; i < (uint8_t) sizeof(motors); i++) {
//        motors[i].attach(MOTOR_PINS[i]);
//    }

    initMotors();


    pinMode(FLASHLIGHT, OUTPUT);
    digitalWrite(FLASHLIGHT, HIGH);
}

void loop() {
    // wait until light level below threshold
    // move hand up x degrees of rotation
    // close hand
    // wait until button press
    // open hand
    // move hand down -x degrees of rotation
}
