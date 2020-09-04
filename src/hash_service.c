#define hash_table_IMPORT
#include <stdlib.h>
#include "hash_service.h"

// Reprensents the hash table of all the values encountered
static uc *hash_table[HASH_TABLE_SIZE];
// Represents all the lengths of the match patterns in the hash table
static us match_lengths[HASH_TABLE_SIZE];
// Rapresents all the position in the history buffer of the matching pattern in the hash table
static us hb_positions[HASH_TABLE_SIZE];
// All the position occupied by the hash table
static ui history_pos[HASH_TABLE_SIZE];
// The size of the position occupied by the hash_table (not counting the collisions)
static ui history_pos_size=0;
// The number of the collision
ui collisions=0;

/**
 * Set the match pattern and the offset to the node
 * @param value match pattern found
 * @param length of the match pattern
 * @param node to set
 * @param offset the value of the position of the history buffer
 */
static void set_value(const uc* value, const us length, const ui final_pos, const us offset);
/**
 * This hash function output the hash value of the pattern mod the size of the table
 * it uses the MURMUR2 hashing function. It has been developed by Austin Appleby in 2008
 * all rights reserved.
 * @Title: MURMURHASH2
 * @Author: Austin Appleyby
 * @Date: 2008
 * @Code version: MurmurHash2
 * @Availability: http://murmurhash.googlepages.com/
 * @param str the string to hash
 * @param str_length the length of the string
 * @return the position in the table
 */
inline static ui hash(const uc* str,us str_length);



//MURMUR2 HASH
inline ui hash(const uc* key,us len) {
        ui seed=0;
        const uint32_t m = 0x5bd1e995;
        const int r = 24;
        uint32_t h = seed ^ len;
        const unsigned char * data = (const unsigned char *)key;
        while(len >= 4){
            uint32_t k = *(uint32_t*)data;

            k *= m;
            k ^= k >> r;
            k *= m;

            h *= m;
            h ^= k;

            data += 4;
            len -= 4;
        }

        switch(len){
            case 3: h ^= data[2] << 16;
            case 2: h ^= data[1] << 8;
            case 1: h ^= data[0];
                h *= m;
        };

        h ^= h >> 13;
        h *= m;
        h ^= h >> 15;

        return h%HASH_TABLE_SIZE;
}

void set_value(const uc* value, const us length,const ui final_pos, const us offset){
    hash_table[final_pos]=(uc*)malloc(sizeof(uc)*length);
    copy_string(hash_table[final_pos], value, length);
    match_lengths[final_pos]=length;
    hb_positions[final_pos]=offset;
}

ui is_match_table(const uc *match, const us match_length){
    ui hash_result=hash(match, match_length);
    uc *cursor=hash_table[hash_result];
    ui i=0;
    // Linear probing
    while(cursor)
        if(match_lengths[((hash_result+i)%HASH_TABLE_SIZE)]==match_length&&
        !compare_string(match, cursor, match_length))
            return (hash_result+i)%HASH_TABLE_SIZE;
        else cursor=hash_table[((hash_result+(++i))%HASH_TABLE_SIZE)];
    return ((hash_result+i)%HASH_TABLE_SIZE)+HASH_TABLE_SIZE;
}

void reset_table(){
    for(ui i=0; i<history_pos_size; i++){
        free(hash_table[history_pos[i]]);
        hash_table[history_pos[i]]=NULL;
    }
    history_pos_size=0;
}

void add_to_table(const uc* value, const us string_length, const us pos_hb){
    ui already_in=is_match_table(value, string_length);
    if(already_in<HASH_TABLE_SIZE)return;

    ui final_pos=(already_in-HASH_TABLE_SIZE);
    ul hash_result=hash(value, string_length);

    // Increment nr of collisions if hash_result do not match the final position
    collisions+=final_pos!=hash_result?1:0;

    history_pos[history_pos_size++]=final_pos;
    set_value(value, string_length, final_pos, pos_hb);
}

us find_hb_pos(const ui pos){return hb_positions[pos];}