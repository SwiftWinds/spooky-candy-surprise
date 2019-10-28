#ifndef SPOOKY_CANDY_SURPRISE_HAND_H
#define SPOOKY_CANDY_SURPRISE_HAND_H

#include <Arduino.h>

class Hand {
public:
    Hand(byte pin);
    bool open();
    bool close();
    void move(int64_t degrees);

private:
    bool isOpen;
    bool onTop;
};
#endif //SPOOKY_CANDY_SURPRISE_HAND_H
