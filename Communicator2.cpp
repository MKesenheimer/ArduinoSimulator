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

std::string s_cinBuffer;
std::string s_pipeBuffer;
const std::string namedPipe12("stdout12");
const std::string namedPipe21("stdout21");

template<int nfile>
class IOHandler {
public:
    static void cinThread() {
        while (1) {
            std::string buffer;
            getline(std::cin, buffer);
            buffer += '\n';
            s_cinBuffer = buffer;
        }
    }

    static void pipeThread() {
        while(1) {
            char c = 0;
            std::string filename(namedPipe12);
            if (nfile == 21)
                filename = std::string(namedPipe21);
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
private:
    int m_nfile;
public:
    SoftwareSerial(int x, int y) : m_nfile(x * 10 + y) {}

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
        std::string filename(namedPipe12);
        if (m_nfile == 21)
            filename = std::string(namedPipe21);
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
class Arduino1 {
public:
    // Arduino-like program
    // ATTENTION: change this to SoftwareSerial mySerial(2, 3); in the "real" setup
    SoftwareSerial mySerial  = SoftwareSerial(2, 1);
    
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
};

// configured as sender
class Arduino2 {
public:
    // Arduino-like program
    // ATTENTION: change this to SoftwareSerial mySerial(2, 3); in the "real" setup
    SoftwareSerial mySerial  = SoftwareSerial(1, 2);

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
};

// program logic
int main(int argc, char* args[])
{
    if (auxiliary::CommandLineParser::cmdOptionExists(args, args + argc, "-r")) {
        IOHandler<12> iohandler;
        std::thread thread1(iohandler.cinThread);
        std::thread thread2(iohandler.pipeThread);
        Arduino1 arduino1;
        arduino1.begin();
        while(1) {
            arduino1.loop();
        }
        thread1.join();
        thread2.join();
    }

    if (auxiliary::CommandLineParser::cmdOptionExists(args, args + argc, "-s")) {
        IOHandler<21> iohandler;
        std::thread thread1(iohandler.cinThread);
        std::thread thread2(iohandler.pipeThread);
        Arduino2 arduino2;
        arduino2.begin();
        while(1) {
            arduino2.loop();
        }
        thread1.join();
        thread2.join();
    }
}