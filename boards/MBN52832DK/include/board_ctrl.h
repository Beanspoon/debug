#ifndef BOARD_CTRL_H
#define BOARD_CTRL_H

#include "gpio_hal.h"

/**
 * @brief Sets up board configuration
*/
void boardCtrl_configureBoard( void );

/**
 * @brief Activates the given LED
 * 
 * @param[in]   led The LED to activate
*/
void boardCtrl_ledActive(const tGpio_pin led);

/**
 * @brief Deactivates the given LED
 * 
 * @param[in]   led The LED to deactivate
*/
void boardCtrl_ledInactive(const tGpio_pin led);


#endif // BOARD_CTRL_H