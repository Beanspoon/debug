#include "rng_hal.h"
#include "rng_prv.h"

#include "utils.h"

#include <stddef.h>
#include <stdint-gcc.h>

void rng_init(void)
{
    RNG.CONFIG.DERCEN = ENABLED;
}

tRng_status rng_generate(void *pBuffer, const size_t size)
{
    if(NULL == pBuffer)
    {
        return RNG_STATUS_ERROR;
    }
    
    uint8_t *pBufferByte = pBuffer;
    RNG.TASKS_START = ENABLED;
    RNG.EVENTS_VALRDY = 0U;

    for(size_t bufferOffset = 0U; bufferOffset < size; ++bufferOffset)
    {
        while(!RNG.EVENTS_VALRDY) { /* Block execution until value is ready */ }
        pBufferByte[bufferOffset] = RNG.VALUE.VALUE;
        RNG.EVENTS_VALRDY = 0u;
    }

    return RNG_STATUS_OK;
}