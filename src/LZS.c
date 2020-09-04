/**
 * LZS with match search with hash table
 * @copyright Copyright (c) 2020 by Mohamed Boutaleb
 * @license This code is licensed under MIT license (see LICENSE.txt for details)
 * @author Mohamed Boutaleb <mohamed.boutaleb@student.supsi.ch>
 * @version 1.0.0 2020-08-19
 * @run To run the program just run the target with the make file by typing "make static_LZS_1.0.0".
 * Then a file with the name "LZS_static_1.0.0" should appear in the dist/ folder. Then access the
 * dist folder and type the following command:
 * ./LZS_static_1.0.0 <option> <input_file> <output_file>
 * Where <option> should be "-c" to compress or "-d" to decompress, and <input_file> and <output_file>
 * should be the name of the input and output file respectively
 */
#include "algorithm_controller.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char** argv) {
    if(argc!=4){
        log_error("ERROR - Specify '-c' or '-d' to compress or decompress file respectively and an input and an output file name...");
        exit(ERROR_ARGUMENTS);
    }
    initialize_algorithm(argv[1], argv[2], argv[3]);
    return 0;
}
