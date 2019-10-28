#include <Arduino.h>
#include <vexMotor.h>
#include <Encoder.h>

#define LIGHT_SENSOR_PIN
#define BUTTON_PIN 8
#define FLASHLIGHT 7
#define UPPER_MOTOR_PIN 6
#define LOWER_MOTOR_PIN 5
#define TOP_ENCODER_PIN 4
#define BOTTOM_ENCODER_PIN 3

#define JOY_X 0
#define JOY_Y 1

#define BAUD_RATE 9600

const byte MOTOR_PINS[] = {UPPER_MOTOR_PIN, LOWER_MOTOR_PIN};
vexMotor lowerMotor, upperMotor;
vexMotor motors[] = {lowerMotor, upperMotor};
Encoder encoder(BOTTOM_ENCODER_PIN, TOP_ENCODER_PIN);

long prevPos, prevX, prevY = -999;

void moveUp(byte speed = 255) {
    for (vexMotor motor : motors) {
        motor.write(speed);
    }
    Serial.println(String("moving up at ") + speed + " velocity...");
}

void moveDown(byte speed = 255) {
    for (vexMotor motor : motors) {
        motor.write(-speed);
    }
    Serial.println(String("moving down at ") + speed + " velocity...");
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
    Serial.println("Initializing motors...");
}

void setup() {
    Serial.begin(BAUD_RATE);

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
//    delay(500);
//    stop();
    const long currPos = encoder.read();
    if (currPos != prevPos) {
        prevPos = currPos;
        Serial.println(String("Encoder: ") + currPos);
    }

    const long currY = analogRead(JOY_Y);
    if (currY != prevY) {
        prevY = currY;
        Serial.println(String("y: ") + currY);
        const long actualY = 128 - map(currY, 0, 1023, 0, 256);
        if (actualY > 0) {
            moveUp(actualY);
        } else {
            moveDown(actualY);
        }
    }
}
