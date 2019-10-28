#include <Arduino.h>
#include <vexMotor.h>
#include <Encoder.h>

#define FLASHLIGHT 7
#define UPPER_MOTOR_PIN 6
#define LOWER_MOTOR_PIN 5
#define TOP_ENCODER_PIN 4
#define BOTTOM_ENCODER_PIN 3

#define BAUD_RATE 9600

// TODO: define emergency stop button and light sensor pins

//const byte MOTOR_PINS[] = {UPPER_MOTOR_PIN, LOWER_MOTOR_PIN};
vexMotor lowerMotor, upperMotor;
vexMotor motors[] = {lowerMotor, upperMotor};
Encoder encoder(BOTTOM_ENCODER_PIN, TOP_ENCODER_PIN);

long prevPos = -999;

void moveUp(byte speed = 255) {
    for (vexMotor motor : motors) {
        motor.write(speed);
    }
//    lowerMotor.write(speed);
//    upperMotor.write(speed);
    Serial.println("moving up...");
}

void moveDown(byte speed = 255) {
    for (vexMotor motor : motors) {
        motor.write(-speed);
    }
//    lowerMotor.write(-speed);
//    upperMotor.write(-speed);
}

void stop() {
    for (vexMotor motor : motors) {
        motor.write(0);
    }
    Serial.println("stopped.");
}

void initMotors() {
    upperMotor.attach(UPPER_MOTOR_PIN);
    lowerMotor.attach(LOWER_MOTOR_PIN);
    Serial.println("Initializing...");
}

void setup() {
//    // initiate motors to their respective pins
//    for (uint8_t i = 0; i < (uint8_t) sizeof(motors); i++) {
//        motors[i].attach(MOTOR_PINS[i]);
//    }
    Serial.begin(BAUD_RATE);

    initMotors();

    pinMode(FLASHLIGHT, OUTPUT);
    digitalWrite(FLASHLIGHT, HIGH);

    moveDown(255);
}

void loop() {
    // wait until light level below threshold
    // move hand up x degrees of rotation
    // close hand
    // wait until button press
    // open hand
    // move hand down -x degrees of rotation
//    delay(500);
//    stop();
    long currPos = encoder.read();
    if (currPos != prevPos) {
        prevPos = currPos;
        Serial.println(currPos);
    }
}
