#ifndef CORE_SYSTICK_PRV_H
#define CORE_SYSTICK_PRV_H

#include "types.h"

#include <stdint-gcc.h>
#include <stdbool.h>

/**
 * @brief Systick clock source enum
 * 
 */
typedef enum
{
    SYSTICK_SOURCE_EXTERNAL,
    SYSTICK_SOURCE_PROCESSOR
} tSystick_clockSource;

/**
 * @brief Systick control and status register
 *
 */
typedef struct
{
    tEnable                 CSR_SYST_EN     : 1;    // Bit[0] Status of the counter
    tEnable                 CSR_TICKINT     : 1;    // Bit[1] Interrupt enable for counter=0
    tSystick_clockSource    CSR_CLKSOURCE   : 1;    // Bit[2] Systick clock source
    const uint16_t                          : 0;
    const bool              CSR_COUNTFLAG   : 1;    // Bit[16] Indicates if counter has reached 0 since last read of this register
    RO_reg                                  : 0;
} tSystick_csrReg;

/**
 * @brief Systick calibration value register
 *
 */
typedef struct
{
    RO_reg  CALIB_TENMS     : 24;   // Bit[0-23] Optionally holds a reload value to be used for 10 ms (100 Hz) timing, subject to skew errors
    RO_reg                  : 5;
    RO_reg  CALIB_SKEW      : 1;    // Bit[30] Indicates whether the CALIB_TENMS value is exact; 0: exact, 1: inexact
    RO_reg  CALIB_NOREF     : 1;    // Bit[31] Indicates whether the external reference clock is defined; 0: implemented, 1: not implemented
} tSystick_calibReg;

/**
 * @brief Systick register map
 *
 */
typedef struct
{
    tSystick_csrReg     SYST_CSR;   // 0x00 Control and status register
    RW_reg              SYST_RVR;   // 0x04 Reload value register
    RW_reg              SYST_CVR;   // 0x08 Current value register
    tSystick_calibReg   SYST_CALIB; // 0x0C Calibration value register
} tSystick_regMap;

#define CORE_SYSTICK_BASE_ADDR  0xE000E010
#define CORE_SYSTICK            (*((volatile tSystick_regMap *) CORE_SYSTICK_BASE_ADDR))

#endif  // CORE_SYSTICK_PRV_H