//بسم الله الرحمن الرحيم

//this file should NOT be included directly and all manupilations should be done to the tlist_t
#include <stdint.h>

struct task_t
{
    uint32_t id;
    char name[30];
    //uint32 parents_id_list, children_id_list;
    //time_t or equivalent
};

