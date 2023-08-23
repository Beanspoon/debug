#include "core_nvic_hal.h"

#include "types.h"

#include <stdint-gcc.h>

#define NVIC_BASE_ADDR  0xE000E004

typedef struct
{
    RO_reg  ICTR;               // 0x004 Interrupt controller type register
    RO_reg  RESERVED_A[0x3E];
    RW_reg  ISER[8];            // 0x100-11C Interrupt set-enable registers
    RO_reg  RESERVED_B[0x18];
    RW_reg  ICER[8];            // 0x180-19C Interrupt clear-enable registers
    RW_reg  ISPR[8];            // 0x200-21C Interrupt set-pending registers
    RO_reg  RESERVED_C[0x18];
    RW_reg  ICPR[8];            // 0x280-29C Interrupt clear-pending registers
    RO_reg  IABR[8];            // 0x300-31C Interrupt active bit register
    RO_reg  RESERVED_D[0x38];
    RW_reg  IPR[60];            // 0x400-4EC Interrupt priority registers
} tNvic_regMap;

#define NVIC        (*((tNvic_regMap *)NVIC_BASE_ADDR))

void nvic_changeInterruptState( const tNvic_interrupt interrupt, const tEnable targetState )
{
    uint8_t registerNumber = interrupt / 32u;
    uint8_t bitNumber = interrupt % 32u;

    RW_reg *targetRegSet = (ENABLED == targetState) ? NVIC.ISER : NVIC.ICER;
    targetRegSet[registerNumber] = (1u << bitNumber);
}