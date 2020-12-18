#pragma once
#include <string>
#include "ArduinoC.h"

class Globals
{ 
public:
   static std::string s_cinBuffer;
    static std::string s_pipeBuffer;
    static ArduinoC* s_arduino;
};