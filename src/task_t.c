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

//sets {task->name} to {new-name}
int8_t task_tree_task_set_name(struct task_t* task, const char* new_name)
{
    if(NULL == task) {return -1;}

    memcpy(task->name, new_name, sizeof(task->name));
    return 0;
}

//adds {child_id} to {task->children_id_list}
int8_t task_tree_task_children_list_add_id(struct task_t* task, uint32_t child_id)
{
    if(NULL == task) {return -1;}

    if(0 == task->children_id_list_size || NULL == task->children_id_list)
    {
        task->children_id_list_size = 1;
        task->children_id_list = (uint32_t*)malloc(sizeof(uint32_t));
        task->children_id_list[0] = child_id;
    }
    else
    {
       task->children_id_list_size += 1;
       task->children_id_list = (uint32_t*)(realloc(task->children_id_list, task->children_id_list_size * sizeof(task->children_id_list[0])));
       task->children_id_list[task->children_id_list_size -1] = child_id;
    }
    return 0;
}

//return 1 if it has the child and 0 if not
int8_t task_tree_task_children_list_has_child(struct task_t* task, uint32_t child_id)
{
    if(NULL == task) {return -1;}

    for(uint32_t i = 0; i < task->children_id_list_size; i++)
    {
        if(child_id == task->children_id_list[i])
        {
            return 1;
        }
    }

    return 0;
}

//adds {parent_id} to {task->parents_id list}
int8_t task_tree_task_parents_list_add_id(struct task_t* task, uint32_t parent_id)
{
    if(NULL == task) {return -1;}

    if(0 == task->parents_id_list_size || NULL == task->parents_id_list)
    {
        task->parents_id_list_size = 1;
        task->parents_id_list = (uint32_t*)(malloc(sizeof(uint32_t)));
        task->parents_id_list[0] = parent_id;
    }
    else
    {
        task->parents_id_list_size += 1;
        task->parents_id_list = (uint32_t*)(realloc(task->parents_id_list ,task->parents_id_list_size * sizeof(task->parents_id_list[0])));
        task->parents_id_list[task->parents_id_list_size - 1] = parent_id;
    }
    return 0;
}

//return 1 if it has the parent and 0 if not
int8_t task_tree_task_parents_list_has_child(struct task_t* task, uint32_t parent_id)
{
    if(NULL == task) {return -1;}

    for(uint32_t i = 0; i < task->parents_id_list_size; i++)
    {
        if(parent_id == task->parents_id_list[i])
        {
            return 1;
        }
    }
    return 0;
}
