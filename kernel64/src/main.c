//
// Created by reindeer002-laptop on 3/18/26.
//

#include "types.h"
#include "keyboard.h"
#include "utility.h"
#include "descriptor.h"
#include "pic.h"

void main() {
    char vcTemp[2] = {0};
    BYTE bFlags;
    BYTE bTemp;
    KEYDATA stData;
    kPrintString(0, 10, "Switch To IA-32e Mode Success.");
    kPrintString(0, 11, "IA-32e C language Kernel Start.");

    kPrintString(0, 12, "GDT Initialize And Switch For IA-32e Mode.");
    kInitializeGDTTableAndTSS();
    kLoadGDTR(GDTR_STARTADDRESS);
    kPrintString(45, 12, "PASS");

    kPrintString(0, 13, "TSS Segment Load");
    kLoadTR(GDT_TSSSEGMENT);
    kPrintString(45, 13, "PASS");

    kPrintString(0, 14, "IDT Initialize");
    kInitializeIDTTables();
    kLoadIDTR(IDTR_STARTADDRESS);
    kPrintString(45, 14, "PASS");

    kPrintString(0, 15, "Keyboard Activate And Queue Initialize");
    if(kInitializeKeyboard()) {
        kPrintString(45, 15, "PASS");
        kChangeKeyboardLED(FALSE, FALSE, FALSE);
    } else {
        kPrintString(45, 15, "FAIL");
        while(1);
    }

    kPrintString(0, 16, "PIC Controller And Interrupt Initialize.");
    kInitializePIC();
    kMaskPICInterrupt(0);
    kEnableInterrupt();
    kPrintString(45, 16, "PASS");

    int i = 0;
    while(1) {
        if(kGetKeyFromKeyQueue(&stData)) {
            if(stData.bFlags & KEY_FLAGS_DOWN) {
                vcTemp[0] = stData.bASCIICode;
                kPrintString(i++, 17, vcTemp);
                if(vcTemp[0] == '0') {
                    bTemp = bTemp / 0;
                }
            }
        }
    }
}
