//
// Created by reindeer002-laptop on 3/18/26.
//

#include "types.h"
#include "keyboard.h"

void kPrintString(int iX, int iY, const char* pcString);

void main() {
    char vcTemp[2] = {0};
    BYTE bFlags;
    BYTE bTemp;

    kPrintString(0, 10, "Switch To IA-32e Mode Success.");
    kPrintString(0, 11, "IA-32e C language Kernel Start.");
    kPrintString(0, 12, "Keyboard Activate.");

    if(kActivateKeyboard()) {
        kPrintString(45, 12, "PASS");
        kChangeKeyboardLED(FALSE, FALSE, FALSE);
    } else {
        kPrintString(45, 12, "FAIL");
        while(1);
    }

    int i = 0;
    while(1) {
        if(kIsOutputBufferFull()) {
            bTemp = kGetKeyboardScanCode();
            if(kConvertScanCodeToASCIICode(bTemp, &(vcTemp[0]), &bFlags)) {
                if(bFlags & KEY_FLAGS_DOWN) {
                    kPrintString(i++, 13, vcTemp);
                }
            }
        }
    }
}

void kPrintString(int iX, int iY, const char* pcString) {
    CHARACTER* pstScreen = ( CHARACTER* ) 0xB8000;

    pstScreen += ( iY * 80 ) + iX;
    for(int i = 0; pcString[i] != 0; i++) {
        pstScreen[i].bCharacter = pcString[i];
    }
}
