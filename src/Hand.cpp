#import "Arduino.h"
#include "Hand.h"

Hand::Hand(byte pin) {
    isOpen = false;

}

bool open();
bool close();
void move(int64_t degrees);