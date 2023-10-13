//بسم الله الرحمن الرحيم

#include <stdint.h>

#include "task_t.c"


//a type that holds a task_t array with {size} elements
struct tlist_t
{
    uint32_t size;//size of array

    //due to memory safety it might be changed to be {task_t*} rather than {task_t**}
    //will prefer safety over speed
    
    struct task_t* data;//actual array
    //(tlist.data[i] == NULL) = (tlist.data[i].name[0] == '\0')
}

