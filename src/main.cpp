#include <Arduino.h>
#include <vexMotor.h>
#include <Encoder.h>
#include <Servo.h>

#define LIGHT_SENSOR_PIN 10
#define HAND_SERVO_PIN 9
#define BUTTON_PIN 8
#define FLASHLIGHT_PIN 7
#define UPPER_MOTOR_PIN 6
#define LOWER_MOTOR_PIN 5
#define TOP_ENCODER_PIN 4
#define BOTTOM_ENCODER_PIN 3

#define JOY_Y 1

#define BAUD_RATE 9600

#define BUTTON_DELAY 30
#define MOTOR_DIST 424
#define HAND_SERVO_ROTATION 90
#define 

vexMotor lowerMotor, upperMotor;
vexMotor motors[] = {lowerMotor, upperMotor};
Encoder encoder(BOTTOM_ENCODER_PIN, TOP_ENCODER_PIN);

Servo handServo;

long prevPos, prevY, origPos = -999;
enum state {
    calibratingOrigPos,
    waitLightThreshold,
    movingHandUp,
    closingHand,
    waitOpenHandButtonPress,
    openingHand,
    movingHandDown
};

state _state = calibratingOrigPos;

state getState() {
    return _state;
}

bool setState(state newState) {
    auto temp = _state;
    _state = newState;
    return temp == newState;
}

void moveUp(byte speed = 255) {
    for (vexMotor motor : motors) {
        motor.write(speed);
    }
    // Serial.println(String("moving up at ") + speed + " velocity...");
}

void moveDown(byte speed = 255) {
    for (vexMotor motor : motors) {
        motor.write(-speed);
    }
    // Serial.println(String("moving down at ") + speed + " velocity...");
}

void stop() {
    for (vexMotor motor : motors) {
        motor.write(0);
    }
    // Serial.println("stopped.");
}

void initMotors() {
    upperMotor.attach(UPPER_MOTOR_PIN);
    lowerMotor.attach(LOWER_MOTOR_PIN);
    // Serial.println("Initializing motors...");
}

void setup() {
    Serial.begin(BAUD_RATE);

    initMotors();

    handServo.attach(HAND_SERVO_PIN);

    pinMode(BUTTON_PIN, INPUT);
    pinMode(FLASHLIGHT_PIN, OUTPUT);
    digitalWrite(FLASHLIGHT_PIN, HIGH);
}

void loop() {
    switch (getState()) {
        case calibratingOrigPos: {
            const long currPos = encoder.read();
            if (currPos != prevPos) {
                prevPos = currPos;
                // Serial.println(String("Encoder: ") + currPos);
            }

            const long currY = analogRead(JOY_Y);
            if (currY != prevY) {
                prevY = currY;
                // Serial.println(String("y: ") + currY);
                const long actualY = map(currY, 0, 1023, 255, -255);
                if (actualY > 0) {
                    moveUp(actualY);
                } else {
                    moveDown(-actualY);
                }
            }

            bool wasInLoop = false;
            boolean lastButton = LOW;
            boolean currentButton = digitalRead(BUTTON_PIN);
            Serial.println(String("lastButton: ") + lastButton + ", currentButton: " + currentButton);
            while (lastButton != currentButton) {
                Serial.println(String("In loop; before delay with lastButton: ") + lastButton + ", currentButton: " +
                               currentButton);
                wasInLoop = true;
                delay(BUTTON_DELAY);
                Serial.println(
                        String("after delay with lastButton: ") + lastButton + ", currentButton: " + currentButton);
                lastButton = currentButton;
                currentButton = digitalRead(BUTTON_PIN);
            }
            if (wasInLoop) {
                Serial.println(
                        String("exited loop with lastButton: ") + lastButton + ", currentButton: " + currentButton);
                origPos = currPos;
                setState(waitLightThreshold);

                Serial.println(String("origPos set to: ") + origPos);
            } else {
                Serial.println(
                        String("failed loop because lastButton: ") + lastButton + ", currentButton: " + currentButton);
            }
            break;
        }
        case waitLightThreshold:
            Serial.println(String("button value: ") + digitalRead(BUTTON_PIN));
            if ()
            break;
        case movingHandUp:
            if (encoder.read() - origPos >= HAND_SERVO_ROTATION) {

            }
            break;
        case closingHand:
            break;
        case waitOpenHandButtonPress:
            break;
        case openingHand:
            break;
        case movingHandDown:
            break;
    }
    // wait until light level below threshold
    // move hand up x degrees of rotation
    // close hand
    // wait until button press
    // open hand
    // move hand down -x degrees of rotation
//    delay(500);
//    stop();
}
