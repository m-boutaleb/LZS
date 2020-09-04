#ifndef PROJECT_BUFFER_SERVICE_H
#define PROJECT_BUFFER_SERVICE_H
#include "utils.h"

#ifndef EXTERN
    #define EXTERN extern
#endif

/**
 * This method based on the Boolean is raw_byte prints
 * the raw_byte_token character. In case it is false
 * then it prints the offset and the length of the
 * match pattern
 * @param is_raw_byte boolean to report a match pattern found (0 means no match pattern found)
 * @param offset the value of the offset
 * @param length the value of the length of the match pattern
 * @param raw_byte_token if there is no match pattern raw_byte_token rapresents the single char to
 * output
 */
EXTERN void load_byte(us is_raw_byte, us offset, us length, uc raw_byte_token );
/**
 * Writes the 9 bits that signal the end of the encoding below encoded
 * (110000000)
 */
EXTERN void write_end_marker(void);
/**
 * Reads only one bit from the buffer
 * @return the value of the bit (0/1)
 */
EXTERN uc read_1bit(void);
/**
 * Reads 1 byte from the buffer
 * @return 1 byte the buffer
 */
EXTERN uc read_1byte(void);
/**
 * Used by the decoding module, it reads the offset depending from the value of the
 * is_greater_than_127
 * @param is_greater_than_127 1 means that is a value greater than 127 otherwise no
 * @return the value of the offset
 */
EXTERN us read_offset(const us is_greater_than_127);
/**
 * Reads the value of the length of the match while decoding
 * @return the value of the length
 */
EXTERN us read_length(void);

#undef buffer_service_IMPORT
#undef EXTERN
#endif //PROJECT_BUFFER_SERVICE_H
