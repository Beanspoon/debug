#ifndef CLOCK_PRV_H
#define CLOCK_PRV_H

#include "types.h"

/**
 * @brief Clock tasks enum
 *
 */
typedef enum
{
    CLOCK_TASKS_HFCLKSTART,     // Start the high-frequency clock
    CLOCK_TASKS_HFCLKSTOP,      // Stop the high-frequency clock
    CLOCK_TASKS_LFCLKSTART,     // Start the low-frequency clock
    CLOCK_TASKS_LFCLKSTOP,      // Stop the low-frequency clock
    CLOCK_TASKS_CAL,            // Start calibration of the LFRC oscillator
    CLOCK_TASKS_CTSSTART,       // Start calibration timer
    CLOCK_TASKS_CTSTOP,         // Stop calibration timer
    CLOCK_TASKS_COUNT
} tClock_tasks;

/**
 * @brief Clock events enum
 *
 */
typedef enum
{
    CLOCK_EVENTS_HFCLKSTARTED,  // High-frequency clock is started
    CLOCK_EVENTS_LFCLKSTARTED,  // Low-frequency clock is started
    CLOCK_EVENTS_DONE = 3,      // Calibration of LFCLK RC oscillator complete
    CLOCK_EVENTS_CTTO,          // Calibration timer timed out
    CLOCK_EVENTS_COUNT
} tClock_events;

/**
 * @brief High-frequency clock source enum
 * 
 */
typedef enum
{
    CLOCK_HF_SOURCE_INTERNAL,   // Internal RC oscillator
    CLOCK_HF_SOURCE_CRYSTAL     // Crystal oscillator
} tClock_HfSource;

/**
 * @brief Low-frequency clock source enum
 *
 */
typedef enum
{
    CLOCK_LF_SOURCE_INTERNAL,  // Internal RC oscillator
    CLOCK_LF_SOURCE_CRYSTAL,   // Crystal oscillator
    CLOCK_LF_SOURCE_SYNTH,     // 32.768 kHz synthesised from high-frquency clock (only applicable to low-frequency clock)
} tClock_LfSource;

/**
 * @brief Clock state enum
 *
 */
typedef enum
{
    CLOCK_STATE_NOT_RUNNING,
    CLOCK_STATE_RUNNING
} tClock_state;

/**
 * @brief Structure of the HFCLKSTAT register
 *
 */
typedef struct
{
    const tClock_HfSource   source  : 1;    // Source of the high-frequency clock
    const uint16_t                  : 0;
    const tClock_state      state   : 1;    // State of the high-frequency clock
    const uint32_t                  : 0;
} tClock_hfClkStatReg;

/**
 * @brief Structure of the LFCLKSTAT register
 * This register is used for reading the clock configuration
 */
typedef struct
{
    const tClock_LfSource   source  : 2;    // Source of the low-frequency clock
    const uint16_t                  : 0;
    const tClock_state              : 1;    // State of the low-freqency clock
    const uint32_t                  : 0;
} tClock_lfClkStatReg;

/**
 * @brief Structure of the LFCLKSRC register
 * This register is used for configuring the clock
 */
typedef struct
{
    tClock_LfSource source      : 2;    // Source of the low-freqency clock
    uint16_t                    : 0;
    tEnable         bypass      : 1;    // Enable or disable bypass of the LFCLK xtal oscillator with external clock source
    tEnable         external    : 1;    // Enable or disable external source for LFCLK
} tClock_lfClkSrcReg;

/**
 * @brief Trace port speed enum
 *
 */
typedef enum
{
    CLOCK_TRACEPORT_SPEED_32MHZ,    // 32 MHz trace port clock (TRACECLK = 16 MHz)
    CLOCK_TRACEPORT_SPEED_16MHZ,    // 16 MHz trace port clock (TRACECLK = 8 MHz)
    CLOCK_TRACEPORT_SPEED_8MHZ,     // 8 MHz trace port clock (TRACECLK = 4 MHz)
    CLOCK_TRACEPORT_SPEED_4MHZ,     // 4 MHz trace port clock (TRACECLK = 2 MHz)
} tClock_tracePortSpeed;

/**
 * @brief Options for pin multiplexing of trace signals
 *
 */
typedef enum
{
    CLOCK_TRACEMUX_GPIO,        // GPIOs multiplexed onto all trace-pins
    CLOCK_TRACEMUX_SERIAL,      // SWO multiplexed onto P0.18, GPIO multiplexed onto other trace pins
    CLOCK_TRACEMUX_PARALLEL,    // TRACECLK and TRACEDATA multiplexed onto P0.20, P0.18, P0.16, P0.15 and P0.14
} tClock_traceMux;

typedef struct
{
    tClock_tracePortSpeed   tracePortSpeed  : 2;    // Speed of the trace port clock. TRACECLK pin will output this clock divided by 2
    uint16_t                                : 0;
    tClock_traceMux         traceMux        : 2;    // Pin multiplexing of trace signals
    uint32_t                                : 0;
} tClock_traceConfig;

/**
 * @brief Clock peripheral register map
 *
 */
typedef struct
{
    RW_reg              TASKS[CLOCK_TASKS_COUNT];     // 0x000-018 Tasks registers
    RO_reg              UNUSED_A[0x39];
    RW_reg              EVENTS[CLOCK_EVENTS_COUNT];   // 0x100-110 Events registers
    RO_reg              UNUSED_B[0x7C];
    RW_reg              INTENSET;                   // 0x304 Interrupt enable register
    RW_reg              INTENCLR;                   // 0x308 Interrupt clear register
    RO_reg              UNUSED_C[0x3F];
    RO_reg              HFCLKRUN;                   // 0x408 Indicates whether HFCLKSTART task has been triggered (0: not triggered, 1: triggered)
    tClock_hfClkStatReg HFCLKSTAT;                  // 0x40C High-frequency clock status
    RO_reg              UNUSED_D;
    RO_reg              LFCLKRUN;                   // 0x414 Indicates whether LFCLKSTART task has been triggered (0: not triggered, 1: triggered)
    tClock_lfClkStatReg LFCLKSTAT;                  // 0x418 Low-frequency clock status
    RO_reg              LFCLKSRCCOPY;               // 0x41C Copy of the two least significant bits of the LFCLKSRC register, set when LFCLKSTART is triggered
    RO_reg              UNUSED_E[0x3E];
    tClock_lfClkSrcReg  LFCLKSRC;                   // 0x518 Source configuration for low-frequency clock
    RO_reg              UNUSED_F[7];
    RW_reg              CTIV;                       // 0x538 Calibration timer interval register (retained). Value is multiples of 0.25 s. Range 0 - 127 (31.75 s)
    RO_reg              UNUSED_G[8];
    tClock_traceConfig  TRACECONFIG;                // 0x55C Clocking options for the trace port debug interface (retained)
} tClock_regMap;

#define CLOCK_BASE_ADDR     0x40000000
#define CLOCK               (*((volatile tClock_regMap *)CLOCK_BASE_ADDR))

#endif  // CLOCK_PRV_H