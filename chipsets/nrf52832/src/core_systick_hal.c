#include "core_systick_hal.h"
#include "core_systick_prv.h"

#include "types.h"
#include "utils.h"

#include <stdint-gcc.h>

#define TEN_MS_FREQUENCY                (ONE_SECOND_IN_MS / 10u)
#define SYSTICK_TICK_PERIODICITY_MS     (1000u / SYSTICK_TICK_FREQUENCY_HZ)

/**
 * @brief Systick flags
 * 
 */
typedef struct
{
    uint8_t isInitialised   : 1;    // Systick has been initialised
} tCoreSystick_flags;

/**
 * @brief Systick context
 * 
 */
typedef struct
{
    tCoreSystick_flags  flags;
} tCoreSystick_context;

static tCoreSystick_context* getContext(void)
{
    static tCoreSystick_context context = { 0 };
    return &context;
}

void systick_init(void)
{
    tCoreSystick_context* pContext = getContext();
    if(!pContext->flags.isInitialised)
    {
        // If there is a reference clock (NOREF==0), use it (CSR_CLKSOURCE==0)
        // Otherwise, CSR_CLKSOURCE is forced to 1 anyway
        CORE_SYSTICK.SYST_CSR.CSR_CLKSOURCE = CORE_SYSTICK.SYST_CALIB.CALIB_NOREF;

        if(CORE_SYSTICK.SYST_CALIB.CALIB_TENMS != 0u)
        {
            // Calibration value is available, so use this to set the correct reload value
            // Calculation is done this way to avoid floating-point calculation
            CORE_SYSTICK.SYST_RVR = CORE_SYSTICK.SYST_CALIB.CALIB_TENMS * TEN_MS_FREQUENCY / SYSTICK_TICK_FREQUENCY_HZ;
        }
        else
        {
            CORE_SYSTICK.SYST_RVR = CORE_CLOCK_FREQUENCY_HZ / SYSTICK_TICK_FREQUENCY_HZ;
        }

        CORE_SYSTICK.SYST_CSR.CSR_TICKINT = ENABLED;    // Enable systick interrupt
        CORE_SYSTICK.SYST_CVR = 0u; // Clear the current value register (reset)
        (volatile void)CORE_SYSTICK.SYST_CSR.CSR_COUNTFLAG;  // Read the countflag to reset

        CORE_SYSTICK.SYST_CSR.CSR_SYST_EN = ENABLED;    // Enable systick
    }
}

void systick_busyWait(uint32_t delay_ms)
{
    while(delay_ms > 0)
    {
        if(CORE_SYSTICK.SYST_CSR.CSR_COUNTFLAG)
        {
            // Guard against underflow
            if(SYSTICK_TICK_PERIODICITY_MS < delay_ms)
            {
                delay_ms -= SYSTICK_TICK_PERIODICITY_MS;
            }
            else
            {
                delay_ms = 0u;
            }
        }
    }
}