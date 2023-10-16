//بسم الله الرحمن الرحيم


//this file should NOT be included directly and all manupilations should be done to the tlist_t
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../include/task_t.h"

struct task_t* newtask(const char* tname)
{
    struct task_t* taskptr = (struct task_t*)malloc(sizeof(struct task_t));
    taskptr->progress = 0;
    memcpy(taskptr->name, tname, sizeof(taskptr->name));

    return taskptr;
}

