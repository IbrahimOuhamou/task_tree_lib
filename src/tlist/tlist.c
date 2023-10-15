//بسم الله الرحمن الرحيم

#include <stdlib.h>
#include <stdint.h>

#include "../../include/tlist.h"

//check for NULL poiters

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
/********************************** tlist_{data_manupilation} **************************************/
/***************************************************************************************************/

//changes the size of {tlist} to hold {newsize} elements/tasks
int8_t tlist_resize(struct tlist_t* tlist, uint32_t newsize)
{
    if(NULL == tlist) return -1;
    //should check {newsize} with {tlist->size}
    tlist->data = realloc(tlist->data, sizeof(struct  tlist_t*) * newsize);
}

//frees the momory of the tasks list
int8_t tlist_free(struct tlist_t* tlist)
{
    if (NULL == tlist) return -1;
    for(uint32_t i = 0; i < tlist->size; i++)
    {
	if (NULL != tlist->data[i])
            free(tlist->data[i]);
    }
    free(tlist->data);//free array
    tlist->size = 0;//resets size
}

/***************************************************************************************************/
/******************************************* tlist_add.. *******************************************/
/***************************************************************************************************/

//adds a task {task_t} to the task list {tlist_t}
//if {task*} is a NULL pointer creates an empty task
//
//you can call tlist_add_task(tlist, newtask("BismiAllah tname"))
int8_t tlist_add_task(struct tlist_t* tlist, struct task_t* task)
{
    if (NULL == tlist) return -1;
    
    tlist_resize(tlist ,tlist->size + 1);
    
    if (NULL == task)
    {
        task = malloc(sizeof(struct task_t));
    }
    
    tlist->data[tlist->size - 1] = task;
    
    task->id = tlist->size - 1;
    return 0;

    return -1;
}

