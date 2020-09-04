#ifndef PROJECT_UTILS_H
#define PROJECT_UTILS_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint32_t ui;
typedef uint64_t ul;
typedef uint8_t uc;
typedef uint16_t us;

#ifndef EXTERN
    #define EXTERN extern
#endif

// Logger of a simple message
#define log(message) printf((message));
// Logger of a message with a parameter
#define log_param(message, param) printf((message), param);
// Logger in the stderr of a message error
#define log_error(message) fprintf(stderr, message);

// All the errors to output if something has gone wrong
enum{ERROR_ARGUMENTS=1, ERROR_INPUT_OUTPUT_FILE=(1<<1), ERROR_OPTION=(1|1<<1)}errors;

/**
 * strcpy does not copy the '\0'
 * so I wrote method to copy from
 * one array of char to the other. Included
 * all the null terminator
 * @param dest destination of the copy
 * @param source of the string to copy
 * @param str_length the length of the string to copy
 */
EXTERN void copy_string(uc* dest, const uc* source,us str_length);
/**
 * strcmp does not compare the '\0'
 * so I wrote method to compare an
 * array of char with the other
 * taking into account the null
 * terminator as well
 * @param dest the destination string to compare
 * @param source string to compare
 * @param str_length length of the source and destination string
 * @return 0 if the string are equals otherwise 1
 */
EXTERN us compare_string(const uc* dest, const uc* source,us str_length);

#endif //PROJECT_UTILS_H
