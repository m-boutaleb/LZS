#define encoding_IMPORT
#include "encoding_service.h"
#include "hash_service.h"
#include "data_repository.h"
#include "buffer_service.h"
#include "completion_bar_service.h"
#include "string.h"

// This array represents all the char encountered
static uc history_buffer[WINDOW_SIZE];
// This array represents the sliding window
static uc holding_buffer[WINDOW_SIZE];
// This values represents the size of the holding buffer and the history buffer
static us holding_buffer_size, history_buffer_size;

/**
 * This methods compute the compressing algorithm until the input file has no more
 * values
 */
static void compute_encoding();
/**
 * This methods generate all the possible subset consecutive of the history_buffer
 */
static inline void generate_subsets();
/**
 * History, holding and table of the hash table are all resetted
 */
static void reset_all();
/**
 * The output of the match is outputted
 * @param is_not_finished check whether the input file is finished to copy all
 * the values in holding buffer or only holding_buffer_size-1
 */
static void output_pattern(const us is_not_finished,const ui hb_pos);

inline void generate_subsets(){
    if(history_buffer_size<2)return;
    for(us i=0; i<history_buffer_size-1; i++){
        us string_length=history_buffer_size-i+1;
        add_to_table(history_buffer+i, string_length, i);
    }
}

void reset_all(){
    reset_table();
    history_buffer_size=holding_buffer_size=0;
    memset(history_buffer, 0, sizeof(history_buffer));
    memset(holding_buffer, 0, sizeof(holding_buffer));
}

void output_pattern(const us is_not_finished, const ui hb_pos){
    us length=(!is_not_finished)?holding_buffer_size:holding_buffer_size-1;
    us final_offset=(history_buffer_size-(!is_not_finished?length-1:length)-hb_pos)-1;
    load_byte(0, final_offset, length, '\0');
    holding_buffer[0] = holding_buffer[holding_buffer_size - 1];
    memset(holding_buffer + 1, 0, sizeof(holding_buffer) - 1);
    holding_buffer_size = 1;
}

void encode(const uc* input_file_name, const uc * output_file_name){
    initialize_files(input_file_name, output_file_name);
    compute_encoding();
}

void compute_encoding(){
    holding_buffer_size=history_buffer_size=0;
    uc readed_byte;
    us is_done=0, is_not_finished=0, hb_pos=0;
    ui is_match=0;

    if((is_not_finished=read_byte_update_c_bar(&readed_byte)))
    do{
        if(history_buffer_size==WINDOW_SIZE) {
            if (is_match)
                output_pattern(0, hb_pos);
            else
                load_byte(1, 0, 0, holding_buffer[0]);
            is_match=0;
            reset_all();
        }
        if(is_not_finished)
            history_buffer[history_buffer_size++] = holding_buffer[holding_buffer_size++] = readed_byte;
        ui hash_pos;
        if(is_not_finished && holding_buffer_size>1 && (is_match=(hash_pos=is_match_table(holding_buffer, holding_buffer_size+1))<HASH_TABLE_SIZE))
            hb_pos = find_hb_pos(hash_pos);
        else{
            is_match=0;
            if((!is_not_finished&&holding_buffer_size<2&&holding_buffer_size)||(is_not_finished&&holding_buffer_size&&holding_buffer_size<3&&holding_buffer_size!=1)){
                load_byte(1, 0, 0, holding_buffer[0]);
                holding_buffer[0]=holding_buffer[1];
                holding_buffer[1]='\0';
                holding_buffer_size=1;
            }else if(holding_buffer_size>2||(holding_buffer_size>=2 && !is_not_finished))
                output_pattern(is_not_finished,hb_pos);
        }
        if(!is_not_finished)
            break;
        generate_subsets();
    }while(!((is_not_finished=read_byte_update_c_bar(&readed_byte)), is_done));
    write_end_marker();
    close_files_complete_c_bar(collisions);
    reset_all();
}
