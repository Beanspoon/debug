#include "radio_hal.h"
#include "radio_prv.h"

#include "utils.h"

#include <stdbool.h>

static bool isTaskValidForState(tRadio_tasks task)
{
    if(RADIO_TASKS_RSSISTOP == task)
    {
        // This task is always valid
        return true;
    }
    
    bool taskIsValidForState = false;

    switch(RADIO.STATE)
    {
        case RADIO_STATE_DISABLED:
            if((RADIO_TASKS_RXEN == task) ||
                (RADIO_TASKS_TXEN == task))
            {
                taskIsValidForState = true;
            }
        break;

        case RADIO_STATE_RXRU:
        case RADIO_STATE_TXRU:
            if(RADIO_TASKS_DISABLE == task)
            {
                taskIsValidForState = true;
            }
        break;

        case RADIO_STATE_RXIDLE:
        case RADIO_STATE_TXIDLE:
            if((RADIO_TASKS_START == task) ||
                (RADIO_TASKS_DISABLE == task))
            {
                taskIsValidForState = true;
            }
        break;

        case RADIO_STATE_RX:
            if((RADIO_TASKS_STOP == task) ||
                (RADIO_TASKS_DISABLE == task) ||
                (RADIO_TASKS_RSSISTART == task))
            {
                taskIsValidForState = true;
            }
        break;
        case RADIO_STATE_TX:
            if((RADIO_TASKS_STOP == task) ||
                (RADIO_TASKS_DISABLE == task))
            {
                taskIsValidForState = true;
            }
        break;
    }
}

void radio_init(void)
{
    RADIO.POWER = ENABLED;
}

tRadio_status radio_configureFrequency(const uint8_t channelFrequency, const tRadio_baseFrequency baseFrequency)
{
    if(channelFrequency > 100)
    {
        return RADIO_STATUS_ERROR;
    }

    RADIO.FREQUENCY.FREQUENCY = channelFrequency;
    RADIO.FREQUENCY.MAP = baseFrequency;

    return RADIO_STATUS_OK;
}

void radio_configureDataWhitening(const uint8_t iv, const tEnable state)
{
    RADIO.DATAWHITEIV = iv;
    RADIO.PCNF.WHITEEN = state;    
}

void radio_setBaseAddressLength(const uint8_t length)
{
    RADIO.PCNF.BALEN = length;
}

void radio_setPrimaryAddress(const uint8_t prefix, const uint32_t base)
{
    RW_reg primaryPrefixMask = 0xFF;
    RADIO.PREFIX[0] = (RADIO.PREFIX[0] & primaryPrefixMask) | prefix;
    RADIO.BASE[0] = base;
}

void radio_configureRxAddress(const tRadio_logicalAddress address, const tEnable setting)
{
    RW_reg registerValue = RADIO.RXADDRESSES & ~(1 << address);
    registerValue |= (setting << address);
    RADIO.RXADDRESSES = registerValue;
}

void radio_configureTxAddress(const tRadio_logicalAddress address)
{
    RADIO.TXADDRESS = address;
}

tRadio_status radio_configurePacket(const tRadio_preambleLength preambleLength,
                                    const uint8_t s0Length,
                                    const uint8_t lengthFieldLength,
                                    const uint8_t s1Length,
                                    const tRadio_s1Include s1Include,
                                    const uint8_t maxPayloadLength,
                                    const uint8_t staticLength,
                                    const tRadio_endianness endianness)
{
    if((s0Length > 1u) ||
        (lengthFieldLength > 15u) ||
        (s1Length > 15u))
    {
        return RADIO_STATUS_ERROR;
    }

    RADIO.PCNF.PLEN = preambleLength;
    RADIO.PCNF.S0LEN = s0Length;
    RADIO.PCNF.LFLEN = lengthFieldLength;
    RADIO.PCNF.S1LEN = s1Length;
    RADIO.PCNF.S1INCL = s1Include;
    RADIO.PCNF.STATLEN = staticLength;
    RADIO.PCNF.ENDIAN = endianness;

    return RADIO_STATUS_OK;
}

tRadio_status radio_configureCrc(const uint8_t length,
                                    const uint32_t initValue,
                                    const uint32_t polynomial,
                                    const tRadio_crcAddressBehaviour addressBehaviour)
{
    if(length > 3)
    {
        return RADIO_STATUS_ERROR;
    }

    RADIO.CRCCNF.LEN = length;
    RADIO.CRCINIT = initValue;
    RADIO.CRCPOLY = polynomial;
    RADIO.CRCCNF.SKIPADDR = addressBehaviour;

    return RADIO_STATUS_OK;
}

void radio_configureShortcut(const tRadio_shorts shortcut, const tEnable state)
{
    switch(state)
    {
        case ENABLED:
            RADIO.SHORTS |= BITMASK(shortcut);
            break;

        case DISABLED:
            RADIO.SHORTS &= ~BITMASK(shortcut);
            break;
        
        default:
            // No behaviour
    }
}

#define MAPPED_STATE_COUNT   3

typedef struct
{
    tRadio_state states[MAPPED_STATE_COUNT];
} tTaskStateMapping;

tRadio_status radio_setTask(const tRadio_tasks task)
{
    static const tTaskStateMapping taskStateMap[RADIO_TASKS_COUNT] = 
    {
        [RADIO_TASKS_TXEN]      = {RADIO_STATE_DISABLED, RADIO_STATE_RXIDLE, RADIO_STATE_TXIDLE},
        [RADIO_TASKS_RXEN]      = {RADIO_STATE_DISABLED, RADIO_STATE_TXIDLE, RADIO_STATE_RXIDLE},
        [RADIO_TASKS_START]     = {RADIO_STATE_TXIDLE, RADIO_STATE_RXIDLE, RADIO_STATE_INVALID},
        [RADIO_TASKS_STOP]      = {RADIO_STATE_TX, RADIO_STATE_RX, RADIO_STATE_INVALID},
        [RADIO_TASKS_DISABLE]   = {RADIO_STATE_INVALID, RADIO_STATE_INVALID, RADIO_STATE_INVALID},
        [RADIO_TASKS_RSSISTART] = {RADIO_STATE_INVALID, RADIO_STATE_INVALID, RADIO_STATE_INVALID},
        [RADIO_TASKS_RSSISTOP]  = {RADIO_STATE_INVALID, RADIO_STATE_INVALID, RADIO_STATE_INVALID},
        [RADIO_TASKS_BCSTART]   = {RADIO_STATE_TX, RADIO_STATE_RX, RADIO_STATE_INVALID},
        [RADIO_TASKS_BCSTOP]    = {RADIO_STATE_INVALID, RADIO_STATE_INVALID, RADIO_STATE_INVALID}
    };
    const tRadio_state state = RADIO.STATE;
    bool stateMatch = false;
    uint8_t stateIndex = 0U;

    if((task == RADIO_TASKS_RSSISTART) ||
        (task == RADIO_TASKS_RSSISTOP) ||
        (task == RADIO_TASKS_BCSTOP))
    {
        // These tasks are valid for any state
        stateMatch = true;
    }

    while(!stateMatch && (stateIndex < MAPPED_STATE_COUNT))
    {
        if(taskStateMap[task].states[stateIndex] == state)
        {
            stateMatch = true;
        }
        ++stateIndex;
    }

    tRadio_status operationStatus = RADIO_STATUS_INVALID;
    if(stateMatch)
    {
        RADIO.TASKS[task] = ENABLED;
        operationStatus = RADIO_STATUS_OK;
    }
    return operationStatus;
}
