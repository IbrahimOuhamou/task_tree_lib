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
/****************************************** tlist_task.. *******************************************/
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
int8_t task_tree_tlist_task_add(struct tlist_t* tlist, struct task_t* task);

#endif

