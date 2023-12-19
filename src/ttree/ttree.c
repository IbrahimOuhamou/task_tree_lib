//بسم الله الرحمن الرحيم

#include <stdlib.h>
#include <stdint.h>

#include "../../include/ttree.h"

//check for NULL pointers

//all functions should start with 't_list'
//return 0 on success
//return a negative value on error

/*
int8_t ttree()
{
    //in the name of Allah
}
*/

/***************************************************************************************************/
/********************************** ttree_{data_maniplation} **************************************/
/***************************************************************************************************/

//inits ttree
int8_t task_tree_ttree_init(struct ttree_t* ttree)
{
    if(NULL == ttree){return -1;}

    ttree->size = 0;
    ttree->data = NULL;

    return 0;
}

//changes the size of {ttree} to hold {newsize} elements/tasks
int8_t task_tree_ttree_resize(struct ttree_t* ttree, uint32_t newsize)
{
    if(NULL == ttree){return -1;}
    ttree->size = newsize;

    //should check {newsize} with {ttree->size}
    if(NULL == ttree->data)
    {
        ttree->data = (struct task_t**)malloc(sizeof(struct ttree_t*) * newsize);
        return 0;
    }
    else //for readability added 'else' DON'T REMOVE
    {
        ttree->data = (struct task_t**)realloc(ttree->data, sizeof(void*) * newsize);
        return 0;
    }
}

//frees the memory of the tasks list
int8_t task_tree_ttree_free(struct ttree_t* ttree)
{
    if (NULL == ttree) return -1;

    for(uint32_t i = 0; i < ttree->size; i++)
    {
        if (NULL != ttree->data[i])
        task_tree_task_free(ttree->data[i]);
    }

    free(ttree->data);//free array
    ttree->size = 0;//resets size
    return 0;
}

/***************************************************************************************************/
/******************************************* ttree_task.. *******************************************/
/***************************************************************************************************/

int8_t task_tree_ttree_add_task(struct ttree_t* ttree, struct task_t* task)
{
    if (NULL == ttree) {return -1;}
    task_tree_ttree_resize(ttree, ttree->size + 1);
    if (NULL == task)
    {
        task = task_tree_task_new("Allah Akbar");
    }
    ttree->data[ttree->size - 1] = task;
    task->id = ttree->size - 1;
    return 0;
}

//removes {ttree[task_id]} from {ttree} and de-attaches its children and its parents
int8_t task_tree_ttree_task_free(struct ttree_t* ttree, uint32_t task_id)
{
    if(NULL == ttree) {return -1;}
    if(task_id >= ttree->size) {return -1;}

    if(NULL == ttree->data[task_id]) {return -1;}
    // 
    struct task_t* task = ttree->data[task_id];
    for(uint32_t i = 0; i < task->children_id_list_size; i++)
    {
        task_tree_ttree_task_children_id_list_remove_id(ttree, task_id, task->children_id_list[i]);
    }
    for(uint32_t i = 0; i < task->parents_id_list_size; i++)
    {
        task_tree_ttree_task_parents_id_list_remove_id(ttree, task_id, task->parents_id_list[i]);
    }
    task_tree_ttree_task_progress_update_from_children(ttree, task_id);
    task_tree_task_free(task);
    ttree->data[task_id] = NULL;
    return 0;
}

/****************************************** ttree_task_child.. *******************************************/

//adds {child_id} to {ttree[task_id]->children_id_list}
//also adds {task_id} to {ttree[chile_id]->parents_id_list}
//
//return 0 on success and a negative value on failure
int8_t task_tree_ttree_task_children_id_list_add_id(struct ttree_t* ttree, uint32_t task_id, uint32_t child_id)
{
    if(NULL == ttree) {return -1;}
    //make sure it is in bound
    if(child_id >= ttree->size || task_id >= ttree->size) {return -1;}

    //for easy use
    struct task_t* task = ttree->data[task_id];
    struct task_t* child = ttree->data[child_id];
    if(NULL == task || NULL == child) {return -1;}

    task_tree_task_children_id_list_add_id(task, child_id);
    task_tree_task_parents_id_list_add_id(child, task_id);

    task_tree_ttree_task_progress_update_from_children(ttree, task_id);
    return 0;
}

