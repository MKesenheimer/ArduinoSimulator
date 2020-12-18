#pragma once
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "Globals.h"
#include "SoftwareSerial.h"
#include "Serial.h"
#include "typedefs.h"
#include "Cryptography.h"
#include "ArduinoC.h"

// second participant (Bob)
class Bob : public ArduinoC {
public:
    // ########### CODE BLOCK BEGIN ###########
    // Arduino-like program
    SoftwareSerial mySerial  = SoftwareSerial(2, 3);

    void setup() {
        Serial.begin(115200);
        mySerial.begin(74880);
    }

    void loop() {
        String key = "abc123";

        // receive the characters from Serial (console) and write to mySerial (named pipe)
        if (Serial.available()) {
            String clr = Serial.readString();
            String cphr = Cryptography::encrypt(clr, key);
            mySerial.print(cphr);
            /*char clr = Serial.read();
            char cphr = Cryptography::encrypt(clr, 1);
            mySerial.write(cphr);*/
        }

        // receive the characters from mySerial (named pipe) and write to Serial (console)
        if (mySerial.available()) {
            String cphr = mySerial.readString();
            String clr = Cryptography::decrypt(cphr, key);
            Serial.print(clr);
            /*char cphr = mySerial.read();
            char clr = Cryptography::decrypt(cphr, 1);
            Serial.write(clr);*/
        }

        usleep(10);
    }
    // ########### CODE BLOCK END #############

public:
    Bob() {}
    ~Bob() {}
    std::string writeTo() {return "stdout21";}
    std::string readFrom() {return "stdout12";}
};
