#ifndef GPIO_PRV_H
#define GPIO_PRV_H

#include "gpio_hal.h"

#include "types.h"

#include <stdint-gcc.h>

/**
 * @brief Pin direction enum
 *
 */
typedef enum
{
    GPIO_DIR_INPUT,
    GPIO_DIR_OUTPUT
} tGpio_dir;

/**
 * @brief Input buffer setting enum
 *
 */
typedef enum
{
    GPIO_INBUF_CONNECT,
    GPIO_INBUF_DISCONNECT
} tGpio_inBuf;

/**
 * @brief Definition of pin cofiguration registers
 * 
 */
typedef struct
{
    tGpio_dir   DIR             : 1;    // Bit[0] Pin direction
    tGpio_inBuf INPUT_BUFFER    : 1;    // Bit[1] Pin input buffer configuration
    tGpio_pull  PULL            : 2;    // Bit[2-3] Pin pull direction
    uint8_t                     : 0;
    tGpio_drive DRIVE           : 3;    // Bit[8-10] Pin drive configuration
    uint8_t                     : 0;
    tGpio_sense SENSE           : 2;    // Bit[16-17] Pin sense configuration
    RO_reg                      : 0;
} tGpio_pinCnfReg;

/**
 * @brief Definition of GPIO register map
 *
 */
typedef struct
{
    RO_reg          RESERVED_A[0x141];
    RW_reg          OUT;           // 0x504 Write GPIO port
    RW_reg          OUTSET;        // 0x508 Set individual bits in GPIO port
    RW_reg          OUTCLR;        // 0x50C Clear individual bits in GPIO port
    RO_reg          IN;            // 0x510 Read GPIO port
    RW_reg          DIR;           // 0x514 Direction of GPIO pins
    RW_reg          DIRSET;        // 0x518 Direction set register (sets pin to output)
    RW_reg          DIRCLR;        // 0x51C Direction clear register (sets pin to input)
    RW_reg          LATCH;         // 0x520 Latch register indicating which GPIO pins have met criteria set in PIN_CNF[n].SENSE. Write '1' to clear
    RW_reg          DETECTMODE;    // 0x524 Select between default DETECT signal behaviour (0) and LDETECT mode (1)
    RO_reg          RESERVED_B[0x76];
    tGpio_pinCnfReg PINCNF[32];    // 0x700-77C Configuration of GPIO pins
} tGpio_regMap;

#define GPIO_BASE_ADDRESS   0x50000000
#define GPIO                (*((volatile tGpio_regMap *)GPIO_BASE_ADDRESS))

#define GPIOTE_CHANNEL_COUNT    8U

/**
 * @brief Definition of the GPIOTE interrupt register
*/
typedef struct
{
    tEnable IN0     : 1; // Bit[0] Enable/disable interrupt for event on channel 0
    tEnable IN1     : 1; // Bit[1] Enable/disable interrupt for event on channel 1
    tEnable IN2     : 1; // Bit[2] Enable/disable interrupt for event on channel 2
    tEnable IN3     : 1; // Bit[3] Enable/disable interrupt for event on channel 3
    tEnable IN4     : 1; // Bit[4] Enable/disable interrupt for event on channel 4
    tEnable IN5     : 1; // Bit[5] Enable/disable interrupt for event on channel 5
    tEnable IN6     : 1; // Bit[6] Enable/disable interrupt for event on channel 6
    tEnable IN7     : 1; // Bit[7] Enable/disable interrupt for event on channel 7
    RO_reg          : 23;
    tEnable PORT    : 1; // Bit[31] Enable/disable interrupt for PORT event
} tGpiote_interruptReg;

/**
 * @brief GPIOTE mode enum
*/
typedef enum
{
    GPIOTE_MODE_DISABLED,
    GPIOTE_MODE_EVENT,
    GPIOTE_MODE_TASK = 3
} tGpiote_mode;

/**
 * @brief GPIOTE polarity enum
*/
typedef enum
{
    GPIOTE_POLARITY_NONE,
    GPIOTE_POLARITY_LOTOHI,
    GPIOTE_POLARITY_HITOLO,
    GPIOTE_POLARITY_TOGGLE
} tGpiote_polarity;

/**
 * @brief Definition of GPIOTE configuration register
*/
typedef struct
{
    tGpiote_mode    MODE    : 2;    // Mode in which to configure the channel
    uint8_t                 : 0;
    RW_reg          PSEL    : 5;    // Pin selection for the channel
    uint16_t                : 0;
    tGpiote_polarity    POLARITY    : 2;    // Tasks: operation to perform on triggering; Events: operation which will trigger on interrupt
    tGpio_pinState  OUTINIT : 1;    // Intial state of pin when channel is configured
} tGpiote_configReg;


/**
 * @brief Definition of GPIO Tasks and Events register map
*/
typedef struct
{
    RW_reg  TASKS_OUT[GPIOTE_CHANNEL_COUNT];    // 0x000-01C Tasks for performing action to pin specified in CONFIG[n]
    RO_reg  RESERVED_A[4];
    RW_reg  TASKS_SET[GPIOTE_CHANNEL_COUNT];    // 0x030-04C Tasks for writing pin specified in CONFIG[n] high
    RO_reg  RESERVED_B[4];
    RW_reg  TASKS_CLR[GPIOTE_CHANNEL_COUNT];    // 0x060-07C Tasks for writing pin specified in CONFIG[n] low
    RO_reg  RESERVED_C[0x20];
    RO_reg  EVENTS_IN[GPIOTE_CHANNEL_COUNT];    // 0x100-11C Events generated from pin specifed in CONFIG[n]
    RO_reg  RESERVED_D[0x17];
    RO_reg  EVENTS_PORT;                        // 0x17C Event generated from multiple GPIO pins with SENSE mechanism enabled
    RO_reg  RESERVED_E[0x61];
    tGpiote_interruptReg    INTENSET;           // 0x304 Set interrupt active for channels
    tGpiote_interruptReg    INTENCLR;           // 0x308 Clear interrupt active for channels
    RO_reg  RESERVED_F[0x81];
    tGpiote_configReg   CONFIG[GPIOTE_CHANNEL_COUNT];   // 0x510-52C Configuration for tasks and events
} tGpiote_regMap;

#define GPIOTE_BASE_ADDRESS 0x40006000
#define GPIOTE              (*((volatile tGpiote_regMap *)GPIOTE_BASE_ADDRESS))

#endif  // GPIO_PRV_H