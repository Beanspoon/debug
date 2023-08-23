#include "gpio_prv.h"

#include "utils.h"

void gpio_configureInputPin(const tGpio_pin pin, const tGpio_pull pullDir, const tGpio_sense sense)
{
    GPIO.PINCNF[pin].DIR = GPIO_DIR_INPUT;
    GPIO.PINCNF[pin].INPUT_BUFFER = GPIO_INBUF_CONNECT;
    GPIO.PINCNF[pin].PULL = pullDir;
    GPIO.PINCNF[pin].SENSE = sense;
}

void gpio_configureOutputPin(const tGpio_pin pin,
                                const tGpio_drive drive)
{
    GPIO.PINCNF[pin].DIR = GPIO_DIR_OUTPUT;
    GPIO.PINCNF[pin].INPUT_BUFFER = GPIO_INBUF_DISCONNECT;
    GPIO.PINCNF[pin].DRIVE = drive;
}

void gpio_writePin(const tGpio_pin pin, const tGpio_pinState state)
{
    RW_reg *reg = state ? &GPIO.OUTSET : &GPIO.OUTCLR;
    *reg = BITMASK(pin);
}

tGpio_pinState gpio_readPin(const tGpio_pin pin)
{
    tGpio_pinState state = (tGpio_pinState)((GPIO.IN & BITMASK(pin)) >> pin);
    return state;
}

tGpio_status gpio_configureEvent(const tGpio_pin pin,
                                    const tGpio_pull pullDir,
                                    const tGpiote_polarity trigger,
                                    const tGpiote_channel * pChannel)
{
    tGpio_status result = GPIO_STATUS_INVALID;
    tGpiote_channel channel = GPIOTE_CHANNEL_0;
    
    while(channel < GPIOTE_CHANNEL_COUNT)
    {
        if(GPIOTE.CONFIG[channel].MODE == GPIOTE_MODE_DISABLED)
        {
            break;
        }
        ++channel;
    }
    
    if(channel <= GPIOTE_CHANNEL_COUNT)
    {
        
        gpio_configureInputPin(pin, pullDir, GPIO_SENSE_DISABLED);
    }
    

}