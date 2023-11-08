//بسم الله الرحمن الرحيم

#include <stdlib.h>
#include <stdint.h>

#include "../../include/tlist.h"

//check for NULL pointers

//all functions should start with 't_list'
//return 0 on success
//return a negative value on error

/*
int8_t tlist()
{
    //in the name of Allah
}
*/

/***************************************************************************************************/
/********************************** tlist_{data_maniplation} **************************************/
/***************************************************************************************************/

//inits tlist
int8_t task_tree_tlist_init(struct tlist_t* tlist)
{
    if(NULL == tlist){return -1;}

    tlist->size = 0;
    tlist->data = NULL;

  return 0;
}

//changes the size of {tlist} to hold {newsize} elements/tasks
int8_t task_tree_tlist_resize(struct tlist_t* tlist, uint32_t newsize)
{
    if(NULL == tlist){return -1;}
    tlist->size = newsize;

    //should check {newsize} with {tlist->size}
    if(NULL == tlist->data)
    {
        tlist->data = (struct task_t**)malloc(sizeof(struct tlist_t*) * newsize);
        return 0;
    }
    else //for readability
    {
        tlist->data = (struct task_t**)realloc(tlist->data, sizeof(void*) * newsize);
        return 0;
    }
}

//frees the memory of the tasks list
int8_t task_tree_tlist_free(struct tlist_t* tlist)
{
    if (NULL == tlist) return -1;

    for(uint32_t i = 0; i < tlist->size; i++)
    {
        if (NULL != tlist->data[i])
        task_tree_task_free(tlist->data[i]);
    }

    free(tlist->data);//free array
    tlist->size = 0;//resets size
    return 0;
}

/***************************************************************************************************/
/******************************************* tlist_task.. *******************************************/
/***************************************************************************************************/

int8_t task_tree_tlist_task_add(struct tlist_t* tlist, struct task_t* task)
{
    if (NULL == tlist) {return -1;}
    task_tree_tlist_resize(tlist, tlist->size + 1);
    if (NULL == task)
    {
        task = task_tree_task_new("Allah Akbar");
    }
    tlist->data[tlist->size - 1] = task;
    task->id = tlist->size - 1;
    return 0;
}

/****************************************** tlist_task_child.. *******************************************/

//adds {child_id} to {tlist[task_id]->children_list}
//also adds {task_id} to {tlist[chile_id]->parents_list}
//
//return 0 on success and a negative value on failure
int8_t task_tree_task_child_add(struct tlist_t* tlist, uint32_t task_id, uint32_t child_id)
{
    if(NULL == tlist) {return -1;}
    //make sure it is in bound
    if(child_id >= tlist->size || task_id >= tlist->size) {return -1;}

    //for easy use
    struct task_t* task = tlist->data[task_id];
    struct task_t* child = tlist->data[child_id];
    if(NULL == task || NULL == child) {return -1;}


    //add {child_id} to {tlist[task_id]->children_list}
    task->children_id_list_size += 1;
    task->children_id_list = (uint32_t*)(realloc(task->children_id_list, task->children_id_list_size));
    task->children_id_list[task->children_id_list_size -1] = child_id;

    //add {task_id} to {child->parents_id_list}
    child->parents_id_list_size += 1;
    child->parents_id_list = (uint32_t*)(realloc(child->parents_id_list, child->parents_id_list_size));
    child->parents_id_list[child->parents_id_list_size - 1] = task_id;
    return 0;
}

/****************************************** tlist_task_parent.. *******************************************/

//adds {parent_id} to {tlist[task_id]->parents_list}
//also adds {task_id} to {tlist[parent_id]->children_list}
//
//return 0 on success and a negative value on failure
int8_t task_tree_task_parent_add(struct tlist_t* tlist, uint32_t task_id, uint32_t parent_id)
{
    if(NULL == tlist) {return -1;}
    //make sure it is in bound
    if(parent_id >= tlist->size || task_id >= tlist->size) {return -1;}

    //for easy use
    struct task_t* task = tlist->data[task_id];
    struct task_t* parent = tlist->data[parent_id];
    if(NULL == task || NULL == parent) {return -1;}


    //add {parent_id} to {tlist[task_id]->parents_list}
    task->parents_id_list_size += 1;
    task->parents_id_list = (uint32_t*)(realloc(task->parents_id_list ,task->parents_id_list_size));
    task->parents_id_list[task->parents_id_list_size - 1] = parent_id;

    //also adds {task_id} to {tlist[parent_id]->children_list}
    parent->children_id_list_size += 1;
    parent->children_id_list = (uint32_t*)(realloc(parent->children_id_list, parent->children_id_list_size));
    parent->children_id_list[parent->children_id_list_size -1] = task_id;

    return 0;
}

