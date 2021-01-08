#pragma once
#include <iostream>
#include <sstream>
#include "typedefs.h"

class Cryptography {
public:
    // s-box "encryption" look-up table (Nachschlage-Tabelle)
    // Bei Caesar, zum Beispiel, Verschiebung um 1:
    // a -> b
    // b -> c
    // c -> d
    // ...
    // bei s-box, zum Beispiel zufällig:
    // a -> y
    // b -> p
    // c -> r
    // d -> e
    // ...
    // brauche funktion, die als eingabe einen Buchstaben hernimmt
    // und diesen mit einem Buchstaben aus dem Array sbox ersetzt:
    static char sboxEncrypt(char c) {
        char ret;
        // wir kommen mit einem Alphabet an:
        // für Kleinbuchstaben:
        // Zeichen:  a, b, c, d, e, ...
        // Position: 0, 1, 2, 3, 4, ...
        if (c >= 97 && c <= 122) {
            int pos = (c - 97) % 26;
            char sbox[26] = {'y', 'p', 'r', 'e', 'f', 'u', 's', 'c', 'i', 't',
                            'h', 'n', 'm', 'a', 'o', 'z', 'x', 'd', 'g', 'j', 
                            'k', 'l', 'v', 'w', 'q', 'b'};
                ret = sbox[pos];
        }
        // für Großbuchstaben:
        else if (c >= 65 && c <= 90) {
            int pos = (c - 65) % 26;
            char sbox[26] = {'B', 'Q', 'W', 'V', 'L', 'K', 'J', 'G', 'D', 'X',
                             'Z', 'O', 'A', 'M', 'N', 'H', 'T', 'I', 'C', 'S',
                             'U', 'F', 'E', 'R', 'P', 'Y'};
            ret = sbox[pos];
        }
        // für alles andere (Sonderzeichen usw. werden nicht ersetzt)
        // Weil wir faul sind.
        // Könnte man noch verbessern
        else {
            ret = c;
        }
        
        return ret;
    }

    // TODO:
    static char sboxDecrypt(char c) {
        char ret;
        // Rückwärtsrichtung von sboxEncrypt
        //...
        return ret;
    }

    static String substring(const String& str, int pos, int length) {
        String temp;
        for (int i = pos; i < pos + length; ++i) {
            temp = temp + str[i];
        }
        return temp;
    }

    // Verschlüsselung nach dem Prinzip der "zufälligen Teilung" in
    // Intervalle
    static String chrisEncrypt(String clr, int *key, int keyLength) {
        // irgendwo vor dem Aufruf der Funktion chrisEncrypt muss das Array "key" definiert werden, z.B.
        // int key[10] = {1, 5, 4, 1, 3, 6, 1, 9, 1, 4};

        // Einfachstes Beispiel: Aufteilung des Strings
        // clr = "Hello World, das ist ein Test!";
        // in Intervalle mit jeweils 2 Buchstaben:
        // clr[] = {"He", "ll", "o ", "Wo", "rl", ...};
        // Vorschlag: Verschiebe das erste Intervall um 1, das zweite Intervall um 5 Buchstaben etc.
        
        /*
        // for...
        char clr1 = ...; // H
        char clr2 = ...; // e
        // Berechne die "verschlüsselten" Buchstaben:
        char cphr1 = clr1 + key[0];
        char cphr2 = clr2 + key[0];
        ... 

        // am Ende alle Buchstaben zu einem cphr-String zusammenfügen:
        String cphr = "";
        cphr += 'H'; // H
        cphr += 'e'; // He
        ...
        */


        // Hinweise zur Lösung:
        // Wie viele Zeichen enthält ein String (z.B. clr): 
        //   int strlength = clr.length();
        // Aufteilung eines großen Strings in einzelne "Substrings"
        //   String subs1 = clr.substr(0, 2); -> subs1 wird mit "He" befüllt
        //   String subs2 = clr.substr(2, 4); -> subs2 wird mit "ll" befüllt
        //


        /*String clrsub, cphr;
        clrsub = substring(clr, 0, 2);
        for (int i = 0; i < clrsub.size(); ++i) {
            char temp = clrsub[i] + key[0];
            cphr = cphr + temp;
        }*/

        //return cphr;
    }

    // xor-encryption with arbitrary long password
    static String encrypt(const String& clr, const String& key) {
        String cphr;
        int keyIter = 0;
        for (int clrIter = 0; clrIter < clr.size(); clrIter++) {
            // einzelnen Buchstaben aus dem Klartext im Alphabet verschieben -> "Verschlüsselung"
            char temp = (clr[clrIter] ^ key[keyIter]) % 128;
            if (temp < 0) temp += 128;
            // verschlüsselten Buchstaben temp an Cipher-Text cphr anhängen
            cphr = cphr + temp;
            keyIter = (keyIter + 1) % key.size();
        }
        return cphr;
    }

    static String decrypt(const String& cphr, const String& key) {
        String clr;
        int keyIter = 0;
        std::cout << "cipher text to decrpyt (hex) = " << convertToHex(cphr) << std::endl;
        std::cout << "cipher text to decrpyt       = " << cphr << std::endl;
        //std::cout << "key = " << key << std::endl;
        for (int cphrIter = 0; cphrIter < cphr.size(); cphrIter++) {
            // einzelnen Buchstaben aus dem Cipher-Text im Alphabet verschieben -> "Entschlüsselung"
            char temp = (cphr[cphrIter] ^ key[keyIter]) % 128;
            if (temp < 0) temp += 128;
            // entschlüsselten Buchstaben temp an Klartext clr anhängen
            clr = clr + temp;
            keyIter = (keyIter + 1) % key.size();
        }
        return clr;
    }

    // one char caesar
    static char encrypt(char clr, int key) {
        return clr - key;
    }

    static char decrypt(char cphr, int key) {
        return cphr + key;
    }

    // helper functions
    static String convertToHex(char c) {
        std::stringstream temp;
        if (c < 15)
            temp << "\\x0" << std::hex << (int)c;
        else
            temp << "\\x" << std::hex << (int)c;
        return temp.str();
    }

    static String convertToHex(const String& str) {
        std::string temp;
        for (const char c : str) {
            temp += convertToHex(c);
        }
        return temp;
    }
};