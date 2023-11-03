//بسم الله الرحمن الرحيم


//this file should NOT be included directly and all manipulations should be done to the tlist_t
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../include/task_t.h"

struct task_t* task_tree_task_new(const char* tname)
{
    struct task_t* taskptr = (struct task_t*)malloc(sizeof(struct task_t));
    taskptr->progress = 0;
    memcpy(taskptr->name, tname, sizeof(taskptr->name));

    return taskptr;
}

int8_t task_tree_task_free(struct task_t* task)
{
    if(NULL == task) {return 0;}

    //Incha2Allah this part should be the last thing
    free(task);
    return 0;
}
