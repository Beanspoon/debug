#include "maths_utils.h"

uint32_t power(uint32_t const base, uint32_t exponent)
{
    uint32_t result = 1U;
    for(; exponent > 0; --exponent)
    {
        result *= base;
    }
    return result;
}