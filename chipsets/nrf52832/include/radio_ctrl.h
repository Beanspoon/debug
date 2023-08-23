#ifndef RADIO_CTRL_H
#define RADIO_CTRL_H

/**
 * @brief Enum to describe status of radio_ctrl operations
 * 
 */
typedef enum
{
    RADIO_CTRL_STATUS_OK,
    RADIO_CTRL_STATUS_ERROR,
} tRadioCtrl_status;

/**
 * @brief Perform initialisation actions required for using the radio
 * 
 * @return  RADIO_CTRL_STATUS_OK if successful
 *          RADIO_CTRL_STATUS_ERROR otherwise
 */
tRadioCtrl_status radioCtrl_init(void);

/**
 * @brief Start up the radio in RX mode to begin transmitting
 * 
 * @return  RADIO_CTRL_STATUS_OK if successful
 *          RADIO_CTRL_STATUS_ERROR otherwise
 */
tRadioCtrl_status radioCtrl_start(void);

#endif  // RADIO_CTRL_H