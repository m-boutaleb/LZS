#ifndef PROJECT_COMPLETION_BAR_SERVICE_H
#define PROJECT_COMPLETION_BAR_SERVICE_H
#include "utils.h"
#ifndef EXTERN
#define EXTERN extern
#endif

EXTERN us read_byte_update_c_bar(uc* byte_to_read);

EXTERN void close_files_complete_c_bar(const ul collisions);

#endif //PROJECT_COMPLETION_BAR_SERVICE_H
