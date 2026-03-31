//
// Created by reindeer002-laptop on 3/18/26.
//

#include "types.h"
#include "keyboard.h"
#include "utility.h"
#include "descriptor.h"
#include "pic.h"
#include "console.h"
#include "console-shell.h"

void main() {
    char vcTemp[2] = {0};
    BYTE bFlags;
    BYTE bTemp;
    KEYDATA stData;

    int iCursorX, iCursorY;
    kInitializeConsole(0, 10);
    kPrintf("Switch To IA-32e Mode Success.\n");
    kPrintf("IA-32e C language Kernel Start.\n");
    kPrintf("Initialize Console.");

    kGetCursor(&iCursorX, &iCursorY);
    kPrintf("GDT Initialize And Switch For IA-32e Mode.\n");
    kInitializeGDTTableAndTSS();
    kLoadGDTR(GDTR_STARTADDRESS);
    kSetCursor(45, iCursorY++);
    kPrintf("PASS\n");

    kPrintf("TSS Segment Load.\n");
    kLoadTR(GDT_TSSSEGMENT);
    kSetCursor(45, iCursorY++);
    kPrintf("PASS\n");

    kPrintf("IDT Initialize.\n");
    kInitializeIDTTables();
    kLoadIDTR(IDTR_STARTADDRESS);
    kSetCursor(45, iCursorY++);
    kPrintf("PASS\n");

    kPrintf("Total RAM Size Check.\n");
    kCheckTotalRAMSize();
    kSetCursor(45, iCursorY++);
    kPrintf("PASS, Size = %d MB\n", kGetTotalRAMSize());

    kPrintf("Keyboard Activate And Queue Initialize.\n");
    if(kInitializeKeyboard()) {
        kSetCursor(45, iCursorY++);
        kPrintf("PASS\n");
        kChangeKeyboardLED(FALSE, FALSE, FALSE);
    } else {
        kSetCursor(45, iCursorY++);
        kPrintf("FAIL\n");
        while(1);
    }

    kPrintf("PIC Controller And Interrupt Initialize.\n");
    kInitializePIC();
    kMaskPICInterrupt(0);
    kEnableInterrupt();
    kSetCursor(45, iCursorY++);
    kPrintf("PASS\n");

    kStartConsoleShell();
}
