#include "radio_ctrl.h"

#include "radio_hal.h"
#include "clock_hal.h"

#include "message_definition.h"
#include "fifo.h"

#include "board_cfg.h"

typedef enum
{
    RADIO_CTRL_STATE_INIT,
    RADIO_CTRL_STATE_RX,
    RADIO_CTRL_STATE_TX
} tRadioCtrl_state;

typedef struct
{
    tRadioCtrl_state state;
    tMessage         rxBuffer[RADIO_RX_QUEUE_SIZE];
    tFifo_instance   rxQueue;
    tMessage         txBuffer[RADIO_TX_QUEUE_SIZE];
    tFifo_instance   txQueue;
} tRadioCtrl_context;

static tRadioCtrl_context* getContext(void)
{
    static tRadioCtrl_context context = {0u};
    return &context;
}

tRadioCtrl_status radioCtrl_init(void)
{
    clock_startHFClock();

    radio_init();

    bool statusOk = (
        RADIO_STATUS_OK == radio_configureFrequency(RADIO_CHANNEL_FREQUENCY,
                                                    RADIO_BASE_FREQUENCY)
    );
    statusOk |= (
        RADIO_STATUS_OK == radio_configurePacket(RADIO_PACKET_PREAMBLE_LENGTH,
                                                    RADIO_PACKET_S0_LENGTH,
                                                    RADIO_PACKET_LENGTH_FIELD_LENGTH,
                                                    RADIO_PACKET_S1_LENGTH,
                                                    RADIO_PACKET_S1_INCLUSION,
                                                    RADIO_PACKET_MAX_PAYLOAD_LENGTH,
                                                    RADIO_PACKET_STATIC_LENGTH,
                                                    RADIO_PACKET_ENDIANNESS)
    );
    statusOk |= (
        RADIO_STATUS_OK == radio_configureCrc(RADIO_CRC_LENGTH,
                                                RADIO_CRC_IV,
                                                RADIO_CRC_POLYNOMIAL,
                                                RADIO_CRC_ADDRESS_BEHAVIOUR)
    );

    radio_configureDataWhitening(RADIO_DATA_WHITENING_IV,
                                    ENABLED);

    radio_setBaseAddressLength(RADIO_BASE_ADDRESS_LENGTH);
    radio_setPrimaryAddress(RADIO_PRIMARY_ADDRESS_PREFIX,
                            RADIO_PRIMARY_ADDRESS_BASE);
    radio_configureTxAddress(RADIO_LOGADDR_PRIMARY);
    radio_configureRxAddress(RADIO_LOGADDR_PRIMARY, ENABLED);

    tRadioCtrl_context *pContext = getContext();
    statusOk |= (
        FIFO_STATUS_OK == fifo_initialise(&(pContext->rxQueue),
                                            pContext->rxBuffer,
                                            RADIO_RX_QUEUE_SIZE,
                                            sizeof(pContext->rxBuffer[0]),
                                            false)
    );
    statusOk |= (
        FIFO_STATUS_OK == fifo_initialise(&(pContext->txQueue),
                                            pContext->txBuffer,
                                            RADIO_TX_QUEUE_SIZE,
                                            sizeof(pContext->txBuffer[0]),
                                            false)
    );

    return statusOk ? RADIO_CTRL_STATUS_OK : RADIO_CTRL_STATUS_ERROR;
}

tRadioCtrl_status radioCtrl_start(void)
{
    tRadioCtrl_context *context = getContext();
    if(context->state != RADIO_CTRL_STATE_INIT)
    {
        return RADIO_CTRL_STATUS_ERROR;
    }

    radio_configureShortcut(RADIO_SHORTS_READY_START, ENABLED);
    tRadio_status setTaskStatus = radio_setTask(RADIO_TASKS_RXEN);
    context->state = RADIO_CTRL_STATE_RX;
    return (setTaskStatus == RADIO_STATUS_OK) ? RADIO_CTRL_STATUS_OK : RADIO_CTRL_STATUS_ERROR;
}