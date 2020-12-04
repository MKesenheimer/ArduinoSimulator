#pragma once
#include <iostream>
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

    static String encrypt(String clr, String key) {
        String cphr;
        int keyIter = 0;
        for (int clrIter = 0; clrIter < clr.size(); clrIter++) {
            // einzelnen Buchstaben aus dem Klartext im Alphabet verschieben -> "Verschlüsselung"
            char temp = (clr[clrIter] - key[keyIter] + 65) % 256;
            // verschlüsselten Buchstaben temp an Cipher-Text cphr anhängen
            cphr = cphr + temp;
            keyIter = (keyIter + 1) % key.size();
        }
        return cphr;
    }

    static String decrypt(String cphr, String key) {
        String clr;
        int keyIter = 0;
        std::cout << "cipher text to decrpyt = " << cphr << std::endl;
        //std::cout << "key = " << key << std::endl;
        for (int cphrIter = 0; cphrIter < cphr.size(); cphrIter++) {
            // einzelnen Buchstaben aus dem Cipher-Text im Alphabet verschieben -> "Entschlüsselung"
            char temp = (cphr[cphrIter] + key[keyIter] - 65) % 256;
            // entschlüsselten Buchstaben temp an Klartext clr anhängen
            clr = clr + temp;
            keyIter = (keyIter + 1) % key.size();
            //std::cout << "keyIter = " << keyIter << std::endl;
        }
        return clr;
    }

    static char encrypt(char clr, int key) {
        return clr - key;
    }

    static char decrypt(char cphr, int key) {
        return cphr + key;
    }
};