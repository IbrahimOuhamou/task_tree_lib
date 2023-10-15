//بسم الله الرحمن الرحيم

//this file should NOT be included directly and all manupilations should be done to the tlist_t
#include <stdint.h>
#include <string.h>

struct task_t
{
    uint32_t id;
    uint8_t progress;
    char name[30];
    //uint32 parents_id_list, children_id_list;
    //time_t or equivalent
};

struct taskt* newtask(const char* tname)
{
    struct task_t* taskptr = malloc(sizeof(task_t));
    taskptr->progress = 0;
    memcpy(taskptr->name, tname, sizeof(taskptr->name));

    return taskptr;
}

