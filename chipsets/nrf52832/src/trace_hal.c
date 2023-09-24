#include "core_debug_reg.h"
#include "core_itm_reg.h"
#include "core_tpiu_reg.h"
#include "clock_prv.h"

#include "utils.h"
#include "var_args.h"

#include "chip_cfg.h"

#include <stdbool.h>

#define UINT32_MAX_DECIMAL_LENGTH (10U)

typedef struct
{
    char const * pWidth;
    bool    padWithZeros;
} tTraceHal_specifierInfo;

static void parseCharacter(char const ** const pCurrentChar, argList * const args);
static bool parseSpecifierCharacter(char const ** const pCurrentChar,
                                    argList * const args,
                                    tTraceHal_specifierInfo * const pSpecifierInfo);
static void putCharacter(char const character);
static void parseUint(char const ** const pCurrentChar,
                        argList * const args, 
                        tTraceHal_specifierInfo * const pSpecifierInfo);

void trace_init(void)
{
    CORE_DEBUG.DEMCR.TRCENA = ENABLED;

    CORE_TPIU.TPIU_SPPR.TXMODE = TPIU_SPPR_TXMODE_SWO_NRZ;
    CORE_TPIU.TPIU_ACPR = (CORE_CLOCK_FREQUENCY_HZ/CORE_CLOCK_TRACEPORT_SPEED_HZ) - 1;

    CORE_ITM.ITM_TCR.ITMENA = ENABLED;
    CORE_ITM.ITM_TER = 1U;
}

void print(char const * const formatString, ...)
{
    argList args;
    initArgList(args, formatString);
    char const * currentChar = formatString;

    while(*currentChar != '\0')
    {
        parseCharacter(&currentChar, &args);
    }
}

static void parseCharacter(char const ** const pCurrentChar, argList * const args)
{
    static bool reentrantGuard = false;
    if(reentrantGuard || (**pCurrentChar != '%'))

    {
        putCharacter(**pCurrentChar);
        ++*pCurrentChar;
        return;
    }

    bool parsingSpecifier = true;
    reentrantGuard = true;
    tTraceHal_specifierInfo specifierInfo = { 0 };
    while(parsingSpecifier)
    {
        ++*pCurrentChar;
        parsingSpecifier = parseSpecifierCharacter(pCurrentChar, args, &specifierInfo);
    }
    ++*pCurrentChar;
    reentrantGuard = false;
}

static bool parseSpecifierCharacter(char const ** const pCurrentChar,
                                    argList * const args,
                                    tTraceHal_specifierInfo * const pSpecifierInfo)
{
    bool parsingSpecifier = true;
    switch(**pCurrentChar)
    {
        case '%':
        {
            putCharacter(**pCurrentChar);
            parsingSpecifier = false;
        }
        break;
        case 's':
        {
            char const * const string = nextArg(*args, char *);
            print(string);
            parsingSpecifier = false;
        }
        break;
        case 'u':
        {
            parseUint(pCurrentChar, args, pSpecifierInfo);
            parsingSpecifier = false;
        }
        break;
        case '0':
        {
            pSpecifierInfo->padWithZeros = (pSpecifierInfo->pWidth == NULL) ? true : pSpecifierInfo->padWithZeros;
        }
        break;
        case '1' ... '9':
        {
            pSpecifierInfo->pWidth = (pSpecifierInfo->pWidth == NULL) ? *pCurrentChar : pSpecifierInfo->pWidth;
        }
        break;
    }
    return parsingSpecifier;
}

static void putCharacter(char const character)
{
    while( CORE_ITM.ITM_STIM[0].STATUS == CORE_ITM_FIFO_FULL ) { }
    CORE_ITM.ITM_STIM[0].WRITE = character;
}

static void parseUint(char const ** const pCurrentChar,
                        argList * const args, 
                        tTraceHal_specifierInfo * const pSpecifierInfo)
{
    // Generate value from string
    uint32_t value = nextArg(*args, uint32_t);
    char string[STRING_SIZE(UINT32_MAX_DECIMAL_LENGTH)] = { '\0' };
    const char padChar = pSpecifierInfo->padWithZeros ? '0' : ' ';
    setBytes(string, padChar, UINT32_MAX_DECIMAL_LENGTH);
    uint8_t place = UINT32_MAX_DECIMAL_LENGTH;
    while(value > 0)
    {
        --place;
        string[place] = '0' + value % 10U;
        value /= 10U;
    }

    // Determine width specifier
    if(pSpecifierInfo->pWidth == NULL)
    {
        // If no width specifier was given, deactivate parsing of the width
        pSpecifierInfo->pWidth = *pCurrentChar;
    }
    uint32_t power = 1U;
    char const * pDigit = *pCurrentChar - 1U;
    size_t width = 0U;
    while(pDigit >= pSpecifierInfo->pWidth)
    {
        width += (*pDigit - '0') * power;
        power *= 10U;
        --pDigit;
    }

    // Print extra padding if specifed width is greater than the maximum length of a uint32
    for(; width > UINT32_MAX_DECIMAL_LENGTH; --width)
    {
        putCharacter(padChar);
    }

    // Update place if width requires more places than are strictly necessary
    const size_t populatedDigits = UINT32_MAX_DECIMAL_LENGTH - place;
    if(width > populatedDigits)
    {
        place = UINT32_MAX_DECIMAL_LENGTH - width;
    }

    print(&string[place]);
}