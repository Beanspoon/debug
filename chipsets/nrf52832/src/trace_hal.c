#include "core_debug_reg.h"
#include "core_itm_reg.h"
#include "core_tpiu_reg.h"
#include "clock_prv.h"

void trace_init(void)
{
    // CLOCK.TRACECONFIG.traceMux = CLOCK_TRACEMUX_SERIAL;
    // CLOCK.TRACECONFIG.tracePortSpeed = CLOCK_TRACEPORT_SPEED_4MHZ;
    // RW_reg * reg = &CLOCK.TRACECONFIG;
    // *reg = 0x10003;

    // CORE_TPIU.TPIU_SPPR.TXMODE = TPIU_SPPR_TXMODE_SWO_NRZ;
    // CORE_TPIU.TPIU_ACPR = (64000000/4000000)-1;

    // CORE_ITM.ITM_TPR = TRACE_PRIVILEGE_PORT_0_TO_7_MASK;
    // CORE_ITM.ITM_TCR.GTSFREQ = GTSFREQ_ON_PACKET;
    // CORE_ITM.ITM_TCR.ITMENA = ENABLED;
    // CORE_DEBUG.DEMCR.TRCENA = ENABLED;
    *((RW_reg *)0xE000EDFC) = (1 << 24);
    *((RW_reg *)0xE00400F0) = 2;
    *((RW_reg *)0xE0040010) = (64000000/4000000)-1;
    *((RW_reg *)0xE0000FB0) = 0xC5ACCE55;
    *((RW_reg *)0xE0000E80) = 0x1000D;
    *((RW_reg *)0xE0000E40) = 0xF;
    *((RW_reg *)0xE0000E00) = 0xFFFFFFFF;
    *((RW_reg *)0xE0001000) = 0x400003FE;
    *((RW_reg *)0xE0040304) = 0x100;
}

void print(void)
{
    CORE_ITM.ITM_STIM[0] = 'a';
}