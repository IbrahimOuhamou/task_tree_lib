//بسم الله الرحمن الرحيم

#ifndef TTREE_T_H
#define TTREE_T_H

#include <stdint.h>

#include "task_t.h"


//a type that holds a task_t array with {size} elements
struct ttree_t
{
    uint32_t size;//size of array

    //due to memory safety it might be changed to be {task_t*} rather than {task_t**}
    //will prefer safety over speed

    //EDIT: due to the the need of having NULL pointers as an {empty slot} it is gonna be an array of pointers by the will of Allah
    struct task_t** data;//actual array
    //(ttree.data[i] == NULL) = (ttree.data[i].name[0] == '\0')
};

                                            /*BismiAllah*/

/***************************************************************************************************/
/****************************************** ttree.. *******************************************/
/***************************************************************************************************/

//inits ttree
int8_t task_tree_ttree_init(struct ttree_t* ttree);

//changes the size of {ttree} to hold {newsize} elements/tasks
int8_t task_tree_ttree_resize(struct ttree_t* ttree, uint32_t newsize);

//frees the memory of the tasks list
int8_t task_tree_ttree_free(struct ttree_t* ttree);


/***************************************************************************************************/
/****************************************** ttree_task.. *******************************************/
/***************************************************************************************************/

//adds a task {task_t} to the task list {ttree_t}
//if {task*} is a NULL pointer creates an empty task
//
//you can call task_tree_ttree_task_add(ttree, task_tree_task_new("BismiAllah tname"))
int8_t task_tree_ttree_add_task(struct ttree_t* ttree, struct task_t* task);

//removes {ttree[task_id]} from {ttree} and de-attaches its children and its parents
int8_t task_tree_ttree_task_free(struct ttree_t* ttree, uint32_t task_id);

/****************************************** ttree_task_children_id_list.. *******************************************/

//adds {child_id} to {ttree[task_id]->children_id_list}
//adds {task_id} to {ttree[chile_id]->parents_id_list}
//updates parents' progress.
int8_t task_tree_ttree_task_children_id_list_add_id(struct ttree_t* ttree, uint32_t task_id, uint32_t child_id);

//removes {child_id} from {ttree[task_id]->children_id_list}
//also removes {task_id} from {ttree[child_id]->parents_id_list}
//update parents' peogress.
int8_t task_tree_ttree_task_children_id_list_remove_id(struct ttree_t *ttree, uint32_t task_id, uint32_t child_id);

/****************************************** ttree_task_parents_id_list.. *******************************************/

//adds {parent_id} to {ttree[task_id]->parents_id_list}
//also adds {task_id} to {ttree[parent_id]->children_id_list}
//updates parents' progress
int8_t task_tree_ttree_task_parents_id_list_add_id(struct ttree_t* ttree, uint32_t task_id, uint32_t parent_id);

//removes {parent_id} from {ttree[task_id]->parents_id_list}
//also removes {task_id} from {ttree[parent_id]->children_id_list}
//updates parents' progress
int8_t task_tree_ttree_task_parents_id_list_remove_id(struct ttree_t* ttree, uint32_t task_id, uint32_t parent_id);

/****************************************** ttree_task_progress.. *******************************************/

//sets the progress of {ttree[task_id]} and calls 'task_tree_ttree_task_update_progress_from_children(ttree, task_id)'
int8_t task_tree_ttree_task_set_progress(struct ttree_t* ttree, uint32_t task_id, uint8_t progress);

//calculates progress from children and updates the progress of {ttree[task_id]} parents
int8_t task_tree_ttree_task_progress_update_from_children(struct ttree_t* ttree, uint32_t task_id);

#endif

