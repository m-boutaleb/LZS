#define algorithm_IMPORT
#include <string.h>
#include <stdlib.h>
#include "algorithm_controller.h"
#include "encoding_service.h"
#include "decoding_service.h"

/**
 * Method that recalls the decompression module
 * @param input_file_name input file name to pass to the module
 * @param output_file_name output file name to pass to the module
 */
static void decode_file();

/**
 * Method that recalls the compression module
 * @param input_file_name input file name to pass to the module
 * @param output_file_name output file name to pass to the module
 */
static void encode_file();

void decode_file(const uc * input_file_name, const uc *output_file_name){
    decode(input_file_name, output_file_name);
}

void encode_file(const uc * input_file_name, const uc *output_file_name){
    encode(input_file_name, output_file_name);
}

void initialize_algorithm(const uc *option, const uc* input_file_name, const uc* output_file_name){
    if(!strcmp("-D", option)||!strcmp("-d", option))
        decode_file(input_file_name, output_file_name);
    else if(!strcmp("-c", option)||!strcmp("-C", option))
        encode_file(input_file_name, output_file_name);
    else {
        log_error("Invalid option. Please use '-c' or '-d' to compress or decompress data respectively");
        exit(ERROR_OPTION);
    }
}
