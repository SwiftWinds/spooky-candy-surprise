#include <Arduino.h>

#define LOWER_MOTOR_PIN 5
#define UPPER_MOTOR_PIN 6
#define TOP_ENCODER_PIN 4
#define BOTTOM_ENCODER_PIN 3

void setup() {
    // 
    pinMode(LOWER_MOTOR_PIN, OUTPUT);
    pinMode(UPPER_MOTOR_PIN, OUTPUT);

    //
}

void loop() {
    // alternate pin 8 and pin 12 every 1 sec
    digitalWrite(12, HIGH);
    digitalWrite(8, LOW);

    delay(1000);

    digitalWrite(12, LOW);
    digitalWrite(8, HIGH);

    delay(1000);
}
