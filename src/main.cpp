#include <Arduino.h>
#include <vexMotor.h>

#define FLASHLIGHT 7
#define UPPER_MOTOR_PIN 6
#define LOWER_MOTOR_PIN 5
#define TOP_ENCODER_PIN 4
#define BOTTOM_ENCODER_PIN 3

// TODO: define emergency stop button and light sensor pins

void setup() {
    pinMode(FLASHLIGHT, OUTPUT);
    digitalWrite(FLASHLIGHT, HIGH);
}

void loop() {

}
