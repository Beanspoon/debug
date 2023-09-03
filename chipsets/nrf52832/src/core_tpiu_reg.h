#ifndef CORE_TPIU_REG
#define CORE_TPIU_REG

#include "types.h"
#include "utils.h"

typedef enum
{
    TPIU_SPPR_TXMODE_PARALLEL,
    TPIU_SPPR_TXMODE_SWO_MANCHESTER,
    TPIU_SPPR_TXMODE_SWO_NRZ
} tCoreTpiu_SelectedPinProtocol;

typedef struct
{
    tCoreTpiu_SelectedPinProtocol TXMODE    : 2;    // Bit[0-1] Protocol for trace output
    RO_reg                                  : 0;
} tCoreTpiu_spprReg;

typedef struct
{
    RO_reg  TPIU_SSPSR; // 0x000 Supported parallel port size register
    RW_reg  TPIU_CSPCR; // 0x004 Current parallel port size register
    RO_reg  UNUSED_A[REG_NUM_FROM_ADDRESS(0x004, 0x010)];
    RW_reg  TPIU_ACPR;  // 0x010 Asynchronous clock prescaler register. Divisor is prescaler + 1
    RO_reg  UNUSED_B[REG_NUM_FROM_ADDRESS(0x010, 0x0F0)];
    tCoreTpiu_spprReg TPIU_SPPR;    // 0x0F0 Selected pin protocol register
} tCoreTpiu_regMap;

#define CORE_TPIU_BASE_ADDRESS  0xE0040000
#define CORE_TPIU   (*((volatile tCoreTpiu_regMap *)CORE_TPIU_BASE_ADDRESS))

#endif // CORE_TPIU_REG