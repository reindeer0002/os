//
// Created by reindeer002-laptop on 3/18/26.
//

#include "types.h"

void kPrintString(int iX, int iY, const char* pcString);

void main() {
    kPrintString(0, 10, "Switch To IA-32e Mode Success.");
    kPrintString(0, 11, "IA-32e C language Kernel Start.");
}

void kPrintString(int iX, int iY, const char* pcString) {
    CHARACTER* pstScreen = ( CHARACTER* ) 0xB8000;

    pstScreen += ( iY * 80 ) + iX;
    for(int i = 0; pcString[i] != 0; i++) {
        pstScreen[i].bCharacter = pcString[i];
    }
}
