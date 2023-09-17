#include "trace_hal.h"
#include "core_systick_hal.h"

void main(void)
{
    systick_init();
    trace_init();

    print("Print a %% symbol\n");
    print("Print %s string\n", "another");
    print("This one has %s in but it doesn't get confused\n", "a single % symbol");
    print("Multiple %s in %s statement\n", "specifiers", "one");
    print("%s, %s, %s", __FILE__, __LINE__, __func__);
    while(1) {}
}