//removes {child_id} from {ttree[task_id]->children_id_list}
//also removes {task_id} from {ttree[child_id]->parents_id_list}
//update parents' peogress.
int8_t task_tree_ttree_task_children_id_list_remove_id(struct ttree_t *ttree, uint32_t task_id, uint32_t child_id)
{
    if(NULL == ttree) {return -1;}
    //make sure it is in bound
    if(child_id >= ttree->size || task_id >= ttree->size) {return -1;}

    //for easy use
    struct task_t* task = ttree->data[task_id];
    struct task_t* child = ttree->data[child_id];
    if(NULL == task || NULL == child) {return -1;}
    
    task_tree_task_children_id_list_remove_id(task, child_id);
    task_tree_task_parents_id_list_remove_id(child, task_id);

    task_tree_ttree_task_progress_update_from_children(ttree, task_id);
    return 0;
}


/****************************************** ttree_task_parent.. *******************************************/

//adds {parent_id} to {ttree[task_id]->parents_id_list}
//also adds {task_id} to {ttree[parent_id]->children_id_list}
//
//return 0 on success and a negative value on failure
int8_t task_tree_ttree_task_parents_id_list_add_id(struct ttree_t* ttree, uint32_t task_id, uint32_t parent_id)
{
    if(NULL == ttree) {return -1;}
    //make sure it is in range
    if(parent_id >= ttree->size || task_id >= ttree->size) {return -1;}

    //for easy use
    struct task_t* task = ttree->data[task_id];
    struct task_t* parent = ttree->data[parent_id];
    if(NULL == task || NULL == parent) {return -1;}

    task_tree_task_parents_id_list_add_id(task, parent_id);
    task_tree_task_children_id_list_add_id(parent, task_id);
    
    task_tree_ttree_task_progress_update_from_children(ttree, task_id);
    return 0;
}

//removes {parent_id} from {ttree[task_id]->parents_id_list}
//also removes {task_id} from {ttree[parent_id]->children_id_list}
//updates parents' progress
int8_t task_tree_ttree_task_parents_id_list_remove_id(struct ttree_t* ttree, uint32_t task_id, uint32_t parent_id)
{
    if(NULL == ttree) {return -1;}
    //make sure it is in range
    if(parent_id >= ttree->size || task_id >= ttree->size) {return -1;}

    //for easy use
    struct task_t* task = ttree->data[task_id];
    struct task_t* parent = ttree->data[parent_id];
    if(NULL == task || NULL == parent) {return -1;}

    task_tree_task_parents_id_list_remove_id(task, parent_id);
    task_tree_task_children_id_list_remove_id(parent, task_id);

    task_tree_ttree_task_progress_update_from_children(ttree, task_id);
    return 0;
}

/****************************************** ttree_task_progress.. *******************************************/

//sets the progress of {ttree[task_id]} and calls 'task_tree_ttree_task_update_progress_from_children(ttree, task_id)'
int8_t task_tree_ttree_task_set_progress(struct ttree_t* ttree, uint32_t task_id, uint8_t progress)
{
    if(NULL == ttree) {return -1;}
    //make sure it is in range
    if(task_id >= ttree->size) {return -1;}
    if(100 < progress) {progress = 100;}
    
    struct task_t* task = ttree->data[task_id];
    if(NULL == task) {return -1;}

    task->progress = progress;
    task_tree_ttree_task_progress_update_from_children(ttree, task_id);
    return 0;
}

//calculates progress from children and updates the progress of {ttree[task_id]} parents
int8_t task_tree_ttree_task_progress_update_from_children(struct ttree_t* ttree, uint32_t task_id)
{
    if(NULL == ttree) {return -1;}
    //make sure it is in range
    if(task_id >= ttree->size) {return -1;}
    struct task_t* task = ttree->data[task_id];
    if(NULL == task) {return -1;}

    uint16_t progress_sum = 0;
    for (uint32_t i = 0; i < task->children_id_list_size; i++)
    {
        struct task_t* child = ttree->data[task->children_id_list[i]];
        if(NULL == child) {continue;}
        progress_sum += child->progress;
    }
    task->progress = (uint8_t) (progress_sum / task->children_id_list_size);
    if (100 < task->progress)
    {
        task->progress = 100;
    }
    return 0;
}

