#include <Arduino.h>
#include <vexMotor.h>

#define LOWER_MOTOR_PIN 5
#define UPPER_MOTOR_PIN 6
#define TOP_ENCODER_PIN 4
#define BOTTOM_ENCODER_PIN 3

// TODO: define flashlight, emergency stop button, and light sensor pins

const byte MOTOR_PINS[] = { LOWER_MOTOR_PIN, UPPER_MOTOR_PIN };
const vexMotor lowerMotor, upperMotor;
const vexMotor motors[] = { lowerMotor, upperMotor };

void setup() {
    // initiate motors to their respective pins
    for (int i = 0; i++; i < sizeof(motors)) {
       motors[i].attach(MOTOR_PINS[i]);
    }

    //
}

void loop() {

}
