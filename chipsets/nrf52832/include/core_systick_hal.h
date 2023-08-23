#ifndef CORE_SYSTICK_HAL_H
#define CORE_SYSTICK_HAL_H

#include "board_cfg.h"

#include <stdint-gcc.h>

#ifndef SYSTICK_TICK_FREQUENCY_HZ
#error SYSTICK_TICK_FREQUENCY_HZ is not defined!
#endif

#ifndef CORE_CLOCK_FREQUENCY_HZ
#error CORE_CLOCK_FREQUENCY_HZ is not defined!
#endif

/**
 * @brief Initialise the systick
 * 
 */
void systick_init(void);

/**
 * @brief Delay execution for the given number of milliseconds
 * 
 * @param delay_ms The number of milliseconds to wait
 */
void systick_busyWait(uint32_t delay_ms);

#endif  // CORE_SYSTICK_HAL_H