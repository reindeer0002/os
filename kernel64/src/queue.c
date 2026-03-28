#include "queue.h"
#include "utility.h"

void kInitializeQueue(QUEUE* pstQueue, void* pvQueueBuffer, int iMaxDataCount, int iDataSize) {
    pstQueue->iMaxDataCount = iMaxDataCount;
    pstQueue->iDataSize = iDataSize;
    pstQueue->pvQueueArray = pvQueueBuffer;
    pstQueue->iPutIndex = 0;
    pstQueue->iGetIndex = 0;
    pstQueue->bLastOperationPut = FALSE;
}

BOOL kIsQueueFull(const QUEUE* pstQueue) {
    if (pstQueue->iPutIndex == pstQueue->iGetIndex && pstQueue->bLastOperationPut) {
        return TRUE;
    }
    return FALSE;
}

BOOL kIsQueueEmpty(const QUEUE* pstQueue) {
    if (pstQueue->iPutIndex == pstQueue->iGetIndex && !pstQueue->bLastOperationPut) {
        return TRUE;
    }
    return FALSE;
}

BOOL kPutQueue(QUEUE* pstQueue, const void* pvData) {
    if (kIsQueueFull(pstQueue)) {
        return FALSE;
    }
    kMemCpy((char*) pstQueue->pvQueueArray + (pstQueue->iPutIndex * pstQueue->iDataSize), pvData, pstQueue->iDataSize);
    pstQueue->iPutIndex = (pstQueue->iPutIndex + 1) % pstQueue->iMaxDataCount;
    pstQueue->bLastOperationPut = TRUE;
    return TRUE;
}

BOOL kGetQueue(QUEUE* pstQueue, void* pvData) {
    if (kIsQueueEmpty(pstQueue)) {
        return FALSE;
    }
    kMemCpy(pvData, (char*) pstQueue->pvQueueArray + (pstQueue->iGetIndex * pstQueue->iDataSize), pstQueue->iDataSize);
    pstQueue->iGetIndex = (pstQueue->iGetIndex + 1) % pstQueue->iMaxDataCount;
    pstQueue->bLastOperationPut = FALSE;
    return TRUE;
}
