#pragma once
#include <string>
#include "Arduino.h"

class ArduinoC : public Arduino {
public:
    virtual std::string writeTo() = 0;
    virtual std::string readFrom() = 0;
};