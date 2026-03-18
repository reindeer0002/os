#ifndef __MODESWITCH_H
#define __MODESWITCH_H

#include "types.h"

void kReadCPUID(DWORD dwEAX, DWORD* pdwEAX, DWORD* pdwEBX, DWORD* pdwECX, DWORD* pdwEDX);
void kSwitchAndExecute64bitKernel();

#endif // __MODESWITCH_H
