#include "trace_hal.h"
#include "core_systick_hal.h"

void main(void)
{
    systick_init();
    trace_init();

    uint32_t counter = 1U;
    while(1){
        print("This is a test for the home-made va_args: %u %u %u %u %u %u\n", 1, 12, 123, 1234, 12345, 1234567890);
        print("\"%%%%\" prints a '%%' symbol\n");
        print("\"%%s\" prints a string: %s\n", "Hello I am another string");
        print("This one has %s in the argument string but it doesn't get confused\n", "a single '%' symbol");
        print("This one has multiple %s in %s statement\n", "specifiers", "one");
        print("This is on line %u in file %s\n", __LINE__, __FILE__);
        print("These messages have been reported %u times\n", counter);
        print("\n");
        systick_busyWait(1000U);
        ++counter;
    }

    while(1) {}
}