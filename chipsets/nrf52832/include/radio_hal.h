#ifndef RADIO_HAL_H
#define RADIO_HAL_H

#include "types.h"

#include <stdint-gcc.h>

/**
 * @brief Radio status enum
 * 
 */
typedef enum
{
    RADIO_STATUS_OK,
    RADIO_STATUS_ERROR,
    RADIO_STATUS_INVALID
} tRadio_status;

/**
 * @brief Radio tasks enum
 *
 */
typedef enum
{
    RADIO_TASKS_TXEN,         // Enable the radio in tx mode
    RADIO_TASKS_RXEN,         // Enable the radio in rx mode
    RADIO_TASKS_START,        // Start radio tx or rx
    RADIO_TASKS_STOP,         // Stop radio tx or rx
    RADIO_TASKS_DISABLE,      // Disable radio
    RADIO_TASKS_RSSISTART,    // Start RSSI measurement and take one sample
    RADIO_TASKS_RSSISTOP,     // Stop RSSI measurement
    RADIO_TASKS_BCSTART,      // Start the bit counter
    RADIO_TASKS_BCSTOP,       // Stop the bit counter
    RADIO_TASKS_COUNT
} tRadio_tasks;

/**
 * @brief Radio base frequency setting
 * 
 */
typedef enum 
{
    RADIO_BASE_FREQUENCY_2400MHZ,
    RADIO_BASE_FREQUENCY_2360MHZ
} tRadio_baseFrequency;

/**
 * @brief Logical address enum
 *
 */
typedef enum
{
    RADIO_LOGADDR_PRIMARY,
    RADIO_LOGADDR1,
    RADIO_LOGADDR2,
    RADIO_LOGADDR3,
    RADIO_LOGADDR4,
    RADIO_LOGADDR5,
    RADIO_LOGADDR6,
    RADIO_LOGADDR7
} tRadio_logicalAddress;

/**
 * @brief Enum describing the endianness of the S0, Length, S1 and Payload fields in radio
 *  packets
 * 
 */
typedef enum
{
    RADIO_LITTLE_ENDIAN,
    RADIO_BIG_ENDIAN
} tRadio_endianness;

/**
 * @brief Enum describing whether the CRC calculation should include the address field
 * 
 */
typedef enum
{
    RADIO_CRC_INCLUDE_ADDRESS,
    RADIO_CRC_SKIP_ADDRESS
} tRadio_crcAddressBehaviour;

/**
 * @brief Enum describing the length of the packet preamble
 * 
 */
typedef enum
{
    RADIO_8_BIT_PREAMBLE,
    RADIO_16_BIT_PREAMBLE
} tRadio_preambleLength;

/**
 * @brief Enum describing the behaviour of whether the S1 field is included in RAM
 * 
 */
typedef enum
{
    RADIO_AUTO_INCLUDE_S1,  // Only include the S1 field in RAM if S1 length > 0
    RADIO_ALWAYS_INCLUDE_S1 // Alwaus include the S1 field in RAM
} tRadio_s1Include;

/**
 * @brief Radio shortcuts enum
 *
 */
typedef enum
{
    RADIO_SHORTS_READY_START,
    RADIO_SHORTS_END_DISABLE,
    RADIO_SHORTS_DISABLED_TXEN,
    RADIO_SHORTS_DISABLED_RXEN,
    RADIO_SHORTS_ADDRESS_RSSISTART,
    RADIO_SHORTS_END_START,
    RADIO_SHORTS_ADDRESS_BCSTART,
    RADIO_SHORTS_DISABLED_RSSISTOP = 8u,
    RADIO_SHORTS_MAX
} tRadio_shorts;

/**
 * @brief Initialise the radio peripheral
 * 
 */
void radio_init(void);

/**
 * @brief Sets the radio frequency to use
 * 
 * @param[in] channelFrequency The value added to the base frequency. Range 0 - 100
 * @param[in] baseFrequency The base frequency setting
 */
tRadio_status radio_configureFrequency(const uint8_t channelFrequency, const tRadio_baseFrequency baseFrequency);

/**
 * @brief Configures data whitening settings for the radio peripheral
 * 
 * @param[in] iv    The initial value to use for data whitening
 * @param[in] state Enable or disable data whitening
 */
void radio_configureDataWhitening(const uint8_t iv, const tEnable state);

/**
 * @brief Sets the base address length to use
 * 
 * @param[in] length Length of the base address in bytes [2-4]
 */
void radio_setBaseAddressLength(const uint8_t length);

/**
 * @brief Sets the primary address
 * 
 * @param[in] prefix The most significant byte of the address
 * @param[in] base The base address value
 */
void radio_setPrimaryAddress(const uint8_t prefix, const uint32_t base);

/**
 * @brief Enables or disables receiving on a particular logical address
 * 
 * @param[in] address The logical address to configure
 * @param[in] setting Takes values ENABLE or DISABLE
 */
void radio_configureRxAddress(const tRadio_logicalAddress address, const tEnable setting);

/**
 * @brief Sets the address used for transmission
 * 
 * @param[in] address The logical address to use
 */
void radio_configureTxAddress(const tRadio_logicalAddress address);

/**
 * @brief Configures the radio packet settings
 * 
 * @param[in] preambleLength Enum describing the length of the packet preamble
 * @param[in] s0Length_bytes Length of the D0 field in bytes [0-1]
 * @param[in] lengthFieldLength_bits Length of the length field in bits [0-15]
 * @param[in] s1Length_bits Length of the S1 field in bits [0-15]
 * @param[in] s1Include Inclusion behaviour in RAM for the S1 field
 * @param[in] maxPayloadLength_bytes Maximum length of the payload in bytes [0-255]
 * @param[in] staticLength_bytes Static length added to the total length of the payload
 * @param[in] endianness Endianness of the S0, length, S1 and payload
 * 
 * @return RADIO_STATUS_OK if successful
 *          RADIO_STATUS_ERROR if paramters given were invalid
 */
tRadio_status radio_configurePacket(const tRadio_preambleLength preambleLength,
                                    const uint8_t s0Length,
                                    const uint8_t lengthFieldLength,
                                    const uint8_t s1Length,
                                    const tRadio_s1Include s1Include,
                                    const uint8_t maxPayloadLength,
                                    const uint8_t staticLength,
                                    const tRadio_endianness endianness);

/**
 * @brief Configure the CRC
 * 
 * @param[in] length Length of the CRC value in bytes (0-3)
 * @param[in] initValue Init value of the CRC (Up to 3 bytes)
 * @param[in] polynomial bitwise representation of the CRC polynomial (1011 = x^3 + x + 1)
 * @param[in] addressBehaviour Enum describing whether CRC will include the address
 */
tRadio_status radio_configureCrc(const uint8_t length,
                                    const uint32_t initValue,
                                    const uint32_t polynomial,
                                    const tRadio_crcAddressBehaviour addressBehaviour);

/**
 * @brief Enable or disable a shortcut between an event and a task
 * 
 * @param shortcut The shortcut to configure
 * @param state The state to set the shortcut to
 */
void radio_configureShortcut(const tRadio_shorts shortcut, const tEnable state);

/**
 * @brief Change the task of the radio peripheral.
 * This function checks against the current radio state to
 * make sure the transition is valid
 * 
 * @param task The task to change to
 * @return tRadio_status    RADIO_STATUS_OK if the task is valid for the current state
 *                          RADIO_STATUS_INVALID if not
 */
tRadio_status radio_setTask(const tRadio_tasks task);

#endif  // RADIO_HAL_H