#ifndef PROJECT_DATA_REPOSITORY_H
#define PROJECT_DATA_REPOSITORY_H
#include "utils.h"
#ifndef EXTERN
#define EXTERN extern
#endif

typedef struct generaldata GeneralData;

/**
 * reads a byte and puts the value in the specified parameter
 * @param byte_to_read parameter where to load the read byte
 * @return 0 if the end of the input file otherwise 1
 */
EXTERN uc read_byte(uc* byte_to_read);
/**
 * writes the value passed per parameter to the output file
 * @param byte_to_write byte to write
 * @return number of bytes readed
 */
EXTERN uc write_byte(const uc *byte_to_write);
/**
 * Method that closes open files (input and output) and output some
 * general info to the terminal
 */
EXTERN void close_files_output_info(const ui collisions);
/**
 * method that initializes input and output files
 * @param input_file_name name of the input file
 * @param output_file_name name of the output file
 */
EXTERN void initialize_files(const uc *input_file_name, const uc * output_file_name);

/**
 * @return the size of the input file
 */
EXTERN size_t get_input_file_size();

#endif //PROJECT_DATA_REPOSITORY_H
