#ifndef CORE_NVIC_H
#define CORE_NVIC_H

#include "types.h"

/**
 * @brief Vector table definition
 *
 */
typedef struct
{
    void *pStack;   // Stack pointer

    // Exception handlers
    void *pfReset_handler;
    void *pfNMI_handler;
    void *pfHardfault_handler;
    void *pfMemMgmtFault_handler;
    void *pfBusFault_handler;
    void *pfUsageFault_handler;
    void *RESERVED_A[4];
    void *pfSVCall_handler;
    void *RESERVED_B[2];
    void *pfPendSV_handler;
    void *pfSystick_handler;

    // Interrupts
    void *pfIsr_clockPowerBprot;
    void *pfIsr_radio;
    void *pfIsr_uarte;
    void *pfIsr_spiTwi0;
    void *pfIsr_spiTwi1;
    void *pfIsr_nfct;
    void *pfIsr_gpiote;
    void *pfIsr_saadc;
    void *pfIsr_timer0;
    void *pfIsr_timer1;
    void *pfIsr_timer2;
    void *pfIsr_rtc0;
    void *pfIsr_temp;
    void *pfIsr_rng;
    void *pfIsr_ecb;
    void *pfIsr_ccm;
    void *pfIsr_aar;
    void *pfIsr_wdt;
    void *pfIsr_rtc1;
    void *pfIsr_qdec;
    void *pfIsr_comp;
    void *pfIsr_swiEgu0;
    void *pfIsr_swiEgu1;
    void *pfIsr_swiEgu2;
    void *pfIsr_swiEgu3;
    void *pfIsr_swiEgu4;
    void *pfIsr_swiEgu5;
    void *pfIsr_timer3;
    void *pfIsr_timer4;
    void *pfIsr_pwm0;
    void *pfIsr_pdm;
    void *pfIsr_nvmc;
    void *pfIsr_ppi;
    void *pfIsr_mwu;
    void *pfIsr_pwm1;
    void *pfIsr_pwm2;
    void *pfIsr_spi2;
    void *pfIsr_rtc2;
    void *pfIsr_i2s;
    void *pfIsr_fpu;
} tVectorTable;

typedef enum
{
    NVIC_INT_CLOCK_POWER_BROT,
    NVIC_INT_RADIO,
    NVIC_INT_UARTE,
    NVIC_INT_SPI_TWI0,
    NVIC_INT_SPI_TWI1,
    NVIC_INT_NFCT,
    NVIC_INT_GPIOTE,
    NVIC_INT_SAADC,
    NVIC_INT_TIMER0,
    NVIC_INT_TIMER1,
    NVIC_INT_TIMER2,
    NVIC_INT_RTC0,
    NVIC_INT_TEMP,
    NVIC_INT_RNG,
    NVIC_INT_ECB,
    NVIC_INT_CCM,
    NVIC_INT_AAR,
    NVIC_INT_WDT,
    NVIC_INT_RTCL,
    NVIC_INT_QDEC,
    NVIC_INT_COMP,
    NVIC_INT_SWIEGU0,
    NVIC_INT_SWIEGU1,
    NVIC_INT_SWIEGU2,
    NVIC_INT_SWIEGU3,
    NVIC_INT_SWIEGU4,
    NVIC_INT_SWIEGU5,
    NVIC_INT_TIMER3,
    NVIC_INT_TIMER4,
    NVIC_INT_PWM0,
    NVIC_INT_PDM,
    NVIC_INT_NVMC,
    NVIC_INT_PPI,
    NVIC_INT_MWU,
    NVIC_INT_PWM1,
    NVIC_INT_PWM2,
    NVIC_INT_SPI2,
    NVIC_INT_RTC2,
    NVIC_INT_I2S,
    NVIC_INT_FPU,
} tNvic_interrupt;

/**
 * @brief Enable/disable the target interrupt
 *
 * @param[in] interrupt Interrupt to change
 * @param[in] targetState State to change to
 */
void nvic_changeInterruptState( const tNvic_interrupt interrupt, const tEnable targetState);

#endif // CORE_NVIC_H