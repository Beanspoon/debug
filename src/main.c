#include "trace_hal.h"
#include "core_systick_hal.h"

void main(void)
{
    systick_init();
    trace_init();

    traceOut("Print a %% symbol\n");
    traceOut("Print %s string\n", "another");
    traceOut("This one has %s in but it doesn't get confused", "a single % symbol");
    while(1) {}
}