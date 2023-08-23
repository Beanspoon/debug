#ifndef RNG_PRV_H
#define RNG_PRV_H

#include "types.h"

#include <stdint-gcc.h>

typedef struct
{
    tEnable VALRDY_STOP : 1; // Bit 0 - Shortcut between VALRDY event and STOP task
    RO_reg              : 0;
} tRng_shortsReg;

typedef enum
{
    RNG_INTERRUPT_VALRDY,
} tRng_interrupt;

typedef struct
{
    tEnable DERCEN  : 1;    // Bit 0 - Bias correction setting
    RO_reg          : 0;
} tRng_configReg;

typedef struct
{
    const uint8_t   VALUE   : 8;  // Bit 0-7 - Generated random number
    RO_reg                  : 0;
} tRng_valueReg;

typedef struct
{
    RW_reg          TASKS_START;    // 0x000 Task starting the random number generator
    RW_reg          TASKS_STOP;     // 0x004 Task stopping the random number generator
    RO_reg          UNUSED_A[0x3E];
    RW_reg          EVENTS_VALRDY;  // 0x100 Event being generated for every new random number written to the VALUE register
    RO_reg          UNUSED_B[0x3F];
    tRng_shortsReg  SHORTS;         // 0x200 Shortcut register
    RO_reg          UNUSED_C[0x40];
    RW_reg          INTENSET;       // 0x304 Interrupt enable register
    RW_reg          INTENCLR;       // 0x308 Interrupt disable register
    RO_reg          UNUSED_D[0x7E];
    tRng_configReg  CONFIG;         // 0x504 Configuration register
    tRng_valueReg   VALUE;          // 0x508 Random number output register
} tRng_regMap;

#define RNG_BASE_ADDRESS    0x4000D000
#define RNG                 (*((volatile tRng_regMap *)RNG_BASE_ADDRESS))

#endif