#ifndef __CONSOLE_SHELL_H__
#define __CONSOLE_SHELL_H__

#include "types.h"

#define CONSOLESHELL_MAXCOMMANDBUFFERCOUNT 300
#define CONSOLESHELL_PROMPTMESSAGE "REIN64> "

typedef void (*CommandFunction)(const char* pcParameterBuffer);

#pragma pack(push, 1)

typedef struct kShellCommandEntryStruct {
    char* pcCommand;
    char* pcHelp;
    CommandFunction pfFunction;
} SHELLCOMMANDENTRY;

typedef struct kParameterListStruct {
    const char* pcBuffer;
    int iLength;
    int iCurrentPosition;
} PARAMETERLIST;

#pragma pack(pop)

void kStartConsoleShell();
void kExecuteCommand(const char* pcCommandBuffer);
void kInitializeParameter(PARAMETERLIST* pstList, const char* pcParameter);
int kGetNextParameter(PARAMETERLIST* pstList, char* pcParameter);
void kHelp(const char* pcParameterBuffer);
void kClear(const char* pcParameterBuffer);
void kShowTotalRAMSize(const char* pcParameterBuffer);
void kStringToDecimalHexTest(const char* pcParameterBuffer);
void kRebootCommand(const char* pcParameterBuffer);

void kSetTimer(const char* pcParameterBuffer);
void kWaitUsingPIT(const char* pcParameterBuffer);
void kReadTimeStampCounter(const char* pcParameterBuffer);
void kMeasureProcessorSpeed(const char* pcParameterBuffer);
void kShowDateAndTime(const char* pcParameterBuffer);

#endif // __CONSOLE_SHELL_H__