#ifndef PROJECT_ALGORITHM_CONTROLLER_H
#define PROJECT_ALGORITHM_CONTROLLER_H
#include "utils.h"

#ifndef EXTERN
    #define EXTERN extern
#endif

/**
 * This method acts as a controller for the two modules (compression and decompression)
 * depending on the specified option (-c for compression and -d for decompression) will
 * call the methods to run the algorithm
 * @param option -c or -d to compress or decompress the file respectively
 * @param input_file_name the name of the existing input file 
 * @param output_file_name the name of the output file
 */
EXTERN void initialize_algorithm(const uc *option, const uc* input_file_name, const uc* output_file_name);

#undef algorithm_IMPORT
#endif //PROJECT_ALGORITHM_CONTROLLER_H
