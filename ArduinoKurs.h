#pragma once
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Serial.h"
#include "typedefs.h"

// first participant (Test)
class ArduinoKurs : public Arduino {
public:
    // ########### CODE BLOCK BEGIN ###########
    // Arduino-like program
    SoftwareSerial mySerial  = SoftwareSerial(2, 3);

    void setup() {
        Serial.begin(115200);
        mySerial.begin(74880);
    }

    void loop() {
        // ##############
        // # Kapitel 0  #
        // ##############
        //
        // Hallo Welt Programm
        //
        //Serial.print("Hello world!\n");

        // 1 Byte = 8 Bit = 2^8 Möglichkeiten = 256 Zahlen
        // 0: 00000000
        // 1: 00000001
        // 2: 00000010
        // 3: 00000011
        // ...
        // 255: 11111111

        // 2 Bytes = 16 Bit = 2^16 Möglichkeiten = 65536 Zahlen

        // ##############
        // # Kapitel 1  #
        // ##############
        //
        // Datentypen
        //
        // Integer = Ganzzahlen: -1, 0, 1, 2, 3...
        // wird im Speicher als 00000000 00000011 abgelegt (1 Integer = 2 Byte)
        int x0 = 3; // Integer x wird mit 3 initialisiert
        // anderes Beispiel
        int x1 = 5; // 00000000 00000101
        // Datenwert mit long können mehr Zahlen definiert werden:
        // long = Ganzzahl mit größerem Speicherbereich: 
        // wird im Speicher als 4 Bytes -> 4294967296 Zahlen
        long x2 = 4294967295; 

        // Rationale Zahlen, reelle Zahlen: 
        // Zusammengefasst in Fließkommazahlen: 1.2, -4.52134234
        float y0 = 47.437; // 32 Bit, 4 Bytes
        double y1 = 3.14159265359; // 64 Bit, 8 Bytes

        // Zeichen, zum Beispiel
        char c0 = 'H'; // das Zeichen "H"
        char c1 = 'e'; // das Zeichen "e"
        char c2 = 'l'; // das Zeichen "l"
        // ...
        // Notiz:  Ein Zeichen ist im Speicher eigentlich einfach nur
        // eine Zahl -> Ascii-Tabelle
        // z.B. Zeichen 'a' wird im Speicher als Zahl 97 gespeichert
        // Beispiel:
        int v0 = 97; // 
        char v1 = 'a'; 
        // werden im Speicher exakt gleich abgelegt.

        // Einschub:
        // Casting:
        // Variablen können vom Prozessor anders interpretiert werden:
        char v2 = (char)v0; // 'a'

        // Strings: Aneinanderreihung von einzelnen Zeichen:
        String str = "Hello World";


        // ##############
        // # Kapitel 2  #
        // ##############
        //
        // Rechnen mit Datentypen
        //
        // Addition: Berechne 2 + 5
        int i = 2;
        int ii = 5;
        int iii = i + ii; // genauso Subtraktion: i - ii -> -3
        //Serial.println(iii);

        // Multiplikation:
        int m = i * ii;
        //Serial.println(m);

        // Division (Aufpassen!)
        int d0 = i / ii; // 2 / 5 = 0.4 -> d0 = 0
        float d1 = i / ii; // 2 / 5 = 0.4 -> d1 = 0.4
        //Serial.println(d1);

        // Rechnen mit Zeichen und Strings
        // + Operator: hängt Zeichen an einen String an:
        String str1 = "Hello ";
        String str2 = "World";
        String str3  = str1 + str2; // str2 wird an str1 angehängt: "Hello World!"
        //Serial.println(str3);

        // Zeichen an einen String anhängen
        char ausrufeZeichen = '!';
        String str4 = str3 + ausrufeZeichen;
        //Serial.println(str4);

        // ##############
        // # Kapitel 3  #
        // ##############
        //
        // Abkürzungen
        //
        // Variable erhöhen
        int j0 = 0; // 0
        j0 = j0 + 1; // 1
        //Serial.print(j0); // 1
        // kann abgekürzt werden zu
        j0++; // gleichbedeutend zu 'j0 = j0 + 1;'
        ++j0; // gleichbedeutend zu 'j0 = j0 + 1;'
        j0 += 1; // gleichbedeutend zu 'j0 = j0 + 1;'
        Serial.println(j0); // 4

        // Variable reduzieren
        int j1 = 10;
        j1 = j1 - 1; 
        j1--; // gleichbedeutend zu 'j1 = j1 - 1'
        --j1; // ...
        j1 -= 1;
        Serial.println(j1); // 6

        // Variable multiplizieren oder dividieren
        int j2 = 20;
        j2 = j2 / 2; // 10
        j2 /= 2; // 5
        j2 = j2 * 3; // 15
        j2 *= 3; // 45

        // Erhöhen oder Reduzieren geht nicht nur mit 1:
        j2 += 5; // 50
        j2 -= 10; // 40
        Serial.println(j2); // 40

        // ##############
        // # Kapitel 4  #
        // ##############
        //
        // Funktionen
        //

        // ##############
        // # Kapitel 5  #
        // ##############
        //
        // Schleifen und Bedingungen
        //

        // nur für den Simulator notwendig: (warte 10 Mikrosekunden)
        usleep(10);
    }
    // ########### CODE BLOCK END #############

public:
    ArduinoKurs() {}
    ~ArduinoKurs() {}
};