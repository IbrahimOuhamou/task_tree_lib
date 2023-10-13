//بسم الله الرحمن الرحيم

#include <stdlib.h>
#include <stdint.h>

#include "../tlist_t.c"

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
    //
}

//frees the momory of the tasks list
int8_t tlist_free(struct tlist_t* tlist)
{
    free(tlist->data);//free array
    tlist->size = 0;//resets size
}

/***************************************************************************************************/
/******************************************* tlist_add.. *******************************************/
/***************************************************************************************************/

//adds a task {task_t} to the task list {tlist_t}
int8_t tlist_add_task(struct tlist_t* tlist, struct task_t* task)
{
    
}

