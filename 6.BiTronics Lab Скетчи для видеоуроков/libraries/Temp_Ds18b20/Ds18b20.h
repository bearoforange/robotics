#ifndef Ds18b20_h
#define Ds18b20_h

#include <inttypes.h>

#if defined(__AVR__)
#include <util/crc16.h>
#endif

#if ARDUINO >= 100
#include "Arduino.h"       // for delayMicroseconds, digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif

class Temp
{
  public:
    Temp(int pin);
    void getTemp();
  private:
    int _pin;
};



#endif

