#ifndef PROJECT_HASH_SERVICE_H
#define PROJECT_HASH_SERVICE_H
#include "utils.h"
#include "encoding_service.h"

#ifndef EXTERN
    #define EXTERN extern
#endif

// variable that counts the number of collisions
// need to be shared to be printed by the data_repository
EXTERN ui collisions;

//173993 43427 696623(1<<10) 11154139(1<<12) is the first prime number after n*1.33. N is the maximum number of the entries
#if WINDOW_SIZE==(1<<9)
#define HASH_TABLE_SIZE 173993 // used for testing
#else
#define HASH_TABLE_SIZE 696623 // first prime number greather than (1024*(512)-512)*1.33
#endif

/**
 * Checks that there is a value already present in the hash_table. It is using the
 * linear probing to manage collisions
 * @param match possible match to find
 * @param match_length the length of the possible match
 * @return n if n>=HASH_TABLE_SIZE then there are no match otherwise there is a match
 */
EXTERN ui is_match_table(const uc *match, const us match_length);
/**
 * Add the value passed to the table if does not exist
 * @param value to add to the table
 * @param string_length length of the match
 * @param offset to save in the node
 */
EXTERN void add_to_table(const uc * value, const us string_length, const us offset);
/**
 * Clear and free the memory allocated in the heap in the hash table
 */
EXTERN void reset_table(void);
/**
 * if a match is found return the value of the history_buffer position
 * @param position in the hash table of the matching pattern
 * @return position of the match in the history_buffer
 */
EXTERN us find_hb_pos(const ui hb_pos);

#undef hash_table_IMPORT
#undef EXTERN
#endif //PROJECT_HASH_SERVICE_H
