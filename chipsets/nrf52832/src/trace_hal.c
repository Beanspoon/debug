#include "core_debug_reg.h"
#include "core_itm_reg.h"
#include "core_tpiu_reg.h"
#include "clock_prv.h"

void trace_init(void)
{
    CLOCK.TRACECONFIG.traceMux = CLOCK_TRACEMUX_SERIAL;
    CLOCK.TRACECONFIG.tracePortSpeed = CLOCK_TRACEPORT_SPEED_32MHZ;

    CORE_TPIU.TPIU_SPPR.TXMODE = TPIU_SPPR_TXMODE_SWO_MANCHESTER;
    CORE_TPIU.TPIU_ACPR = 3332U;    // 9600 baud

    CORE_ITM.ITM_TPR = TRACE_PRIVILEGE_PORT_0_TO_7_MASK;
    CORE_ITM.ITM_TCR.GTSFREQ = GTSFREQ_ON_PACKET;
    CORE_ITM.ITM_TCR.ITMENA = ENABLED;
}

void print(void)
{
    CORE_ITM.ITM_STIM[0] = 'a';
}