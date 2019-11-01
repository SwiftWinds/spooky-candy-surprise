#include <Arduino.h>
#include <vexMotor.h>
#include <Encoder.h>
#include <Servo.h>

#define LIGHT_SENSOR_PIN A2
#define HAND_SERVO_PIN 9
#define BUTTON_PIN 8
#define FLASHLIGHT_PIN 7
#define UPPER_MOTOR_PIN 6
#define LOWER_MOTOR_PIN 5
#define TOP_ENCODER_PIN 4
#define BOTTOM_ENCODER_PIN 3

#define JOY_Y A1

#define BAUD_RATE 9600

#define BUTTON_DELAY 30
#define MOTOR_DIST 424
#define HAND_SERVO_ROTATION 90
#define LIGHT_THRESHOLD 80

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

void stopMotors() {
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

bool buttonPressed() {
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
        return true;
    } else {
        Serial.println(
                String("failed loop because lastButton: ") + lastButton + ", currentButton: " + currentButton);
        return false;
    }
}

void setup() {
    Serial.begin(BAUD_RATE);

    initMotors();

    handServo.attach(HAND_SERVO_PIN);

    pinMode(LIGHT_SENSOR_PIN, INPUT);
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

            if (buttonPressed()) {
                origPos = currPos;
                setState(waitLightThreshold);

                Serial.println(String("origPos set to: ") + origPos);
            }
            break;
        }
        case waitLightThreshold: {
            Serial.println(String("light value: ") + analogRead(LIGHT_SENSOR_PIN));
            if (analogRead(LIGHT_SENSOR_PIN) > LIGHT_THRESHOLD) {
                moveUp();
                setState(movingHandUp);
            }
            break;
        }
        case movingHandUp: {
            if (encoder.read() - origPos >= MOTOR_DIST) {
                stopMotors();
                setState(closingHand);
            }
            break;
        }
        case closingHand: {
            handServo.write(HAND_SERVO_ROTATION);
            setState(waitOpenHandButtonPress);
            break;
        }
        case waitOpenHandButtonPress: {
            if (buttonPressed()) {
                setState(openingHand);
            }
            break;
        }
        case openingHand: {
            handServo.write(0);
            moveDown();
            setState(movingHandDown);
            break;
        }
        case movingHandDown: {
            if (encoder.read() == origPos) {
                stopMotors();
                setState(waitLightThreshold);
            }
            break;
        }
    }
    // wait until light level below threshold
    // move hand up x degrees of rotation
    // close hand
    // wait until button press
    // open hand
    // move hand down -x degrees of rotation
}
