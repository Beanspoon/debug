#ifndef CORE_ITM_REG
#define CORE_ITM_REG

#include "types.h"
#include "utils.h"

typedef struct
{
    RW_reg  ITM_STIM[32];   // 0x000 - 07C Stimulus port registers
    RO_reg  UNUSED_A[REG_NUM_FROM_ADDRESS(0x7C, 0xE00)];
    RW_reg  ITM_TER;        // 0xE00 Trace enable register
    RO_reg  UNUSED_B[REG_NUM_FROM_ADDRESS(0xE00, 0xE40)];
    RW_reg  ITM_TPR;        // 0xE40 Trace privilege register
    RO_reg  UNUSED_C[REG_NUM_FROM_ADDRESS(0xE40, 0xE80)];
    RW_reg  ITM_TCR;        // 0xE80 Trace control register
} tCoreItm_regMap;

#define CORE_ITM_BASE_ADDRESS   0xE0000000
#define CORE_ITM    (*((volatile tCoreItm_regMap *)CORE_ITM_BASE_ADDRESS))

#endif  // CORE_ITM_REG