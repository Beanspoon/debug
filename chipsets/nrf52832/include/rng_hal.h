#ifndef RNG_HAL_H
#define RNG_HAL_H

#include <stddef.h>

/**
 * @brief Value indicating the status of an operation
 * 
 */
typedef enum
{
    RNG_STATUS_OK,
    RNG_STATUS_ERROR,
} tRng_status;

/**
 * @brief Initialise the RNG peripheral
 * 
 */
void rng_init(void);

/**
 * @brief Generate a random value and place it in the buffer
 *  This function blocks execution until the random number is generated
 * 
 * @param[in,out]   buffer the buffer into which the value should be placed
 * @param[in]       size the size of the buffer in bytes
 */
tRng_status rng_generate(void *buffer, const size_t size);

#endif  // RNG_HAL_H