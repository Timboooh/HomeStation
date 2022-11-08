#include "beeper.hpp"
#include <Arduino.h>

#define beeperPin 25

namespace BEEPER
{
    void setup(){
        pinMode(beeperPin, OUTPUT);
        setBeeper(false);
    }

    void setBeeper(bool enable){
        digitalWrite(beeperPin, enable);
    }
} // namespace BEEPER
