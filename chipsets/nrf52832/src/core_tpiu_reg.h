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
    RO_reg          : 1;
    tEnable EnFCont : 1;    // Bit[1] Enable continuous formatting
    const uint8_t   : 0;
    RO_reg TrigIn   : 1;    // Bit[8] This bit RAO, specifying that triggers are insterted when a trigger pin is asserted
    RO_reg          : 0;
} tCoreTpiu_ffcrReg;

typedef struct
{
    RO_reg  TPIU_SSPSR; // 0x000 Supported parallel port size register
    RW_reg  TPIU_CSPCR; // 0x004 Current parallel port size register
    RO_reg  UNUSED_A[REG_NUM_FROM_ADDRESS(0x004, 0x010)];
    RW_reg  TPIU_ACPR;  // 0x010 Asynchronous clock prescaler register. Divisor is prescaler + 1
    RO_reg  UNUSED_B[REG_NUM_FROM_ADDRESS(0x010, 0x0F0)];
    tCoreTpiu_spprReg   TPIU_SPPR;    // 0x0F0 Selected pin protocol register
    RO_reg  UNUSED_C[REG_NUM_FROM_ADDRESS(0x0F0, 0x300)];
    RO_reg  TPIU_FFSR;  // 0x300 Formatter and flush status register
    tCoreTpiu_ffcrReg   TPIU_FFCR;  // 0x304 Formatter and flush control register
    RO_reg  TPIU_FSCR;  // 0x308 Formatter synchronisation counter register
    RO_reg  UNUSED_D[REG_NUM_FROM_ADDRESS(0x308, 0xEE8)];
    RO_reg  TRIGGER;    // 0xEE8 Register corresponding to the TRIGGER input
} tCoreTpiu_regMap;

#define CORE_TPIU_BASE_ADDRESS  0xE0040000
#define CORE_TPIU   (*((volatile tCoreTpiu_regMap *)CORE_TPIU_BASE_ADDRESS))

#endif // CORE_TPIU_REG