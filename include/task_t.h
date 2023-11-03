//بسم الله الرحمن الرحيم

#ifndef TASK_T_H
#define TASK_T_H

#include <stdint.h>

struct task_t
{
    uint32_t id;
    uint8_t progress;
    char name[30];
    //uint32 parents_id_list, children_id_list;
    //time_t or equivalent
};

struct task_t* task_tree_task_new(const char* tname);
int8_t task_tree_task_free(struct task_t* task);

#endif
