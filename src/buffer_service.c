#define buffer_service_IMPORT
#include "buffer_service.h"
#include "data_repository.h"
#include "completion_bar_service.h"

#define MAX_BUFFER_SIZE 8

static us buffer_size=0;
static uc buffer=0;

/**
 * Load a value in the buffer
 * @param bits the value to load in the buffer
 * @param nr_of_bits nr of bits of the bits value
 */
static void write_bits_buffer(uc bits, us nr_of_bits);
/**
 * Write the value of the buffer in the output file
 */
static void write_buffer();
/**
 * Load the value readed from the input file in to the buffer
 */
static void read_buffer();
/**
 * Empty the buffer (only if the buffer_size==MAX_BUFFER_SIZE) writing the value
 * in it in the output file and resetting the buffer
 */
static void empty_buffer();
/**
 * Reset the value of the buffer to 0 and reset the value of the buffer_size
 */
static void reset_buffer();

void empty_buffer(){
    if(buffer_size==MAX_BUFFER_SIZE) {
        write_buffer();
        reset_buffer();
    }
}

void write_bits_buffer(uc bits, us nr_of_bits){
    while(nr_of_bits){
        empty_buffer();
        if(nr_of_bits==(MAX_BUFFER_SIZE-buffer_size)){
            buffer_size+=nr_of_bits;
            buffer|=bits;
            nr_of_bits=0;
        }else if(nr_of_bits>(MAX_BUFFER_SIZE-buffer_size)) {
            us shift = (nr_of_bits - (MAX_BUFFER_SIZE - buffer_size));
            buffer|=(bits>>shift);
            nr_of_bits-=(MAX_BUFFER_SIZE-buffer_size);
            buffer_size=MAX_BUFFER_SIZE;
        }else if(nr_of_bits<(MAX_BUFFER_SIZE-buffer_size)){
            us shift=MAX_BUFFER_SIZE-buffer_size-nr_of_bits;
            buffer_size+=nr_of_bits;
            buffer|=(bits<<shift);
            nr_of_bits=0;
        }
    }
    empty_buffer();
}

void read_buffer(){
    read_byte_update_c_bar(&buffer);
}

void write_buffer(){
    write_byte(&buffer);
}

void reset_buffer(){
    buffer_size=0;
    buffer=0;
}

us read_offset(const us is_greater_than_127){
    us result=0;
    for(int i=1; i<(is_greater_than_127?12:8); i++)
        result=(result<<1)|read_1bit();
    return result;
}

us read_length(){
    us first_2bit=0;
    for(int i=0; i<2; i++)
        first_2bit=(first_2bit<<1)|read_1bit();
    if(first_2bit!=3)return first_2bit+2;
    for(int i=0; i<2; i++)
        first_2bit=(first_2bit<<1)|read_1bit();
    if(first_2bit!=15)return first_2bit+5-12;
    us n=0;
    while(first_2bit==15) {
        first_2bit=0;
        n++;
        for (int i = 0; i < 4; i++)
            first_2bit = (first_2bit << 1) | read_1bit();
    }
    us to_find=n-1;
    us result=to_find*15+8;
    return result+first_2bit;
}

uc read_1byte(){
    uc result=0;
    if(buffer_size==MAX_BUFFER_SIZE){result=buffer; read_buffer(); return result;}
    if(buffer_size==0){read_buffer();result=buffer; reset_buffer(); return result; }
    us to_read=buffer_size;
    result=buffer;
    read_buffer();
    result|=(buffer>>(to_read));
    buffer<<=(MAX_BUFFER_SIZE-to_read);
    buffer_size=to_read;
    return result;
}

uc read_1bit(){
    if(buffer_size==0){read_buffer();buffer_size=MAX_BUFFER_SIZE;}
    uc result=buffer>>(MAX_BUFFER_SIZE-1);
    buffer<<=1;
    buffer_size--;
    return result;
}

void write_end_marker(){
    write_bits_buffer(1, 1);
    write_bits_buffer((1<<7), 8);
    if(buffer_size!=0)
        write_bits_buffer(0, MAX_BUFFER_SIZE-buffer_size);
}

void load_byte(us is_raw_byte, us offset, us length, uc raw_byte_token ){
    if(is_raw_byte) {
        write_bits_buffer(0, 1);
        write_bits_buffer(raw_byte_token, 8);
    }else{
        write_bits_buffer(1, 1);
        if(offset<128)
            write_bits_buffer((1<<7)|offset, 8);
        else if(offset>127) {
            write_bits_buffer(0, 1);
            write_bits_buffer(offset>>4, 7);
            write_bits_buffer(offset&15, 4);
        }
        if(length<5)
            write_bits_buffer(length-2, 2);
        else if(length>4&&length<8)
            write_bits_buffer((1<<3)|(1<<2)|(length-5), 4);
        else if(length>7){
            us number_of_4_bit_patters=(length-8)/15+1;
            while(number_of_4_bit_patters--)write_bits_buffer(15, 4);
            write_bits_buffer((length-8)%15, 4);
        }
    }
}


