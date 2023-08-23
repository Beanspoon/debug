#ifndef RADIO_PRV_H
#define RADIO_PRV_H

#include "radio_hal.h"

#include "types.h"

/**
 * @brief Radio events enum
 *
 */
typedef enum
{
    RADIO_EVENTS_READY    = 0,    // Radio has ramped up and is ready for tx or rx
    RADIO_EVENTS_ADDRESS  = 1,    // Address transmitted or received
    RADIO_EVENTS_PAYLOAD  = 2,    // Payload transmitted or recieved
    RADIO_EVENTS_END      = 3,    // Tx or rx complete
    RADIO_EVENTS_DISABLED = 4,    // Radio has been disabled
    RADIO_EVENTS_DEVMATCH = 5,    // Address match occurred on the last recevied packet
    RADIO_EVENTS_DEVMISS  = 6,    // No address match occurred on the last recevied packet
    RADIO_EVENTS_RSSIEND  = 7,    // RSSI sampling is complete

    RADIO_EVENTS_BCMATCH  = 10,   // Bit counter reached bit count match value

    RADIO_EVENTS_CRCOK    = 12,   // Packet recieved with CRC OK
    RADIO_EVENTS_CRCERROR = 13,   // Packet recieved with CRC error
    RADIO_EVENTS_COUNT
} tRadio_events;

/**
 * @brief Definition of the frequency setting register
 *
 */
typedef struct
{
    RW_reg                  FREQUENCY   : 7; // Bit[0-6] Radio channel frequency (2400 + FREQUENCY) MHz [0-100]
    uint8_t                             : 0;
    tRadio_baseFrequency    MAP         : 1; // Bit[8] Base frequency 0: 2400 MHz, 1: 2360 MHz
    RW_reg                              : 0;
} tRadio_frequencyReg;

/**
 * @brief Radio power enum
 *
 */
typedef enum
{
    RADIO_POWER_POS4DBM   = 0x04,
    RADIO_POWER_POS3DBM   = 0x03,
    RADIO_POWER_0DBM      = 0x00,
    RADIO_POWER_NEG4DBM   = 0xFC,
    RADIO_POWER_NEG8DBM   = 0xF8,
    RADIO_POWER_NEG12DBM  = 0xF4,
    RADIO_POWER_NEG16DBM  = 0xF0,
    RADIO_POWER_NEG20DBM  = 0xEC,
    RADIO_POWER_NEG40DBM  = 0xD8
} tRadio_txPower;

/**
 * @brief Definition of the packet config registers
 *
 */
typedef struct
{
    // PCNF0
    RW_reg          LFLEN   : 4; // Bit[0-3] Length on air of LENGTH field in bits
    const uint8_t           : 0;
    RW_reg          S0LEN   : 1; // Bit[8] Length on air of S0 field in bytes
    const uint16_t          : 0;
    RW_reg          S1LEN   : 4; // Bit[16-19] Length on air of S1 field in bits
    RW_reg          S1INCL  : 1; // Bit[20] 0: Include S1 in RAM if S1LEN > 0, 1: Always include
    const uint8_t           : 0;
    RW_reg          PLEN    : 1; // Bit[24] Length of preamble on air 0: 8bit, 1: 16bit
    RO_reg                  : 0;
    //PCNF1
    RW_reg          MAXLEN  : 8; // Bit[0-7] Maximum length in bytes of packet payload. Larger payloads will be truncated
    RW_reg          STATLEN : 8; // Bit[8-15] Static length in bytes. This is added to payload length
    RW_reg          BALEN   : 3; // Bit[16-18] Base address length in bytes
    const uint8_t           : 0;
    RW_reg          ENDIAN  : 1; // Bit[24] On-air endianness of packet (S0, LENGTH, S1 & PAYLOAD). 0: Little, 1: Big
    tEnable         WHITEEN : 1; // Bit[25] 0: disable, or 1: enable packet whitening
    RO_reg                  : 0;
} tRadio_pCnfRegs;

/**
 * @brief Definition of the CRC config register
 *
 */
typedef struct
{
    RW_reg  LEN                 : 3; // Bit[0-2] CRC length in number of bytes
    uint8_t                     : 0;
    tEnable SKIPADDR            : 1; // Bit[8] Skip address field in CRC calculation
    RW_reg                      : 0;
} tRadio_crcCnfReg;

/**
 * @brief Radio state enum
 *
 */
typedef enum
{
    RADIO_STATE_DISABLED,
    RADIO_STATE_RXRU,
    RADIO_STATE_RXIDLE,
    RADIO_STATE_RX,
    RADIO_STATE_RXDISABLE,
    RADIO_STATE_TXRU      = 9,
    RADIO_STATE_TXIDLE,
    RADIO_STATE_TX,
    RADIO_STATE_TXDISABLE,
    RADIO_STATE_INVALID = 0xFF,
} tRadio_state;

/**
 * @brief Definition of the device address configuration register
 *
 */
