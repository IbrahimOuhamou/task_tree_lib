//بسم الله الرحمن الرحيم


//this file should NOT be included directly and all manupilations should be done to the tlist_t
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../include/task_t.h"

struct task_t* tasknew(const char* tname)
{
    struct task_t* taskptr = (struct task_t*)malloc(sizeof(struct task_t));
    taskptr->progress = 0;
    memcpy(taskptr->name, tname, sizeof(taskptr->name));
    taskptr->progress = 0;

    return taskptr;
}

int8_t taskfree(struct task_t* task)
{
    if(NULL == task) {return 0;}

    
    //Incha2Allah this part should be the last thing
    free(task);
    return 0;
}
