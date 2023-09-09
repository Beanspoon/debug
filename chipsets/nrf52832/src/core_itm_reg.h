#ifndef CORE_ITM_REG
#define CORE_ITM_REG

#include "types.h"
#include "utils.h"

typedef enum
{
    TRACE_PRIVILEGE_PORT_0_TO_7_MASK = 0x1,
    TRACE_PRIVILEGE_PORT_8_TO_15_MASK = 0x2,
    TRACE_PRIVILEGE_PORT_16_TO_23_MASK = 0x4,
    TRACE_PRIVILEGE_PORT_24_TO_31_MASK = 0x8
} tCoreItm_tracePrivilegeMasks;

typedef struct
{
    tEnable ITMENA  : 1;    // Bit[0] Enables the ITM
    tEnable TSENA   : 1;    // Bit[1] Enables local timestamp generation
    tEnable SYNCENA : 1;    // Bit[2] Enables synchronisation packet transmission for a synchronous TPIU
    tEnable TXENA   : 1;    // Bit[3] Enables forwarding of hardware event packets from the DWT to the ITM
    tEnable SWOENA  : 1;    // Bit[4] Enables asynchronous clocking of the timestamp coutner
} tCoreItm_tcrReg;

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