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

    // mit dieser Funktion kann ein Array übergeben werden
    // Allerdings weiß die Funktion nicht, wie groß das Array ist.
    // Deshalb muss die Länge des Arrays als extra Parameter übergeben werden
    int mittelwert(int *z, int arrayLength) {
        // z[0] -> Zugriff auf das 0te Element
        // z[arrayLength - 1] -> Zugriff auf das letzte Element von z
        // for (int i = 0; i <= arrayLength - 1; ++i)
        int sum = 0;
        for (int i = 0; i < arrayLength; ++i) 
            sum += z[i];
        sum /= arrayLength; // sum = sum / arrayLength
        return sum;
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
        //ausgabe(sum);

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
        // Einführung: Sehr ungeschickt, wenn Zahlen nacheinander im Speicher abgelegt werden sollen:
        int z1 = 1;
        int z2 = 2;
        int z3 = 3;
        // Geschickter ist die Benutzung von Arrays in diesem Fall
        // Initialisierung:
        //   ____________________ Datentyp des Arrays, kann auch long, float, double, char... sein
        //  |   _________________ Variablenname, beliebig wählbar
        //  |  |  _______________ Größe des Arrays (wie viele Zahlen können abgespeichert werden)
        //  |  | |      _________ Initialisierungsliste, also die Zahlen, die im Array abgespeichert werden sollen
        //  |  | |     |
        // int z[3] = {1, 2, 3}; // äquivalent zu oben mit den drei Integer z1, z2, z3
        int z[3] = {1, 2, 3};

        // Auf einzelne Zahlen im Array, kann mit dem Klammeroperator zugegriffen werden:
        int temp1 = z[0]; // in temp1 steht 1
        int temp2 = z[2]; // in temp2 steht 3
        //int temp3 = z[3]; // Zugriff ist problematisch, da das Array nur 3 Felder groß ist, hier aber auf die vierte Zahl zugegriffen wird

        // Anstatt einer Initialisierungsliste zu verwenden, kann jedes Feld des Arrays
        // auch einzeln befüllt werden:
        int x[100];
        for (int i = 0; i < 100; ++i)
            x[i] = i; // x wird mit den zahlen {0, 1, 2, 3, 4, ..., 99} befüllt

        // Anwendungsfall: Länge von Vektoren
        //    |\ 
        //  y |  \  c
        //    |    \ 
        //    |______\ 
        //        x
        // c = sqrt(x^2 + y^2 + z^2)
        // Sei c ein Vektor c = (4, 5, 1)
        int c[3] = {4, 5, 1};
        float length = sqrt(pow(c[0], 2) + pow(c[1], 2) + pow(c[2], 2));

        // Anwendungsfall: Mittelwert aus beliebigen Zahlen
        // So können Arrays (siehe Kapitel 0x06) übergeben werden
        int zahlen[6] = {1, 3, 5, 200, 6, 45};
        int mw2 = mittelwert(zahlen, 6);
        // ausgabe(mw2);

        // Strings und arrays
        // Strings (Zeichenfolgen) sind nichts anderes als char-Arrays
        char string1[11] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
        // gleichbedeutend mit
        String string2 = "Hello world";
        Serial.print(string1);

        // ################
        // # Kapitel 0x07 #
        // ################
        //
        // Bedingungen (if-Anweisungen, Verzweigungen)
        // Bestimmte Code-Abschnitten sollen nur unter bestimmten Vorraussetzungen 
        // ausgeführt werden:
        for (int i = 0; i < 10; ++i) {
            if (i > 2) {
                ausgabe(i); // sobald i >= 3 (also i 2 übersteigt), werden die nächsten Zahlen von 3 bis 9 auf der Konsole ausgegeben
            }
            // Notiz: zwei if-Anweisungen nacheinander beeinflussen sich nicht gegenseitig.
            if (i % 2 == 0) {
                ausgabe(i); // nur alle geraden Zahlen werden ausgegeben: 0, 2, 4, ..., 8
            }

            // zwei verschachtelte if-Anweisungen
            if (i < 6) {
                if (i % 2 == 1) {
                    ausgabe(i); // alle ungeraden Zahlen unter 6 werden ausgegeben.
                }
            }
        }

        // if-Anweisungen mit mehreren Ausgängen (Pfaden)
        int bed = 1;
        if (bed == 0) { // wenn das...
            Serial.print("Erster Pfad"); // dann das...
        } else { // wenn nicht:
            Serial.print("Zweiter Pfad"); // dann das...
        }

        bed = 2;
        if (bed == 0) { // wenn das...
            Serial.print("Erster Pfad"); // dann das...
        } else if (bed == 1) { // wenn das...
            Serial.print("Zweiter Pfad"); // dann das...
        } else if (bed == 2) {
            Serial.print("Dritter Pfad");
        } else {
            Serial.print("Vierter Pfad");
        }

        // Verknüpfungen "und", "oder"
        int bed1 = 0;
        int bed2 = 5;
        if (bed1 == 0 && bed2 < 6) // das nachfolgende wird nur ausgeführt, wenn sowohl Bedingung1 und Bedingung2 wahr sind
            Serial.print("Bedingung1 und Bedingung2 wahr!");
        if (bed1 != 0 || bed2 < 6) // 
            Serial.print("Bedingung1 oder Bedingung2 wahr!");

        // "Negation"
        int bed3 = 3;
        // bed3 > 5: falsch
        if ( !(bed3 > 5) ) // falsch wird in wahr umgewandelt
            Serial.print("Variable bed3 ist kleiner gleich 5");

        // nur für den Simulator notwendig: (warte 10 Mikrosekunden)
        usleep(10);
    }
    // ########### CODE BLOCK END #############

public:
    ArduinoKurs() {}
    ~ArduinoKurs() {}
};