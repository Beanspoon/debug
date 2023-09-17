#ifndef TRACE_HAL_H
#define TRACE_HAL_H

/**
 * @brief Initialises the trace functionality
*/
void trace_init(void);

/**
 * @brief Prints 'a'
*/
void print(char const * const formatString, ...);

#endif  // TRACE_HAL_H