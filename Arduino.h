#pragma once

class Arduino {
public:
    //virtual ~Arduino() = 0;
    virtual void setup() = 0;
    virtual void loop() = 0;
};