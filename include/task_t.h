//بسم الله الرحمن الرحيم

#ifndef TASK_T_H
#define TASK_T_H

#include <stdint.h>

struct task_t
{
    uint32_t id;
    char name[36];
    uint8_t progress;

    /*array of parents IDs*/
    uint8_t parents_id_list_size;
    uint8_t children_id_list_size;
    uint32_t* parents_id_list;
    uint32_t* children_id_list;

    //time_t or equivalent
};

//returns a new {task_t*}
struct task_t* task_tree_task_new(const char* tname);

//frees {task} and it children
int8_t task_tree_task_free(struct task_t* task);

//sets {task->name} to {new-name}
int8_t task_tree_task_set_name(struct task_t* task, const char* new_name);

//adds {child_id} to {task->children_id_list}
int8_t task_tree_task_children_id_list_add_id(struct task_t* task, uint32_t child_id);

//return 1 if it has the child and 0 if not
int8_t task_tree_task_children_id_list_has_child(struct task_t* task, uint32_t child_id);

//adds {parent_id} to {task->parents_id list}
int8_t task_tree_task_parents_id_list_add_id(struct task_t* task, uint32_t parent_id);

//return 1 if it has the parent and 0 if not
int8_t task_tree_task_parents_id_list_has_child(struct task_t* task, uint32_t parent_id);

#endif
