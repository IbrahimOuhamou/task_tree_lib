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
    uint32_t parents_id_list_size;
    uint32_t children_id_list_size;
    uint32_t *parents_id_list;
    uint32_t *children_id_list;

    //ui
    int16_t pos_x, pos_y; //or maybe incha2Allah pos[2]
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

//removes {child_id} from {task->children_id_list}
int8_t task_tree_task_children_id_list_remove_id(struct task_t* task, uint32_t child_id);

//return 1 if it has the child and 0 if not
int8_t task_tree_task_children_id_list_has_id(struct task_t* task, uint32_t child_id);

//adds {parent_id} to {task->parents_id list}
int8_t task_tree_task_parents_id_list_add_id(struct task_t* task, uint32_t parent_id);

//removes {parent_id} from {task->parents_id list}
//return 0 on succes and -1 on failure
int8_t task_tree_task_parents_id_list_remove_id(struct task_t* task, uint32_t parent_id);

//return 1 if it has the parent and 0 if not
int8_t task_tree_task_parents_id_list_has_id(struct task_t* task, uint32_t parent_id);

//sets tasks's progress without updating the parents' progress.
//will set proress even if {task} has children
//to update the parents' progress use the "tlist_t.h" fumction
int8_t task_tree_task_set_progress(struct task_t* task, uint8_t progress);

#endif

