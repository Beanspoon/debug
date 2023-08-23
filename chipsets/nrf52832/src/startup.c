#include "core_nvic_hal.h"

extern unsigned int __srodata;
extern unsigned int __erodata;
extern unsigned int __sbss;
extern unsigned int __ebss;
extern unsigned int __sdata;
extern unsigned int __edata;
extern unsigned int __sstack;
extern unsigned int __estack;

// Forward-define main
void main( void );

__attribute__((weak))
void Reset_handler( void )
{
    // Initialise zeroed statics
    unsigned int *pBss = &__sbss;
    while( pBss < &__ebss )
    {
        *pBss = 0;
        ++pBss;
    }

    // Copy statics from flash to ram section
    unsigned int *pInitVals = &__erodata;
    unsigned int *pData = &__sdata;
    while( pData < &__edata)
    {
        *pData = *pInitVals;
        ++pData;
        ++pInitVals;
    }

    main();

    while(1) {}
}

__attribute__((weak))
void NMI_handler( void )
{
    while(1) {}
}

__attribute__((weak))
void Hardfault_handler( void )
{
    while(1) {}
}

__attribute__((weak))
void MemMgmtFault_handler( void )
{
    while(1) {}
}

__attribute__((weak))
void BusFault_handler( void )
{
    while (1) {}
}

__attribute__((weak))
void UsageFault_handler( void )
{
    while (1) {}
}

void Dummy_handler( void ) {}

void SVCall_handler( void )     __attribute__((weak, alias("Dummy_handler")));
void PendSV_handler( void )     __attribute__((weak, alias("Dummy_handler")));
void Systick_handler( void )    __attribute__((weak, alias("Dummy_handler")));

void ClockPowerBrot_isr( void ) __attribute__((weak, alias("Dummy_handler")));
void Radio_isr( void )          __attribute__((weak, alias("Dummy_handler")));
void Uarte_isr( void )          __attribute__((weak, alias("Dummy_handler")));
void SpiTwi0_isr( void )        __attribute__((weak, alias("Dummy_handler")));
void SpiTwi1_isr( void )        __attribute__((weak, alias("Dummy_handler")));
void Nfct_isr( void )           __attribute__((weak, alias("Dummy_handler")));
void Gpiote_isr( void )         __attribute__((weak, alias("Dummy_handler")));
void Saadc_isr( void )          __attribute__((weak, alias("Dummy_handler")));
void Timer0_isr( void )         __attribute__((weak, alias("Dummy_handler")));
void Timer1_isr( void )         __attribute__((weak, alias("Dummy_handler")));
void Timer2_isr( void )         __attribute__((weak, alias("Dummy_handler")));
void Rtc0_isr( void )           __attribute__((weak, alias("Dummy_handler")));
void Temp_isr( void )           __attribute__((weak, alias("Dummy_handler")));
void Rng_isr( void )            __attribute__((weak, alias("Dummy_handler")));
void Ecb_isr( void )            __attribute__((weak, alias("Dummy_handler")));
void Ccm_isr( void )            __attribute__((weak, alias("Dummy_handler")));
void Aar_isr( void )            __attribute__((weak, alias("Dummy_handler")));
void Wdt_isr( void )            __attribute__((weak, alias("Dummy_handler")));
void Rtc1_isr( void )           __attribute__((weak, alias("Dummy_handler")));
void Qdec_isr( void )           __attribute__((weak, alias("Dummy_handler")));
void Comp_isr( void )           __attribute__((weak, alias("Dummy_handler")));
void SwiEgu0_isr( void )        __attribute__((weak, alias("Dummy_handler")));
void SwiEgu1_isr( void )        __attribute__((weak, alias("Dummy_handler")));
void SwiEgu2_isr( void )        __attribute__((weak, alias("Dummy_handler")));
void SwiEgu3_isr( void )        __attribute__((weak, alias("Dummy_handler")));
void SwiEgu4_isr( void )        __attribute__((weak, alias("Dummy_handler")));
void SwiEgu5_isr( void )        __attribute__((weak, alias("Dummy_handler")));
void Timer3_isr( void )         __attribute__((weak, alias("Dummy_handler")));
void Timer4_isr( void )         __attribute__((weak, alias("Dummy_handler")));
void Pwm0_isr( void )           __attribute__((weak, alias("Dummy_handler")));
void Pdm_isr( void )            __attribute__((weak, alias("Dummy_handler")));
void Nvmc_isr( void )           __attribute__((weak, alias("Dummy_handler")));
void Ppi_isr( void )            __attribute__((weak, alias("Dummy_handler")));
void Mwu_isr( void )            __attribute__((weak, alias("Dummy_handler")));
void Pwm1_isr( void )           __attribute__((weak, alias("Dummy_handler")));
void Pwm2_isr( void )           __attribute__((weak, alias("Dummy_handler")));
void Spi2_isr( void )           __attribute__((weak, alias("Dummy_handler")));
void Rtc2_isr( void )           __attribute__((weak, alias("Dummy_handler")));
void I2s_isr( void )            __attribute__((weak, alias("Dummy_handler")));
void Fpu_isr( void )            __attribute__((weak, alias("Dummy_handler")));

