#ifndef PANIC_H
#define PANIC_H

#include <stdint-gcc.h>

void panic_handler(const char *filename, const uint16_t line);
#define panic()     (panic_handler(__FILE__, __LINE__))

#define expect_or_panic(expected, functionCall)     {if(expected != functionCall) { panic(); }}

#endif  // PANIC_H