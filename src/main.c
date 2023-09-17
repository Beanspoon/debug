#include "trace_hal.h"
#include "core_systick_hal.h"

void main(void)
{
    systick_init();
    trace_init();

    while(1){
        print("\"%%%%\" prints a '%%' symbol\n");
        print("\"%%s\" prints a string: %s\n", "Hello I am another string");
        print("This one has %s in the argument string but it doesn't get confused\n", "a single '%' symbol");
        print("This one has multiple %s in %s statement\n", "specifiers", "one");
        print("\n");
    }

    while(1) {}
}