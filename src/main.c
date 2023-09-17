#include "trace_hal.h"
#include "core_systick_hal.h"

void main(void)
{
    systick_init();
    trace_init();

    while(1)
    {
        traceOut("Trace is cool\n");
        systick_busyWait(1000U);
    }
}