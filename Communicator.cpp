// Program to simulate the serial communication between two Arduinos
// mkfifo stdout
// g++ Communicator.cpp -std=c++17 -o comm
// ./comm -r
// ./comm -s

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include "CommandLineParser.h"

// low level stuff
class SoftwareSerial {
private:
    std::string buffer;
public:
    // dummy constructor
    SoftwareSerial(int, int) {}

    // dummy function
    void begin(int) {}

    char read() {
        // variables for the file sink
        char c = 0;
        std::string filename("stdout");
        const size_t size = sizeof(c);
        std::ifstream pipe(filename, std::ios::in | std::ios::binary);
        pipe.read(&c, size);
        pipe.close();
        return c;
    }

    std::string readString() {
        std::string str = std::string();
        char c = 0;
        while (c != '\n') {
            c = read();
            str += c;
        }
        return str;
    }

    void write(char c) {
        buffer += c;
        if (c == '\n')
        {
            write(buffer);
            buffer = std::string();
        }
    }

    void writeChar(char c) {
        std::string filename("stdout");
        const size_t size = sizeof(c);
        std::ofstream pipe(filename, std::ios::out | std::ios::binary);
        pipe.write(&c, size);
        usleep(1000);
        pipe.close();
    }

    void write(std::string str) {
        for(char& c : str) {
            writeChar(c);
        }
    }

    void writeln(char c) {
        writeChar(c);
        writeChar('\n');
    }

    // dummy function
    bool available() {
        return true;
    }
};

// "Serial Communication" with command line
// read and print characters from/to command line
class Serial_ {
private:
    std::string buffer;
public:
    // dummy function
    void begin(int) {}

    std::string readString() {
        getline(std::cin, buffer);
        buffer += '\n';
        return buffer;
    }

    char read() {
        char c = 0;
        if (buffer.size() > 0) {
            c = buffer[0];
            buffer.erase(buffer.begin());
        }
        return c;
    }

    // TODO: use template
    void write(std::string str) {
        std::cout << str;
    }

    void write(char c) {
        std::cout << c;
    }

    bool available() {
        if (buffer.size() == 0)
            readString();
        return (buffer.size() > 0);
    }
} Serial;

// configured as receiver
class Arduino1 {
public:
    // Arduino-like program
    SoftwareSerial mySerial  = SoftwareSerial(2, 3);
    int offst = 1;

    void begin() {
        Serial.begin(115200);
        mySerial.begin(74880);
    }

    void loop() {
        // receive the characters from mySerial and write to Serial
        if (mySerial.available())
        {
            //Serial.write(mySerial.readString());
            char a = mySerial.read();
            if (a != '\n')
                a -= offst;
            Serial.write(a);
        }
    }
};

// configured as sender
class Arduino2 {
public:
    // Arduino-like program
    SoftwareSerial mySerial = SoftwareSerial(2, 3);
    int offst = 1;

    void begin() {
        Serial.begin(115200);
        mySerial.begin(74880);
    }

    void loop() {
        // receive the characters from Serial and write to mySerial
        if (Serial.available()) {
            char a = Serial.read();
            if (a != '\n')
                a += offst;
            mySerial.write(a);
        }

        // or instead read whole strings (terminated by \n)
        /*std::string text = Serial.readString();
        for (char& c : text)
            c += offst;
        mySerial.write(text);
        */
    }
};

// program logic
int main(int argc, char* args[])
{
    if (auxiliary::CommandLineParser::cmdOptionExists(args, args + argc, "-r")) {
        Arduino1 receiver;
        receiver.begin();
        while(1) {
            receiver.loop();
        }
    }

    if (auxiliary::CommandLineParser::cmdOptionExists(args, args + argc, "-s")) {
        Arduino2 sender;
        sender.begin();
        while(1) {
            sender.loop();
        }
    }
}