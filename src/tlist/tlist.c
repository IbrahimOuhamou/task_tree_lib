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
    else //for readability added 'else' DON'T REMOVE
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

int8_t task_tree_tlist_add_task(struct tlist_t* tlist, struct task_t* task)
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

//removes {tlist[task_id]} from {tlist} and de-attaches its children and its parents
int8_t task_tree_tlist_task_free(struct tlist_t* tlist, uint32_t task_id)
{
    if(NULL == tlist) {return -1;}
    if(task_id >= tlist->size) {return -1;}

    if(NULL == tlist->data[task_id]) {return -1;}
    // 
    struct task_t* task = tlist->data[task_id];
    for(uint32_t i = 0; i < task->children_id_list_size; i++)
    {
        task_tree_tlist_task_children_id_list_remove_id(tlist, task_id, task->children_id_list[i]);
    }
    for(uint32_t i = 0; i < task->parents_id_list_size; i++)
    {
        task_tree_tlist_task_parents_id_list_remove_id(tlist, task_id, task->parents_id_list[i]);
    }
    task_tree_tlist_task_progress_update_from_children(tlist, task_id);
    task_tree_task_free(task);
    return 0;
}

/****************************************** tlist_task_child.. *******************************************/

//adds {child_id} to {tlist[task_id]->children_id_list}
//also adds {task_id} to {tlist[chile_id]->parents_id_list}
//
//return 0 on success and a negative value on failure
int8_t task_tree_tlist_task_children_id_list_add_id(struct tlist_t* tlist, uint32_t task_id, uint32_t child_id)
{
    if(NULL == tlist) {return -1;}
    //make sure it is in bound
    if(child_id >= tlist->size || task_id >= tlist->size) {return -1;}

    //for easy use
    struct task_t* task = tlist->data[task_id];
    struct task_t* child = tlist->data[child_id];
    if(NULL == task || NULL == child) {return -1;}

    task_tree_task_children_id_list_add_id(task, child_id);
    task_tree_task_parents_id_list_add_id(child, task_id);

    task_tree_tlist_task_progress_update_from_children(tlist, task_id);
    return 0;
}

//removes {child_id} from {tlist[task_id]->children_id_list}
//also removes {task_id} from {tlist[child_id]->parents_id_list}
//update parents' peogress.
int8_t task_tree_tlist_task_children_id_list_remove_id(struct tlist_t *tlist, uint32_t task_id, uint32_t child_id)
{
    if(NULL == tlist) {return -1;}
    //make sure it is in bound
    if(child_id >= tlist->size || task_id >= tlist->size) {return -1;}

    //for easy use
    struct task_t* task = tlist->data[task_id];
    struct task_t* child = tlist->data[child_id];
    if(NULL == task || NULL == child) {return -1;}
    
    task_tree_task_children_id_list_remove_id(task, child_id);
    task_tree_task_parents_id_list_remove_id(child, task_id);

    task_tree_tlist_task_progress_update_from_children(tlist, task_id);
    return 0;
}


/****************************************** tlist_task_parent.. *******************************************/

//adds {parent_id} to {tlist[task_id]->parents_id_list}
//also adds {task_id} to {tlist[parent_id]->children_id_list}
//
//return 0 on success and a negative value on failure
int8_t task_tree_tlist_task_parents_id_list_add_id(struct tlist_t* tlist, uint32_t task_id, uint32_t parent_id)
{
    if(NULL == tlist) {return -1;}
    //make sure it is in range
    if(parent_id >= tlist->size || task_id >= tlist->size) {return -1;}

    //for easy use
    struct task_t* task = tlist->data[task_id];
    struct task_t* parent = tlist->data[parent_id];
    if(NULL == task || NULL == parent) {return -1;}

    task_tree_task_parents_id_list_add_id(task, parent_id);
    task_tree_task_children_id_list_add_id(parent, task_id);
    
    task_tree_tlist_task_progress_update_from_children(tlist, task_id);
    return 0;
}

//removes {parent_id} from {tlist[task_id]->parents_id_list}
//also removes {task_id} from {tlist[parent_id]->children_id_list}
//updates parents' progress
int8_t task_tree_tlist_task_parents_id_list_remove_id(struct tlist_t* tlist, uint32_t task_id, uint32_t parent_id)
{
    if(NULL == tlist) {return -1;}
    //make sure it is in range
    if(parent_id >= tlist->size || task_id >= tlist->size) {return -1;}

    //for easy use
    struct task_t* task = tlist->data[task_id];
    struct task_t* parent = tlist->data[parent_id];
    if(NULL == task || NULL == parent) {return -1;}

    task_tree_task_parents_id_list_remove_id(task, parent_id);
    task_tree_task_children_id_list_remove_id(parent, task_id);

    task_tree_tlist_task_progress_update_from_children(tlist, task_id);
    return 0;
}

/****************************************** tlist_task_progress.. *******************************************/

//sets the progress of {tlist[task_id]} and calls 'task_tree_tlist_task_update_progress_from_children(tlist, task_id)'
int8_t task_tree_tlist_task_set_progress(struct tlist_t* tlist, uint32_t task_id, uint8_t progress)
{
    if(NULL == tlist) {return -1;}
    //make sure it is in range
    if(task_id >= tlist->size) {return -1;}
    if(100 < progress) {progress = 100;}
    
    struct task_t* task = tlist->data[task_id];
    if(NULL == task) {return -1;}

    task->progress = progress;
    task_tree_tlist_task_progress_update_from_children(tlist, task_id);
    return 0;
}

//calculates progress from children and updates the progress of {tlist[task_id]} parents
int8_t task_tree_tlist_task_progress_update_from_children(struct tlist_t* tlist, uint32_t task_id)
{
    if(NULL == tlist) {return -1;}
    //make sure it is in range
    if(task_id >= tlist->size) {return -1;}
    struct task_t* task = tlist->data[task_id];
    if(NULL == task) {return -1;}

    uint16_t progress_sum = 0;
    for (uint32_t i = 0; i < task->children_id_list_size; i++)
    {
        struct task_t* child = tlist->data[task->parents_id_list[i]];
        progress_sum += child->progress;
    }
    task->progress = progress_sum / task->children_id_list_size;
    if (100 < task->progress)
    {
        task->progress = 100;
    }
    return 0;
}