// Vector table
__attribute__ ((section(".vectors")))
const tVectorTable vectorTable = 
{
    // Stack pointer
    .pStack                 = (void *)(&__estack),

    // Exception handlers
    .pfReset_handler        = (void *)Reset_handler,
    .pfNMI_handler          = (void *)NMI_handler,
    .pfHardfault_handler    = (void *)Hardfault_handler,
    .pfMemMgmtFault_handler = (void *)MemMgmtFault_handler,
    .pfBusFault_handler     = (void *)BusFault_handler,
    .pfUsageFault_handler   = (void *)UsageFault_handler,
    .pfSVCall_handler       = (void *)SVCall_handler,
    .pfPendSV_handler       = (void *)PendSV_handler,
    .pfSystick_handler      = (void *)Systick_handler,

    // Interrupt service routines
    .pfIsr_clockPowerBprot  = (void *)ClockPowerBrot_isr,
    .pfIsr_radio            = (void *)Radio_isr,
    .pfIsr_uarte            = (void *)Uarte_isr,
    .pfIsr_spiTwi0          = (void *)SpiTwi0_isr,
    .pfIsr_spiTwi1          = (void *)SpiTwi1_isr,
    .pfIsr_nfct             = (void *)Nfct_isr,
    .pfIsr_gpiote           = (void *)Gpiote_isr,
    .pfIsr_saadc            = (void *)Saadc_isr,
    .pfIsr_timer0           = (void *)Timer0_isr,
    .pfIsr_timer1           = (void *)Timer1_isr,
    .pfIsr_timer2           = (void *)Timer2_isr,
    .pfIsr_rtc0             = (void *)Rtc0_isr,
    .pfIsr_temp             = (void *)Temp_isr,
    .pfIsr_rng              = (void *)Rng_isr,
    .pfIsr_ecb              = (void *)Ecb_isr,
    .pfIsr_ccm              = (void *)Ccm_isr,
    .pfIsr_aar              = (void *)Aar_isr,
    .pfIsr_wdt              = (void *)Wdt_isr,
    .pfIsr_rtc1             = (void *)Rtc1_isr,
    .pfIsr_qdec             = (void *)Qdec_isr,
    .pfIsr_comp             = (void *)Comp_isr,
    .pfIsr_swiEgu0          = (void *)SwiEgu0_isr,
    .pfIsr_swiEgu1          = (void *)SwiEgu1_isr,
    .pfIsr_swiEgu2          = (void *)SwiEgu2_isr,
    .pfIsr_swiEgu3          = (void *)SwiEgu3_isr,
    .pfIsr_swiEgu4          = (void *)SwiEgu4_isr,
    .pfIsr_swiEgu5          = (void *)SwiEgu5_isr,
    .pfIsr_timer3           = (void *)Timer3_isr,
    .pfIsr_timer4           = (void *)Timer4_isr,
    .pfIsr_pwm0             = (void *)Pwm0_isr,
    .pfIsr_pdm              = (void *)Pdm_isr,
    .pfIsr_nvmc             = (void *)Nvmc_isr,
    .pfIsr_ppi              = (void *)Ppi_isr,
    .pfIsr_mwu              = (void *)Mwu_isr,
    .pfIsr_pwm1             = (void *)Pwm1_isr,
    .pfIsr_pwm2             = (void *)Pwm2_isr,
    .pfIsr_spi2             = (void *)Spi2_isr,
    .pfIsr_rtc2             = (void *)Rtc2_isr,
    .pfIsr_i2s              = (void *)I2s_isr,
    .pfIsr_fpu              = (void *)Fpu_isr
};
