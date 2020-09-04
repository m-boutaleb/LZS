#define decoding_IMPORT
#include "decoding_service.h"
#include "encoding_service.h"
#include "buffer_service.h"
#include "data_repository.h"
#include "completion_bar_service.h"
#include "string.h"

// This represents the history buffer of all the chars passed
static uc history_buffer[WINDOW_SIZE];
// This value represents the size of the history_buffer
static us history_buffer_size;

/**
 * Methods that compute the decoding until the end marker is encountered
 */
static void compute_decoding();
/**
 * This methods resets the history_buffer
 */
static void reset_all();

void decode(const uc * input_file_name, const uc *output_file_name){
    initialize_files(input_file_name, output_file_name);
    compute_decoding();
}

void reset_all(){
    history_buffer_size=0;
    memset(history_buffer, 0, sizeof(history_buffer));
}

void compute_decoding(){
    history_buffer_size=0;
    uc readed_byte;
    while(1){
        if(history_buffer_size>=WINDOW_SIZE)
            reset_all();
        if(!read_1bit()){
            readed_byte=read_1byte();
            history_buffer[history_buffer_size++]=readed_byte;
            write_byte(&readed_byte);
        }else{
            us offset, length;
            if(read_1bit()){
                offset=read_offset(0);
                if(!offset)
                    break;
                length=read_length();
            }else{
                offset=read_offset(1);
                length=read_length();
            }
            uc output[WINDOW_SIZE];
            for(int i=history_buffer_size-offset, k=0;  k<length; i++, k++) {
                if (i > (history_buffer_size -1))
                    i =history_buffer_size-offset;
                output[k] = history_buffer[i];
            }
            for(int i=0; i<length; i++){
                history_buffer[history_buffer_size++]=output[i];
                write_byte(&output[i]);
            }
        }
    }
    close_files_complete_c_bar(0);
}
