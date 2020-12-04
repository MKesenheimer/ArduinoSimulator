#pragma once
#include <string>

class Arduino {
public:
    //virtual ~Arduino() = 0;
    virtual void begin() = 0;
    virtual void loop() = 0;
    virtual std::string writeTo() = 0;
    virtual std::string readFrom() = 0;
};