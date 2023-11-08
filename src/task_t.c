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
    taskptr->children_id_list_size = 0;
    taskptr->parents_id_list_size = 0;
    taskptr->children_id_list = NULL;
    taskptr->parents_id_list = NULL;

    return taskptr;
}

int8_t task_tree_task_free(struct task_t* task)
{
    if(NULL == task) {return 0;}

    if(NULL != task->children_id_list) {free(task->children_id_list);}
    if(NULL != task->parents_id_list) {free(task->parents_id_list);}

    //Incha2Allah this part should be the last thing
    free(task);
    return 0;
}
