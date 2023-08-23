#ifndef FIFO_H
#define FIFO_H

#include <stddef.h>
#include <stdint-gcc.h>
#include <stdbool.h>

/**
 * @brief Status value returned from FIFO buffer functions indicating
 *  the status of the operation
 */
typedef enum
{
    FIFO_STATUS_OK,     // Operation completed successfully
    FIFO_STATUS_ERROR,  // Operation failed
    FIFO_STATUS_EMPTY,  // Circular buffer was empty
    FIFO_STATUS_FULL,   // Circular buffer was full
} tFifo_status;

/**
 * @brief Generic structure of a FIFO buffer instance - used by FIFO buffer
 *  functions to carry out the specified operation
 */
typedef struct
{
    uint32_t        numSlotsEmpty;      // Number of empty slots remaining
    void *          pRead;              // Read pointer
    void *          pWrite;             // Write pointer
    const void *    pBuffer;            // Pointer to the buffer in memory
    size_t          slotSize;           // Size of the slots in bytes
    size_t          numSlots;           // Number of slots in the buffer
    bool            overwriteAllowed;   // Is writing to a full buffer allowed?
} tFifo_instance;

/**
 * @brief Initialise a fifo buffer instance by populating the instance struct
 * 
 * @param[out] instance Pointer to the fifo instance struct to be initialised
 * @param[in] array The array acting as the physical memory for the fifo buffer
 * @param[in] numSlotsInArray Size of the array in number of slots
 * @param[in] slotSize Size of an element in bytes
 * @param[in] allowOverwrite Enables/disables overwriting of the oldest element in a full buffer
 * 
 * @return tFifo_status FIFO_STATUS_OK if instance was initialised successfully
 *                      FIFO_STATUS_ERROR if initialisation failed
 */
tFifo_status fifo_initialise(tFifo_instance * const pInstance,
                                void * const array,
                                const size_t numSlotsInArray,
                                const size_t slotSize,
                                const bool allowOverwrite);

/**
 * @brief Write a new element to the FIFO buffer
 * 
 * @param[in,out] pInstance Pointer to the instance of the FIFO buffer
 * @param[in] pElement Pointer to the element to write
 * @return tFifo_status OK if operation successful
 *                      ERROR if operation failed
 *                      FULL if FIFO buffer was full
 * If allowOverwrite is true, FULL indicates that the write operation was completed, but
 * the oldest element was overwritten.
 * If allowOverwrite is false, FULL indicates that the write operation failed as the buffer
 * was already full.
 */
tFifo_status fifo_write(tFifo_instance * const pInstance, const void * const pElement);

/**
 * @brief Peek the oldest element on the FIFO buffer and leave the element in the
 *  buffer
 *
 * @param pInstance Pointer to the instance of the FIFO buffer
 * @param pPeekBuffer Pointer to the buffer to copy the element into
 *
 * @return tFifo_status OK if successful
 *                      ERROR if failed
 *                      EMPTY if operation failed due to FIFO buffer being empty
 */
tFifo_status fifo_peek(tFifo_instance * const pInstance, void * const pPeekBuffer);

/**
 * @brief Read the oldest element on the FIFO buffer, removing it
 *
 * @param pInstance Pointer to the instance of the FIFO buffer
 * @param pReadBuffer Pointer to the buffer to copy the element into
 *
 * @return tFifo_status OK if successful
 *                      ERROR if failed
 *                      EMPTY if operation failed due to FIFO buffer being empty
 */
tFifo_status fifo_read(tFifo_instance * const pInstance, void * const pReadBuffer);

/**
 * @brief Read or peek the oldest element from the FIFO buffer
 * 
 * @param[in,out] pInstance Pointer to the instance of the FIFO buffer
 * @param[in] pReadBuffer Pointer to buffer to copy the read element into
 * @param[in] peek If true, leave the element on the buffer. If false, remove the element 
 *  from the buffer
 * @return tFifo_status OK if successful
 *                      ERROR if failed
 *                      EMPTY if operation failed due to buffer being empty
 */
tFifo_status fifo_readPeek(tFifo_instance * const pInstance, void * const pBuffer, const bool peek);

/**
 * @brief Empty the FIFO buffer
 * 
 * @param[in,out] pInstance Pointer to the instance of the FIFO buffer
 * @return tFifo_status OK if operation is successful
 *                      ERROR if operation failed
 */
tFifo_status fifo_clear(tFifo_instance * const pInstance);

/**
 * @brief Get the status of the FIFO buffer
 * 
 * @param[in,out] pInstance Pointer to the instance of the FIFO buffer
 * @return tFifo_status OK if the buffer contains data but is not full
 *                      ERROR if there was a problem retrieving the buffer status
 *                      EMPTY if the buffer is empty
 *                      FULL if the buffer is full
 */
tFifo_status fifo_getStatus(const tFifo_instance * const pInstance);

/**
 * @brief Get the number of empty slots in a buffer
 *
 * @param[in] pInstance Pointer to the instance of the FIFO buffer
 *
 * @return The number of empty slots
 */
uint32_t fifo_numEmptySlots(const tFifo_instance * const pInstance);

#endif  // FIFO_H
