#include <Arduino.h>

void setup() {
    // set pinMode of pin 12 and 8 to OUTPUT
    pinMode(12, OUTPUT);
    pinMode(8, OUTPUT);
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
