//
// Created by reindeer002-laptop on 3/12/26.
//

#include "types.h"
#include "page.h"

void kPrintString(int iX, int iY, const char* pcString);
BOOL kInitializeKernel64Area();
BOOL kIsMemoryEnough();

void main() {
    kPrintString(0, 3, "C Language Kernel Started.");
    kPrintString(0, 4, "Minimum Memory Size Check.");
    if(kIsMemoryEnough() == FALSE) {
        kPrintString(45, 4, "FAIL");
        kPrintString(0, 5, "Not Enough Memory, REIN OS Requires Over 64MB Memory.");
        while(1);
    }
    kPrintString(45, 4, "PASS");

    kPrintString(0, 5, "IA-32e Kernel Area Initialize.");
    if(kInitializeKernel64Area() == FALSE) {
        kPrintString(45, 5, "FAIL");
        kPrintString(0, 6, "Kernel Area Initialization Fail.");
        while(1);
    }
    kPrintString(45, 5, "PASS");

    kPrintString(0, 6, "IA-32e Page Tables Initialize.");
    kInitializePageTables();
    kPrintString(45, 6, "PASS");

    while(1);
}

void kPrintString(int iX, int iY, const char* pcString) {
    CHARACTER* pstScreen = ( CHARACTER* ) 0xB8000;

    pstScreen += ( iY * 80 ) + iX;
    for(int i = 0; pcString[i] != 0; i++) {
        pstScreen[i].bCharacter = pcString[i];
    }
}

BOOL kInitializeKernel64Area() {
    DWORD* pdwCurrentAddress;

    pdwCurrentAddress = ( DWORD* ) 0x100000;

    while((DWORD) pdwCurrentAddress < 0x600000) {
        *pdwCurrentAddress = 0x00;
        if(*pdwCurrentAddress != 0) {
            return FALSE;
        }
        pdwCurrentAddress++;
    }
    return TRUE;
}

BOOL kIsMemoryEnough() {
    DWORD* pdwCurrentAddress;
    pdwCurrentAddress = (DWORD*) 0x100000;
    while((DWORD)pdwCurrentAddress < 0x4000000) {
        *pdwCurrentAddress = 0x12345678;

        if(*pdwCurrentAddress != 0x12345678) {
            return FALSE;
        }
        pdwCurrentAddress += (0x100000 / 4);
    }
    return TRUE;
}
