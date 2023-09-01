#ifndef UTILS_H
#define UTILS_H

#include <stdint-gcc.h>
#include <stddef.h>

#define ONE_SECOND_IN_MS    1000u

#define BITMASK(val)    (1U << val)

#define REG_NUM_FROM_ADDRESS(last, next)    (((next - last) / 4U) - 1U)

/**
 * @brief Copy data from source memory to destination memory
 * 
 * @param[in,out] pDest Pointer to the destination memory
 * @param[in] pSource Pointer to the source memory
 * @param[in] length Length of the data to be transferred
 */
void copyBytes( void *pDest, const void *pSource, size_t length );

/**
 * @brief Set length bytes starting at pMemory equal to setValue
 * 
 * @param[in,out] pMemory Pointer to the beginning of the memory to be set
 * @param[in] setValue Value to set the memory to
 * @param[in] length Number of bytes to set
 */
void setBytes(void *pMemory, const uint8_t setValue, size_t length);

#endif  // UTILS_H