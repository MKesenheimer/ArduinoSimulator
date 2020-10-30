// Program to simulate the serial communication between two Arduinos
// mkfifo stdout
// g++ Communicator2.cpp -std=c++17 -o comm
// ./comm -r
// ./comm -s

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <thread>
#include "CommandLineParser.h"

class Arduino {
public:
    //virtual ~Arduino() = 0;
    virtual void begin() = 0;
    virtual void loop() = 0;
    virtual std::string writeTo() = 0;
    virtual std::string readFrom() = 0;
};

// globals
std::string s_cinBuffer;
std::string s_pipeBuffer;
Arduino* s_arduino;

class IOHandler {
public:
    void cinThread() {
        while (1) {
            std::string buffer;
            getline(std::cin, buffer);
            buffer += '\n';
            s_cinBuffer = buffer;
        }
    }

    void pipeThread() {
        while(1) {
            char c = 0;
            std::string filename(s_arduino->readFrom());
            const size_t size = sizeof(c);
            std::ifstream pipe(filename, std::ios::in | std::ios::binary);
            pipe.read(&c, size);
            pipe.close();
            s_pipeBuffer += c;
        }
    }
};

// low level stuff
class SoftwareSerial {
public:
    // dummy constructor
    SoftwareSerial(int, int) {}

    // dummy function
    void begin(int) {}

    bool available() {
        return (s_pipeBuffer.size() > 0);
    }

    char read() {
        char c = 0;
        if (s_pipeBuffer.size() > 0) {
            c = s_pipeBuffer[0];
            s_pipeBuffer.erase(s_pipeBuffer.begin());
        }
        return c;
    }

    void write(char c) {
        std::string filename(s_arduino->writeTo());
        const size_t size = sizeof(c);
        std::ofstream pipe(filename, std::ios::out | std::ios::binary);
        pipe.write(&c, size);
        usleep(1000);
        pipe.close();
    }

    void write(std::string str) {
        for(char& c : str) {
            write(c);
        }
    }
};

// "Serial Communication" with command line
// read and print characters from/to command line
class Serial_ {
public:
    // dummy function
    void begin(int) {}

    void write(char c) {
        std::cout << c;
    }

    bool available() {
        return (s_cinBuffer.size() > 0);
    }

    char read() {
        char c = 0;
        if (s_cinBuffer.size() > 0) {
            c = s_cinBuffer[0];
            s_cinBuffer.erase(s_cinBuffer.begin());
        }
        return c;
    }

    std::string readLine() {
        std::string buffer = s_cinBuffer;
        s_cinBuffer = std::string();
        return buffer;
    }
} Serial;

// configured as receiver
class Alice : public Arduino {
public:
    // Arduino-like program
    SoftwareSerial mySerial  = SoftwareSerial(2, 3);
    
    void begin() {
        Serial.begin(115200);
        mySerial.begin(74880);
    }

    void loop() {
        // receive the characters from mySerial (named pipe) and write to Serial (console)
        if (mySerial.available()) {
            char a = mySerial.read();
            Serial.write(a);
        }

        // receive the characters from Serial (console) and write to mySerial (named pipe)
        if (Serial.available()) {
            char a = Serial.read();
            mySerial.write(a);
        }
    }

public:
    Alice() {}
    ~Alice() {}
    std::string writeTo() {return "stdout12";}
    std::string readFrom() {return "stdout31";}
};

// configured as sender
class Bob : public Arduino {
public:
    // Arduino-like program
    SoftwareSerial mySerial  = SoftwareSerial(2, 3);

    void begin() {
        Serial.begin(115200);
        mySerial.begin(74880);
    }

    void loop() {
        // receive the characters from Serial (console) and write to mySerial (named pipe)
        if (Serial.available()) {
            char a = Serial.read();
            mySerial.write(a);
        }

        // receive the characters from mySerial (named pipe) and write to Serial (console)
        if (mySerial.available()) {
            char a = mySerial.read();
            Serial.write(a);
        }
    }
public:
    Bob() {}
    ~Bob() {}
    std::string writeTo() {return "stdout23";}
    std::string readFrom() {return "stdout12";}
};

// configured as sender
class Carter : public Arduino {
public:
    // Arduino-like program
    SoftwareSerial mySerial  = SoftwareSerial(2, 3);

    void begin() {
        Serial.begin(115200);
        mySerial.begin(74880);
    }

    void loop() {
        // receive the characters from Serial (console) and write to mySerial (named pipe)
        if (mySerial.available()) {
            char a = mySerial.read();
            Serial.write(a);
            mySerial.write(a);
        }

        // receive the characters from mySerial (named pipe) and write to Serial (console)
        /*if (mySerial.available()) {
            char a = mySerial.read();
            Serial.write(a);
        }*/
    }
public:
    Carter() {}
    ~Carter() {}
    std::string writeTo() {return "stdout31";}
    std::string readFrom() {return "stdout23";}
};

// program logic
int main(int argc, char* args[])
{
    if (auxiliary::CommandLineParser::cmdOptionExists(args, args + argc, "-a")) {
        s_arduino = new Alice;
    }

    if (auxiliary::CommandLineParser::cmdOptionExists(args, args + argc, "-b")) {
        s_arduino = new Bob;
    }

    if (auxiliary::CommandLineParser::cmdOptionExists(args, args + argc, "-c")) {
        s_arduino = new Carter;
    }

    IOHandler iohandler;
    std::thread thread1(&IOHandler::cinThread, iohandler);
    std::thread thread2(&IOHandler::pipeThread, iohandler);
    s_arduino->begin();
    while(1) {
        s_arduino->loop();
    }

    // is never reached
    thread1.join();
    thread2.join();
    //delete s_arduino;
}