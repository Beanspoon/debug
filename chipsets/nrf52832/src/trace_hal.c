#include "core_debug_reg.h"
#include "core_itm_reg.h"
#include "core_tpiu_reg.h"
#include "clock_prv.h"

#include "utils.h"

#include "chip_cfg.h"

#include <stdarg.h>
#include <stdbool.h>

static void parseFormatSpecifier(char const * currentChar, va_list args);

void trace_init(void)
{
    CORE_DEBUG.DEMCR.TRCENA = ENABLED;

    CORE_TPIU.TPIU_SPPR.TXMODE = TPIU_SPPR_TXMODE_SWO_NRZ;
    CORE_TPIU.TPIU_ACPR = (CORE_CLOCK_FREQUENCY_HZ/CORE_CLOCK_TRACEPORT_SPEED_HZ) - 1;

    CORE_ITM.ITM_TCR.ITMENA = ENABLED;
    CORE_ITM.ITM_TER = 1U;
}

void traceOut(char const * const formatString, ...)
{
    va_list args;
    va_start(args, formatString);
    char const * currentChar = formatString;

    while(*currentChar != '\0')
    {
        while( CORE_ITM.ITM_STIM[0].STATUS == CORE_ITM_FIFO_FULL ) { }

        // parseFormatSpecifier(currentChar, args);

        CORE_ITM.ITM_STIM[0].WRITE = *currentChar;
        ++currentChar;
    }
    va_end(args);
}

static void parseFormatSpecifier(char const * currentChar, va_list args)
{
    static bool reentrantGuard = false;
    if(reentrantGuard || (*currentChar != '%'))
    {
        return;
    }
    reentrantGuard = true;
    ++currentChar;
    switch(*currentChar)
    {
        case '%':
        {
            CORE_ITM.ITM_STIM[0].WRITE = '%';
        }
        break;
    }
    reentrantGuard = false;
}