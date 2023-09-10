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

typedef enum
{
    TSPRESCALE_NONE,
    TSPRESCALE_DIVIDE_BY_4,
    TSPRESCALE_DIVIDE_BY_16,
    TSPRESCALE_DIVIDE_BY_64
} tCoreItm_timestampPrescaler;

typedef enum
{
    GTSFREQ_DISABLE,
    GTSFREQ_ON_LOW_BITS,    // Approx every 128 cycles
    GTSFREQ_ON_HIGH_BITS,   // Approx every 8192 cycles
    GTSFREQ_ON_PACKET       // After every packet if FIFO is empty
} tCoreItm_gtsFreq;

typedef struct
{
    tEnable ITMENA  : 1;    // Bit[0] Enables the ITM
    tEnable TSENA   : 1;    // Bit[1] Enables local timestamp generation
    tEnable SYNCENA : 1;    // Bit[2] Enables synchronisation packet transmission for a synchronous TPIU
    tEnable TXENA   : 1;    // Bit[3] Enables forwarding of hardware event packets from the DWT to the ITM
    tEnable SWOENA  : 1;    // Bit[4] Enables asynchronous clocking of the timestamp counter
    const uint8_t   : 0;
    tCoreItm_timestampPrescaler TSPRESCALE  : 2;    // Bit[8-9] Local timestamp prescaler, used with trace packet reference clock
    tCoreItm_gtsFreq    GTSFREQ : 2;    // Bit[10-11] Global timestamp frequency. Defines how often ITM generates a global timestamp
    const uint8_t   : 0;
    const uint8_t   : 0;
    RO_reg  BUSY    : 1;    // Bit[23] Indicates whether the ITM is currently processing events
    RO_reg          : 0;
} tCoreItm_tcrReg;

typedef struct
{
    RW_reg  ITM_STIM[32];   // 0x000 - 07C Stimulus port registers
    RO_reg  UNUSED_A[REG_NUM_FROM_ADDRESS(0x7C, 0xE00)];
    RW_reg  ITM_TER;        // 0xE00 Trace enable register
    RO_reg  UNUSED_B[REG_NUM_FROM_ADDRESS(0xE00, 0xE40)];
    RW_reg  ITM_TPR;        // 0xE40 Trace privilege register
    RO_reg  UNUSED_C[REG_NUM_FROM_ADDRESS(0xE40, 0xE80)];
    tCoreItm_tcrReg ITM_TCR;        // 0xE80 Trace control register
} tCoreItm_regMap;

#define CORE_ITM_BASE_ADDRESS   0xE0000000
#define CORE_ITM    (*((volatile tCoreItm_regMap *)CORE_ITM_BASE_ADDRESS))

#endif  // CORE_ITM_REG