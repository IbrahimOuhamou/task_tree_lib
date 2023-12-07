//بسم الله الرحمن الرحيم

#ifndef TLIST_T_H
#define TLIST_T_H

#include <stdint.h>

#include "task_t.h"


//a type that holds a task_t array with {size} elements
struct tlist_t
{
    uint32_t size;//size of array

    //due to memory safety it might be changed to be {task_t*} rather than {task_t**}
    //will prefer safety over speed

    //EDIT: due to the the need of having NULL pointers as an {empty slot} it is gonna be an array of pointers by the will of Allah
    struct task_t** data;//actual array
    //(tlist.data[i] == NULL) = (tlist.data[i].name[0] == '\0')
};

                                            /*BismiAllah*/

/***************************************************************************************************/
/****************************************** tlist.. *******************************************/
/***************************************************************************************************/

//inits tlist
int8_t task_tree_tlist_init(struct tlist_t* tlist);

//changes the size of {tlist} to hold {newsize} elements/tasks
int8_t task_tree_tlist_resize(struct tlist_t* tlist, uint32_t newsize);

//frees the memory of the tasks list
int8_t task_tree_tlist_free(struct tlist_t* tlist);


/***************************************************************************************************/
/****************************************** tlist_task.. *******************************************/
/***************************************************************************************************/

//adds a task {task_t} to the task list {tlist_t}
//if {task*} is a NULL pointer creates an empty task
//
//you can call task_tree_tlist_task_add(tlist, task_tree_task_new("BismiAllah tname"))
int8_t task_tree_tlist_add_task(struct tlist_t* tlist, struct task_t* task);

//removes {tlist[task_id]} from {tlist} and de-attaches its children and its parents
int8_t task_tree_tlist_task_free(struct tlist_t* tlist, uint32_t task_id);

/****************************************** tlist_task_children_id_list.. *******************************************/

//adds {child_id} to {tlist[task_id]->children_id_list}
//adds {task_id} to {tlist[chile_id]->parents_id_list}
//updates parents' progress.
int8_t task_tree_tlist_task_children_id_list_add_id(struct tlist_t* tlist, uint32_t task_id, uint32_t child_id);

//removes {child_id} from {tlist[task_id]->children_id_list}
//also removes {task_id} from {tlist[child_id]->parents_id_list}
//update parents' peogress.
int8_t task_tree_tlist_task_children_id_list_remove_id(struct tlist_t *tlist, uint32_t task_id, uint32_t child_id);

/****************************************** tlist_task_parents_id_list.. *******************************************/

//adds {parent_id} to {tlist[task_id]->parents_id_list}
//also adds {task_id} to {tlist[parent_id]->children_id_list}
//updates parents' progress
int8_t task_tree_tlist_task_parents_id_list_add_id(struct tlist_t* tlist, uint32_t task_id, uint32_t parent_id);

//removes {parent_id} from {tlist[task_id]->parents_id_list}
//also removes {task_id} from {tlist[parent_id]->children_id_list}
//updates parents' progress
int8_t task_tree_tlist_task_parents_id_list_remove_id(struct tlist_t* tlist, uint32_t task_id, uint32_t parent_id);

/****************************************** tlist_task_progress.. *******************************************/

//sets the progress of {tlist[task_id]} and calls 'task_tree_tlist_task_update_progress_from_children(tlist, task_id)'
int8_t task_tree_tlist_task_set_progress(struct tlist_t* tlist, uint32_t task_id, uint8_t progress);

//calculates progress from children and updates the progress of {tlist[task_id]} parents
int8_t task_tree_tlist_task_progress_update_from_children(struct tlist_t* tlist, uint32_t task_id);

#endif

