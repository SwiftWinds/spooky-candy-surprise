//
// Created by Matt on 10/30/19.
//

#include <Arduino.h>

boolean CurrentButton = LOW;
boolean LastButton = LOW;
int LEDPin = 13;
int ButtonPin = 2;

void setup() {
    pinMode(LEDPin, OUTPUT);
    pinMode(ButtonPin, INPUT);
}

void loop() {
    CurrentButton = digitalRead(ButtonPin);
    while (LastButton != CurrentButton) {
        delay(30);
        LastButton = CurrentButton;
        CurrentButton = digitalRead(ButtonPin);
    }
    digitalWrite(LEDPin, CurrentButton);
}