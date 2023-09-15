#include "core_debug_reg.h"
#include "core_itm_reg.h"
#include "core_tpiu_reg.h"
#include "clock_prv.h"

#include "chip_cfg.h"

void trace_init(void)
{

    // CORE_ITM.ITM_TCR.GTSFREQ = GTSFREQ_ON_PACKET;
    CORE_DEBUG.DEMCR.TRCENA = ENABLED;

    CORE_TPIU.TPIU_SPPR.TXMODE = TPIU_SPPR_TXMODE_SWO_NRZ;
    CORE_TPIU.TPIU_ACPR = (CORE_CLOCK_FREQUENCY_HZ/CORE_CLOCK_TRACEPORT_SPEED_HZ) - 1;

    CORE_ITM.ITM_TCR.ITMENA = ENABLED;
    CORE_ITM.ITM_TER = 1U;
}

void print(void)
{
    CORE_ITM.ITM_STIM[0] = 'a';
}