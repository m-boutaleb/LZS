#define data_repository_IMPORT
#include "data_repository.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define CURRENT_PATH "./"
#define MAX_MESSAGE_LENGTH 100
// Size of about 1 MB to enhance all the readings and writings without
// without making too many requests to the operating system
#define MAX_BUFFER_SIZE (1<<20)

struct generaldata{
    FILE *INPUT_FILE, *OUTPUT_FILE; // Input and output files
    uc input_file_name[MAX_MESSAGE_LENGTH], output_file_name[MAX_MESSAGE_LENGTH]; // Names of the input and output files
    size_t input_file_size, output_file_size; // The size of the input and output file in bytes
    time_t start_time, end_time; // Value of the start time and end time
};

/**
 * Using these bigger buffers, computing time is optimized because the
 * requests to the os are less.
 */
static uc buffer_reader[MAX_BUFFER_SIZE];
static ui buffer_reader_size=0;
static uc buffer_writer[MAX_BUFFER_SIZE];
static ui buffer_writer_size=0;

// Rapresents a general info such as the name of the input and output file
static GeneralData data_info;

/**
 * Methods that print some info to the terminal, such as the author the name
 * of the input and output files and the total time and collisions.
 */
static void print_info();
/**
 * Methods that close the input and output files
 */
static void close_files();


void close_files(){
    fclose(data_info.INPUT_FILE);fclose(data_info.OUTPUT_FILE);
}

void print_info(const uc* input_file_name, const uc* output_file_name){
    log("\n**********************LZS**********************\n");
    log("Author: Mohamed Boutaleb\n");
    log_param("Input file name: %s\n",input_file_name);
    log_param("Output file name: %s\n",output_file_name);
    data_info.start_time=time(NULL);
    strcpy(data_info.input_file_name, input_file_name);
    strcpy(data_info.output_file_name, output_file_name);

    fseek(data_info.INPUT_FILE,0, SEEK_END);
    data_info.input_file_size=ftell(data_info.INPUT_FILE);
    rewind(data_info.INPUT_FILE);
    log("Computing data...\n");
}

uc read_byte(uc* byte_to_read){
	static ul current_pos=0;
    if(current_pos==buffer_reader_size) {
        buffer_reader_size = fread(buffer_reader, sizeof(uc), MAX_BUFFER_SIZE, data_info.INPUT_FILE);
        current_pos=0;
        if (buffer_reader_size == 0)
            return 0;
    }

    *byte_to_read=buffer_reader[current_pos++];
    return 1;
}

uc write_byte(const uc* byte_to_write){
    static ul current_pos=0;
    if(current_pos==MAX_BUFFER_SIZE){
        fwrite(buffer_writer,sizeof(uc), current_pos, data_info.OUTPUT_FILE);
        current_pos=0;
    }
    buffer_writer[current_pos++]=*byte_to_write;
    buffer_writer_size=current_pos;
    return buffer_writer[buffer_writer_size];
}

void close_files_output_info(const ui collisions){
    data_info.end_time=time(NULL);

    log_param("\nSize of input file: %zu byte\n", data_info.input_file_size);

    // Write the remaining byte in the buffer writer
    if(buffer_writer_size)
        fwrite(buffer_writer, sizeof(uc), buffer_writer_size, data_info.OUTPUT_FILE);

    fseek(data_info.OUTPUT_FILE,0, SEEK_END);
    data_info.output_file_size=ftell(data_info.OUTPUT_FILE);
    log_param("Size of output file: %zu byte\n", data_info.output_file_size);

    // Close files after calculating the compressing ratio of the output file
    close_files();

    double compressing_ratio=100.0-((double)data_info.output_file_size/(double)data_info.input_file_size*100.0);
    log_param("Compressing ratio: %.2lf %%", (data_info.input_file_size==0?0:compressing_ratio));
    log_param("\nTotal collisions: %d",collisions )

    data_info.end_time=time(NULL);
    log_param("\nTotal time: %ld s", (data_info.end_time-data_info.start_time));
    log("\n**********************LZS**********************\n");
}

void initialize_files(const uc *input_file_name, const uc * output_file_name){
    uc error_message[MAX_MESSAGE_LENGTH], file_name[MAX_MESSAGE_LENGTH]=CURRENT_PATH;
    if((data_info.INPUT_FILE=fopen(strcat(file_name, input_file_name), "rb+")) == NULL){
        sprintf(error_message, "Something gone wrong with the input file. Make sure that '%s' exists and is in the right directory", input_file_name);
        log_error(error_message);
        close_files();
        exit(ERROR_INPUT_OUTPUT_FILE);
    }
    file_name[2]='\0';
    if((data_info.OUTPUT_FILE=fopen(strcat(file_name, output_file_name), "wb+")) == NULL){
        sprintf(error_message, "Something gone wrong with the output file. Make sure that '%s' has a valid name", output_file_name);
        log_error(error_message);
        close_files();
        exit(ERROR_INPUT_OUTPUT_FILE);
    }
    print_info(input_file_name, output_file_name);
}

size_t get_input_file_size(){
	return data_info.input_file_size;
}
