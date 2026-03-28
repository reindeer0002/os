#include "utility.h"
#include "assembly-utility.h"

void kMemSet(void* pvDestination, BYTE bData, int iSize) {
    for (int i = 0; i < iSize; i++) {
        ((char*) pvDestination)[i] = bData;
    }
}

int kMemCpy(void* pvDestination, void* pvSource, int iSize) {
    for (int i = 0; i < iSize; i++) {
        ((char*) pvDestination)[i] = ((char*) pvSource)[i];
    }
    return iSize;
}

int kMemCmp(const void* pvDestination, const void* pvSource, int iSize) {
    char cTemp;
    for (int i = 0; i < iSize; i++) {
        cTemp = ((char*) pvDestination)[i] - ((char*) pvSource)[i];
        if (cTemp != 0) {
            return (int) cTemp;
        }
    }
    return 0;
}

BOOL kSetInterruptFlag(BOOL bEnableInterrupt) {
    QWORD qwRFLAGS;
    qwRFLAGS = kReadRFLAGS();
    if (bEnableInterrupt) {
        kEnableInterrupt();
    } else {
        kDisableInterrupt();
    }

    if (qwRFLAGS & 0x0200) {
        return TRUE;
    }
    return FALSE;
}

void kPrintString(int iX, int iY, const char* pcString) {
    CHARACTER* pstScreen = ( CHARACTER* ) 0xB8000;

    pstScreen += ( iY * 80 ) + iX;
    for(int i = 0; pcString[i] != 0; i++) {
        pstScreen[i].bCharacter = pcString[i];
    }
}
