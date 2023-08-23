#include "clock_hal.h"

#include "clock_prv.h"

#include "types.h"

void clock_startHFClock(void)
{
    CLOCK.EVENTS[CLOCK_EVENTS_HFCLKSTARTED] = 0u;
    CLOCK.TASKS[CLOCK_TASKS_HFCLKSTART] = ENABLED;
}