typedef struct
{
    tEnable ENA0    : 1;    // Bit[0] Enable device address matching using address 0
    tEnable ENA1    : 1;    // Bit[1] Enable device address matching using address 1
    tEnable ENA2    : 1;    // Bit[2] Enable device address matching using address 2
    tEnable ENA3    : 1;    // Bit[3] Enable device address matching using address 3
    tEnable ENA4    : 1;    // Bit[4] Enable device address matching using address 4
    tEnable ENA5    : 1;    // Bit[5] Enable device address matching using address 5
    tEnable ENA6    : 1;    // Bit[6] Enable device address matching using address 6
    tEnable ENA7    : 1;    // Bit[7] Enable device address matching using address 7
    tEnable TXADD0  : 1;    // Bit[8] Txadd for device address 0
    tEnable TXADD1  : 1;    // Bit[9] Txadd for device address 1
    tEnable TXADD2  : 1;    // Bit[10] Txadd for device address 2
    tEnable TXADD3  : 1;    // Bit[11] Txadd for device address 3
    tEnable TXADD4  : 1;    // Bit[12] Txadd for device address 4
    tEnable TXADD5  : 1;    // Bit[13] Txadd for device address 5
    tEnable TXADD6  : 1;    // Bit[14] Txadd for device address 6
    tEnable TXADD7  : 1;    // Bit[15] Txadd for device address 7
    RO_reg          : 0;
} tRadio_daCnfReg;

typedef enum
{
    RADIO_DEFAULT_RAMPUP,
    RADIO_FAST_RAMPUP
} tRadio_rampUpRate;

/**
 * @brief Radio default transmission frequency register
 *
 */
typedef enum
{
    B1,         // Transmit '1'
    B0,         // Transmit '0'
    CENTER,     // Transmit center frequency
} tRadio_dtx;

/**
 * @brief Radio mode config register
 *
 */
typedef struct
{
    tRadio_rampUpRate   RU      : 1;    // Bit[0] Radio ramp up time 0: Default, 1: Fast
    uint8_t                     : 0;
    tRadio_dtx          DTX     : 2;    // Bit[8-9] Default TX value - specifies what is transmitted when radio is up but not started
} tRadio_modeCnf0Reg;

/**
 * @brief Radio register map
 *
 */
typedef struct
{
    RW_reg                  TASKS[RADIO_TASKS_COUNT];     // 0x000-020 Tasks registers
    RO_reg                  RESERVED_A[0x37];
    RW_reg                  EVENTS[RADIO_EVENTS_COUNT];   // 0x100-134 Events registers
    RO_reg                  RESERVED_B[0x32];
    RW_reg                  SHORTS;                     // 0x200 Shortcuts register
    RO_reg                  RESERVED_C[0x40];
    RW_reg                  INTENSET;                   // 0x304 Interrupt enable register
    RW_reg                  INTENCLR;                   // 0x308 Interrupt clear register
    RO_reg                  RESERVED_D[0x3D];
    RO_reg                  CRCSTATUS;                  // 0x400 CRC status register
    RO_reg                  RESERVED_E;
    RO_reg                  RXMATCH;                    // 0x408 Received address logical match register
    RO_reg                  RXCRC;                      // 0x40C CRC field of previously received packet (24 bits)
    RO_reg                  DAI;                        // 0x410 Device address match index
    RO_reg                  RESERVED_F[0x3C];
    RW_reg                  PACKETPTR;                  // 0x504 RAM address of memory in which packet is stored
    tRadio_frequencyReg     FREQUENCY;                  // 0x508 Frequency setting register
    tRadio_txPower          TXPOWER;                    // 0x50C Transmission power register
    RW_reg                  MODE;                       // 0x510 Radio data rate and modulation
    tRadio_pCnfRegs         PCNF;                       // 0x514-518 Packet configuration registers
    RW_reg                  BASE[2];                    // 0x51C-520 Radio base address registers
    RW_reg                  PREFIX[2];                  // 0x524-528 Prefix bytes for logical addresses
    RW_reg                  TXADDRESS;                  // 0x52C Transmit logical address select
    RW_reg                  RXADDRESSES;                // 0x530 Receive logical address select
    tRadio_crcCnfReg        CRCCNF;                     // 0x534 CRC configuration register
    RW_reg                  CRCPOLY;                    // 0x538 CRC polynomial register (24 bits)
    RW_reg                  CRCINIT;                    // 0x53C Initial value for CRC (24 bits)
    RO_reg                  RESERVED_G;
    RW_reg                  TIFS;                       // 0x544 Inter-frame spacing in us (8 bits)
    RO_reg                  RSSISAMPLE;                 // 0x548 RSSI sample register (read as -A dbm, 7 bits)
    RO_reg                  RESERVED_H;
    const tRadio_state      STATE;                      // 0x550 Current radio state
    RW_reg                  DATAWHITEIV;                // 0x554 Data whitening initial value register (7 bits)
    RO_reg                  RESERVED_I[2];
    RW_reg                  BCC;                        // 0x560 Bit counter compare
    RO_reg                  RESERVED_J[0x27];
    RW_reg                  DAB[8];                     // 0x600-61C Device address base segment registers
    RW_reg                  DAP[8];                     // 0x620-63C Device address prefix segment registers
    tRadio_daCnfReg         DACNF;                      // 0x640 Device address match configuration
    RO_reg                  RESERVED_K[3];
    tRadio_modeCnf0Reg      MODECNF0;                   // 0x650 Radio mode configuration register 0
    RO_reg                  RESERVED_L[0x26A];
    RW_reg                  POWER;                      // 0xFFC Peripheral power control. Registers will be reset if peripheral power is toggled
} tRadio_regMap;

#define RADIO_BASE_ADDR 0x40001000
#define RADIO           (*((tRadio_regMap *)RADIO_BASE_ADDR))


#endif  // RADIO_PRV_H