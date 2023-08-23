#ifndef MESSAGE_DEFINITION_H
#define MESSAGE_DEFINITION_H

#include <stdint-gcc.h>

/**
 * @brief Message ID enum
 * 
 */
typedef enum
{
    MSG_LED_REQ,
    MSG_LED_RES
} tMessageId;

/**
 * @brief Message structure
 * 
 */
typedef struct __attribute__((packed))
{
    tMessageId  messageId;
    uint32_t    nodeId;
    uint8_t     ledId;
} tMessage;

#endif // MSG_DEF_H