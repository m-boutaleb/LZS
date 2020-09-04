#include "completion_bar_service.h"
#include "data_repository.h"

#define NR_OF_ASTERISKS 47
// Value that represent the value of the current completion bar
static us completion_bar=0;

us read_byte_update_c_bar(uc* byte_to_read){
    // To print out the buffer content to the terminal
    setvbuf(stdout, NULL, _IONBF, 0);
    if(!get_input_file_size())
        return 0;
    static ul comp_bar_pos=0;
    us result= comp_bar_pos * NR_OF_ASTERISKS / get_input_file_size();
    comp_bar_pos++;
    us output=result>completion_bar?result-completion_bar:0;
    completion_bar=result;
    while(output--)
        log("*");
    return read_byte(byte_to_read);
}

void close_files_complete_c_bar(const ul collisions){
    us remaining_asterisks=NR_OF_ASTERISKS-completion_bar;
    while(remaining_asterisks--)log("*");
    close_files_output_info(collisions);
}
