#include "fifo.h"

#include "utils.h"

#include <stdint-gcc.h>

/**
 * @brief Find the next location for the pointer given that it will be advanced by one element
 * This will take into account wrapping if the end of the buffer is reached
 * 
 * @param[in] pointer The pointer in question
 * @param pInstance Pointer to the FIFO buffer instance with which the pointer is associated
 * @return void* indicating the new address to which the pointer will be pointing
 */
static void* getNextLocationForPointer(const void* const pointer, const tFifo_instance* const pInstance)
{
    const uint8_t * const pByteAligned = (uint8_t *)pointer;
    const uint8_t *pNextLocation = pByteAligned + pInstance->slotSize;
    const size_t bufferSize_bytes = pInstance->slotSize * pInstance->numSlots;
    const uint8_t * const pStart = (uint8_t *)pInstance->pBuffer;
    pNextLocation = (pNextLocation < pStart + bufferSize_bytes) ? pNextLocation : pStart;
    return (void *)pNextLocation;
}

tFifo_status fifo_initialise(tFifo_instance * const pInstance,
                                void * const array,
                                const size_t numSlotsInArray,
                                const size_t slotSize,
                                const bool allowOverwrite)
{
    if((pInstance == NULL) ||
        (array == NULL) ||
        (numSlotsInArray == 0u) ||
        (slotSize == 0u))
    {
        return FIFO_STATUS_ERROR;
    }

    pInstance->pBuffer = array;
    pInstance->pRead = array;
    pInstance->pWrite = array;
    pInstance->numSlots = numSlotsInArray;
    pInstance->numSlotsEmpty = numSlotsInArray;
    pInstance->slotSize = slotSize;
    pInstance->overwriteAllowed = allowOverwrite;

    return FIFO_STATUS_OK;
}

tFifo_status fifo_write(tFifo_instance* const pInstance, const void* const pElement)
{
    const tFifo_status instanceStatus = fifo_getStatus(pInstance);
    if(instanceStatus == FIFO_STATUS_ERROR)
    {
        // Early return for error state
        return FIFO_STATUS_ERROR;
    }

    if((instanceStatus == FIFO_STATUS_FULL) && !pInstance->overwriteAllowed)
    {
        // Early return if buffer is full and overwriting is forbidden
        return FIFO_STATUS_FULL;
    }

    copyBytes(pInstance->pWrite, pElement, pInstance->slotSize);

    pInstance->pWrite = getNextLocationForPointer(pInstance->pWrite, pInstance);
    bool hasBecomeFull = (pInstance->pWrite == pInstance->pRead);

    if(pInstance->numSlotsEmpty == 0U)
    {
        // Read pointer must also be updated as buffer was full
        //  and oldest element has been overwritten
        pInstance->pRead = getNextLocationForPointer(pInstance->pRead, pInstance);
    }
    else
    {
        --(pInstance->numSlotsEmpty);
    }

    return FIFO_STATUS_OK;
}

tFifo_status fifo_peek(tFifo_instance * const pInstance, void * const pPeekBuffer)
{
    return fifo_readPeek(pInstance, pPeekBuffer, true);
}

tFifo_status fifo_read(tFifo_instance * const pInstance, void * const pReadBuffer)
{
    return fifo_readPeek(pInstance, pReadBuffer, false);
}

tFifo_status fifo_readPeek(tFifo_instance* const pInstance, void * const pBuffer, const bool peek)
{
    const tFifo_status instanceStatus = fifo_getStatus(pInstance);
    if(instanceStatus == FIFO_STATUS_ERROR ||
        pBuffer == NULL)
    {
        // Early return due to invalid arguments
        return FIFO_STATUS_ERROR;
    }
    else if(instanceStatus == FIFO_STATUS_EMPTY)
    {
        // Early return as there is nothing to read
        return FIFO_STATUS_EMPTY;
    }

    copyBytes(pBuffer, pInstance->pRead, pInstance->slotSize);

    if(!peek)
    {
        pInstance->pRead = getNextLocationForPointer(pInstance->pRead, pInstance);
        ++(pInstance->numSlotsEmpty);
    }

    return FIFO_STATUS_OK;
}

tFifo_status fifo_clear(tFifo_instance* const pInstance)
{
    if(fifo_getStatus(pInstance) == FIFO_STATUS_ERROR)
    {
        // Early return due to invalid arguments
        return FIFO_STATUS_ERROR;
    }

    // Move read pointer to write pointer - indicates FIFO buffer is empty
    pInstance->pRead = pInstance->pWrite;
    pInstance->numSlotsEmpty = pInstance->numSlots;

    return FIFO_STATUS_OK;
}

tFifo_status fifo_getStatus(const tFifo_instance* const pInstance)
{
    // Early return for invalid argument
    if(pInstance == NULL ||
        pInstance->pRead == NULL ||
        pInstance->pWrite == NULL)
    {
        return FIFO_STATUS_ERROR;
    }

    if(pInstance->pRead == pInstance->pWrite)
    {
        // If the pointers point to the same element, the buffer is either empty or full
        return (pInstance->numSlotsEmpty == 0U ? FIFO_STATUS_FULL : FIFO_STATUS_EMPTY);
    }
    else
    {
        return FIFO_STATUS_OK;
    }
}

uint32_t fifo_numEmptySlots(const tFifo_instance * const pInstance)
{
    return pInstance->numSlotsEmpty;
}
