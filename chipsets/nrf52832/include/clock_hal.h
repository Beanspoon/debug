#ifndef CLOCK_HAL_H
#define CLOCK_HAL_H

/**
 * @brief Start the high-frequency clock
 * 
 * The CLOCK_EVENTS_HFCLKSTARTED event will be generated when the clock is started
 */
void clock_startHFClock(void);

#endif // CLOCK_HAL_H