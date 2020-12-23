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


    // Funktionsdefinitionen hier (immer außerhalb von loop() und setup())
    // Prototyp:
    //  _______________________________________ Datentyp des Rückgabewerts der Funktion (Output)
    // |    ___________________________________ Funktionsname
    // |   |     ______________________________ Datentyp des ersten Arguments (Input)
    // |   |    |      ________________________ erstes Argument
    // |   |    |     |         _______________ Datentyp des zweiten Arguments (Input)
    // |   |    |     |        |      _________ zweites Argument
    // |   |    |     |        |     |        _ Funktionskörper (bzw. Deklaration) kommt in die geschweiften Klammern
    // |   |    |     |        |     |       |
      int name(int argument1, int argument2) {
        //... hier wird die Funktion beschrieben
        return 0; // hier wird der Rückgabewert angegeben und zum "Caller" zurückgekehrt
    }

    // Kapitel 0x04: Addition
    int addition(int zahl1, int zahl2) {
        int ergebnis = zahl1 + zahl2;
        return ergebnis;
    }

    // Kapitel 0x04: Mittelwert
    int mittelwert(int z1, int z2, int z3, int z4, int z5, int z6, int z7, int z8, int z9, int z10) {
        int ergebnis = z1 + z2 + z3 + z4 + z5 + z6 + z7 + z8 + z9 + z10;
        ergebnis /= 10; // siehe Kapitel 0x03
        return ergebnis;
    }

    // Kapitel 0x04: Funktionen ohne Rückgabewert -> Datentyp "void"
    void ausgabe(int zahl) {
        Serial.print("Die Zahl ist: ");
        Serial.println(zahl);
        // hier wird kein "return" gebraucht, da nichts zurückgegeben wird
    }

    // Allgemeine Setup-Funktion
    void setup() {
        Serial.begin(115200);
        mySerial.begin(74880);
    }

    void loop() {
        // ################
        // # Kapitel 0x00 #
        // ################
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

        // ################
        // # Kapitel 0x01 #
        // ################
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


        // ################
        // # Kapitel 0x02 #
        // ################
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

        // ################
        // # Kapitel 0x03 #
        // ################
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
        //Serial.println(j0); // 4

        // Variable reduzieren
        int j1 = 10;
        j1 = j1 - 1; 
        j1--; // gleichbedeutend zu 'j1 = j1 - 1'
        --j1; // ...
        j1 -= 1;
        //Serial.println(j1); // 6

        // Variable multiplizieren oder dividieren
        int j2 = 20;
        j2 = j2 / 2; // 10
        j2 /= 2; // 5
        j2 = j2 * 3; // 15
        j2 *= 3; // 45

        // Erhöhen oder Reduzieren geht nicht nur mit 1:
        j2 += 5; // 50
        j2 -= 10; // 40
        //Serial.println(j2); // 40

        // ################
        // # Kapitel 0x04 #
        // ################
        //
        // Funktionen
        //
        int x4 = 5;
        int y4 = 6;
        int z4 = x4 + y4; // Plus-Operation kann in eine Funktion ausgelagert werden

        int x5 = 10;
        int y5 = 4;
        int z5 = x5 + y5; // Plus-Operation kann in eine Funktion ausgelagert werden

        // Funktionen müssen am Anfang vom Programm definiert werden, siehe oben
        // Addition mit Funktion "addition"
        int z6 = addition(3, 4); // -> z2 = 7

        // Beispiel: Mittelwert aus den Zahlen 1 - 10, siehe oben
        int mw1 = mittelwert(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        //ausgabe(mw1);

        // ################
        // # Kapitel 0x05 #
        // ################
        //
        // Schleifen
        //
        // Schleifen automatisieren gewisse Dinge
        // - hochzählen
        // - bestimmte Funktionen mehrfach aufrufen
        // - etwas so lange Ausführen, bis eine Abbruchbedingung erfüllt ist
        //
        // for-Schleife
        //   ___________________________________ Um welchen Schleifentyp handelt es sich? (for, while, do, ...)
        //  |        ___________________________ Laufvariable, bzw. Index, der hochgezählt wird
        //  |       |    _______________________ Start der Laufvariable i
        //  |       |   |     __________________ Abbruchbedingung, die Schleife wird ausgeführt so lange i < max ist
        //  |       |   |    |         _________ Um wie viel wird die Laufvariable i in jedem Iterationsschritt erhöht, hier um 1
        //  |       |   |    |        |
        // for (int i = 0; i < max; ++i) {  ____ Funktionskörper, bzw. diese Anweisungen werden in jedem Schritt ausgeführt
        //     
        // }

        // Beispiel, Variable i von 0 bis 9 hochzählen lassen
        for (int i = 0; i < 10; ++i) {
            //ausgabe(i);
        }

        // Beispiel 2, Variable j von -10 bis 18 hochzählen, um 3 erhöhen in jedem Iterationsschritt
        for (int j = -10; j < 18; j+=3) {
            //ausgabe(j);
        }

        // Beispiel3, Mittelwertsberechnung der Zahlen 1 - 10:
        int sum = 0;
        int max = 1000;
        for (int i = 1; i < max + 1; ++i) {
            sum += i; // gleichbedeutend mit sum = sum + i;
        }
        sum /= max;
        ausgabe(sum);

        // Aufgabe: 
        // Schreibe Funktion, die zwei Zahlen z1 und z2 nimmt und damit den
        // Mittelwert der Zahlenfolge z1 bis z2 bestimmt
        // Beispiel: z1 = 1 und z2 = 3: Mittelwert aus den Zahlen 1, 2, 3 -> 2
        // Beispiel: z1 = 4 und z2 = 7: Mittelwert aus den zahlen 4, 5, 6, 7 ->  ...
        

        // ################
        // # Kapitel 0x06 #
        // ################
        //
        // Arrays

        // ################
        // # Kapitel 0x07 #
        // ################
        //
        // Bedingungen

        // nur für den Simulator notwendig: (warte 10 Mikrosekunden)
        usleep(10);
    }
    // ########### CODE BLOCK END #############

public:
    ArduinoKurs() {}
    ~ArduinoKurs() {}
};