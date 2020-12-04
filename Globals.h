#pragma once
#include <string>
#include "Arduino.h"

class Globals
{ 
public:
   static std::string s_cinBuffer;
    static std::string s_pipeBuffer;
    static Arduino* s_arduino;
};