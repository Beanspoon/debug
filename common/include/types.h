#ifndef TYPES_H
#define TYPES_H

#include <stdint-gcc.h>

#define RW_reg  volatile uint32_t
#define RO_reg  volatile const uint32_t

/**
 * @brief Bit state enum
 *
 */
typedef enum
{
    DISABLED,
    ENABLED
} tEnable;

#endif // TYPES_H