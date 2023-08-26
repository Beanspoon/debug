#include "board_ctrl.h"

#include "gpio_hal.h"

#include "board_cfg.h"

void boardCtrl_configureBoard( void )
{
    gpio_configureInputPin(BTN0, GPIO_PULL_UP, GPIO_SENSE_DISABLED);
    gpio_configureInputPin(BTN1, GPIO_PULL_UP, GPIO_SENSE_DISABLED);

    gpio_configureOutputPin(LED0, GPIO_DRIVE_S0S1);
    gpio_configureOutputPin(LED1, GPIO_DRIVE_S0S1);
}

void boardCtrl_ledActive(const tGpio_pin led)
{
    gpio_writePin(led, LOW);
}

void boardCtrl_ledInactive(const tGpio_pin led)
{
    gpio_writePin(led, HIGH);
}