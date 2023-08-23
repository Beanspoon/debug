#include "panic.h"

#include "core_systick_hal.h"
#include "board_ctrl.h"

#include "board_cfg.h"

#include <stdint-gcc.h>

void panic_handler(const char *filename, const uint16_t lineNumber)
{
    systick_init();
    boardCtrl_configureBoard();
    while(1)
    {
        boardCtrl_ledActive(LED0);
        boardCtrl_ledActive(LED1);
        systick_busyWait(1000u);
        boardCtrl_ledInactive(LED0);
        boardCtrl_ledInactive(LED1);
        systick_busyWait(1000u);
    }
}