#ifndef CORE_DEBUG_REG
#define CORE_DEBUG_REG

#include "types.h"

typedef struct
{
    RO_reg          : 24;
    RW_reg  TRCENA  : 1;    // Bit[24] Global enable for all DWT and ITM features
    RO_reg          : 0;
} tCoreDebug_demcrReg;

typedef struct
{
    RO_reg  UNUSED_A[3];
    tCoreDebug_demcrReg DEMCR;  // 0x0C Debug exception and monitor control register
} tCoreDebug_regMap;

#define CORE_DEBUG_BASE_ADDRESS 0xE000EDF0
#define CORE_DEBUG  (*((volatile tCoreDebug_regMap *)CORE_DEBUG_BASE_ADDRESS))

#endif  // CORE_DEBUG_REG