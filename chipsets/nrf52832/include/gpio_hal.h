#ifndef GPIO_HAL_H
#define GPIO_HAL_H

/**
 * @brief Pin state enum
 *
 */
typedef enum
{
    LOW,
    HIGH
} tGpio_pinState;

/**
 * @brief GPIO operation status enum
 *
 */
typedef enum
{
    GPIO_STATUS_OK,
    GPIO_STATUS_INVALID
} tGpio_status;

/**
 * @brief GPIO pin enum
 *
 */
typedef enum
{
    GPIO_PIN0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,
    GPIO_PIN8,
    GPIO_PIN9,
    GPIO_PIN10,
    GPIO_PIN11,
    GPIO_PIN12,
    GPIO_PIN13,
    GPIO_PIN14,
    GPIO_PIN15,
    GPIO_PIN16,
    GPIO_PIN17,
    GPIO_PIN18,
    GPIO_PIN19,
    GPIO_PIN20,
    GPIO_PIN21,
    GPIO_PIN22,
    GPIO_PIN23,
    GPIO_PIN24,
    GPIO_PIN25,
    GPIO_PIN26,
    GPIO_PIN27,
    GPIO_PIN28,
    GPIO_PIN29,
    GPIO_PIN30,
    GPIO_PIN31,
    GPIO_PIN_MAX
} tGpio_pin;

/**
 * @brief Pin pull direction enum (input)
 *
 */
typedef enum
{
    GPIO_PULL_DISABLED,
    GPIO_PULL_DOWN,
    GPIO_PULL_UP = 3
} tGpio_pull;

/**
 * @brief Pin drive configuration enum (output)
 *
 */
typedef enum
{
    GPIO_DRIVE_S0S1,    // Standard '0', standard '1'
    GPIO_DRIVE_H0S1,    // High drive '0', standard '1'
    GPIO_DRIVE_S0H1,    // Standard '0', high drive '1'
    GPIO_DRIVE_H0H1,    // High drive '0', high drive '1'
    GPIO_DRIVE_D0S1,    // Disconnect '0', standard '1' (wired-or)
    GPIO_DRIVE_D0H1,    // Disconnect '0', high drive '1' (wired-or)
    GPIO_DRIVE_S0D1,    // Standard '0', disconnect '1' (wired-and)
    GPIO_DRIVE_H0D1,    // High drive '0', disconnect '1' (wired-and)
} tGpio_drive;

/**
 * @brief GPIOTE channel identifier
*/
typedef enum
{
    GPIOTE_CHANNEL_0,
    GPIOTE_CHANNEL_1,
    GPIOTE_CHANNEL_2,
    GPIOTE_CHANNEL_3,
    GPIOTE_CHANNEL_4,
    GPIOTE_CHANNEL_5,
    GPIOTE_CHANNEL_6,
    GPIOTE_CHANNEL_7,
    GPIOTE_CHANNEL_COUNT
} tGpiote_channel;

/**
 * @brief Pin sense configuration enum (input)
 *
 */
typedef enum
{
    GPIO_SENSE_DISABLED,    // Pin sensing mechanism disabled
    GPIO_SENSE_HIGH = 2,    // Sense for high level
    GPIO_SENSE_LOW          // Sense for low level
} tGpio_sense;

/**
 * @brief Configures a pin as an input
 * 
 * @param[in] pin   The pin to configure
 * @param[in] pullDir   Pull direction setting for the pin
 * @param[in] sense Pin sensing mechanism setting
 */
void gpio_configureInputPin(const tGpio_pin pin,
                            const tGpio_pull pullDir,
                            const tGpio_sense sense);

/**
 * @brief Configures a pin as an output
 * 
 * @param[in] pin   The pin to configure
 * @param[in] drive Pin drive configuration
 */
void gpio_configureOutputPin(const tGpio_pin pin,
                                const tGpio_drive drive);

/**
 * @brief Set pin to state
 * 
 * @param[in] pin   The pin to set
 * @param[in] state The state to set the pin to
 */
void gpio_writePin(const tGpio_pin pin,
                    const tGpio_pinState state);

#endif  // GPIO_HAL_H