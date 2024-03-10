//بسم الله الرحمن الرحيم

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "../../include/tlist.h"

//check for NULL pointers

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
/********************************** tlist_{data_maniplation} **************************************/
/***************************************************************************************************/

//inits tlist
int8_t task_tree_tlist_init(struct tlist_t* tlist)
{
    if(NULL == tlist){return -1;}

    tlist->size = 0;
    tlist->data = NULL;

    return 0;
}

//changes the size of {tlist} to hold {newsize} elements/tasks
int8_t task_tree_tlist_resize(struct tlist_t* tlist, uint32_t newsize)
{
    if(NULL == tlist){return -1;}
    tlist->size = newsize;

    //should check {newsize} with {tlist->size}
    if(NULL == tlist->data)
    {
        tlist->data = (struct task_t**)malloc(sizeof(struct tlist_t*) * newsize);
        return 0;
    }
    else //for readability added 'else' DON'T REMOVE
    {
        tlist->data = (struct task_t**)realloc(tlist->data, sizeof(void*) * newsize);
        return 0;
    }
}

//frees the memory of the tasks list
int8_t task_tree_tlist_free(struct tlist_t* tlist)
{
    if (NULL == tlist) return -1;

    for(uint32_t i = 0; i < tlist->size; i++)
    {
        if (NULL != tlist->data[i])
        task_tree_task_free(tlist->data[i]);
    }

    free(tlist->data);//free array
    tlist->size = 0;//resets size
    return 0;
}

/***************************************************************************************************/
/******************************************* tlist_task.. *******************************************/
/***************************************************************************************************/

int8_t task_tree_tlist_add_task(struct tlist_t* tlist, struct task_t* task)
{
    if (NULL == tlist) {return -1;}
    task_tree_tlist_resize(tlist, tlist->size + 1);
    if (NULL == task)
    {
        task = task_tree_task_new("Allah Akbar");
    }
    tlist->data[tlist->size - 1] = task;
    task->id = tlist->size - 1;
    return 0;
}

//removes {tlist[task_id]} from {tlist} and de-attaches its children and its parents
int8_t task_tree_tlist_task_free(struct tlist_t* tlist, uint32_t task_id)
{
    if(NULL == tlist) {return -1;}
    if(task_id >= tlist->size) {return -1;}

    if(NULL == tlist->data[task_id]) {return -1;}
    // 
    struct task_t* task = tlist->data[task_id];
    for(uint32_t i = 0; i < task->children_id_list_size; i++)
    {
        task_tree_tlist_task_children_id_list_remove_id(tlist, task_id, task->children_id_list[i]);
    }
    for(uint32_t i = 0; i < task->parents_id_list_size; i++)
    {
        task_tree_tlist_task_parents_id_list_remove_id(tlist, task_id, task->parents_id_list[i]);
    }
    task_tree_tlist_task_progress_update_from_children(tlist, task_id);
    task_tree_task_free(task);
    tlist->data[task_id] = NULL;
    return 0;
}

/****************************************** tlist_task_child.. *******************************************/

//adds {child_id} to {tlist[task_id]->children_id_list}
//also adds {task_id} to {tlist[chile_id]->parents_id_list}
//
//return 0 on success and a negative value on failure
int8_t task_tree_tlist_task_children_id_list_add_id(struct tlist_t* tlist, uint32_t task_id, uint32_t child_id)
{
    if(NULL == tlist) {return -1;}
    //make sure it is in bound
    if(child_id >= tlist->size || task_id >= tlist->size) {return -1;}

    //for easy use
    struct task_t* task = tlist->data[task_id];
    struct task_t* child = tlist->data[child_id];
    if(NULL == task || NULL == child) {return -1;}

    task_tree_task_children_id_list_add_id(task, child_id);
    task_tree_task_parents_id_list_add_id(child, task_id);

    task_tree_tlist_task_progress_update_from_children(tlist, task_id);
    return 0;
}

//removes {child_id} from {tlist[task_id]->children_id_list}
//also removes {task_id} from {tlist[child_id]->parents_id_list}
//update parents' peogress.
int8_t task_tree_tlist_task_children_id_list_remove_id(struct tlist_t *tlist, uint32_t task_id, uint32_t child_id)
{
    if(NULL == tlist) {return -1;}
    //make sure it is in bound
    if(child_id >= tlist->size || task_id >= tlist->size) {return -1;}

    //for easy use
    struct task_t* task = tlist->data[task_id];
    struct task_t* child = tlist->data[child_id];
    if(NULL == task || NULL == child) {return -1;}
    
    task_tree_task_children_id_list_remove_id(task, child_id);
    task_tree_task_parents_id_list_remove_id(child, task_id);

    task_tree_tlist_task_progress_update_from_children(tlist, task_id);
    return 0;
}


/****************************************** tlist_task_parent.. *******************************************/

//adds {parent_id} to {tlist[task_id]->parents_id_list}
//also adds {task_id} to {tlist[parent_id]->children_id_list}
//
//return 0 on success and a negative value on failure
int8_t task_tree_tlist_task_parents_id_list_add_id(struct tlist_t* tlist, uint32_t task_id, uint32_t parent_id)
{
    if(NULL == tlist) {return -1;}
    //make sure it is in range
    if(parent_id >= tlist->size || task_id >= tlist->size) {return -1;}

    //for easy use
    struct task_t* task = tlist->data[task_id];
    struct task_t* parent = tlist->data[parent_id];
    if(NULL == task || NULL == parent) {return -1;}

    task_tree_task_parents_id_list_add_id(task, parent_id);
    task_tree_task_children_id_list_add_id(parent, task_id);
    
    task_tree_tlist_task_progress_update_from_children(tlist, task_id);
    return 0;
}

//removes {parent_id} from {tlist[task_id]->parents_id_list}
//also removes {task_id} from {tlist[parent_id]->children_id_list}
//updates parents' progress
int8_t task_tree_tlist_task_parents_id_list_remove_id(struct tlist_t* tlist, uint32_t task_id, uint32_t parent_id)
{
    if(NULL == tlist) {return -1;}
    //make sure it is in range
    if(parent_id >= tlist->size || task_id >= tlist->size) {return -1;}

    //for easy use
    struct task_t* task = tlist->data[task_id];
    struct task_t* parent = tlist->data[parent_id];
    if(NULL == task || NULL == parent) {return -1;}

    task_tree_task_parents_id_list_remove_id(task, parent_id);
    task_tree_task_children_id_list_remove_id(parent, task_id);

    task_tree_tlist_task_progress_update_from_children(tlist, task_id);
    return 0;
}

/****************************************** tlist_task_progress.. *******************************************/

//sets the progress of {tlist[task_id]} and calls 'task_tree_tlist_task_update_progress_from_children(tlist, task_id)'
int8_t task_tree_tlist_task_set_progress(struct tlist_t* tlist, uint32_t task_id, uint8_t progress)
{
    if(NULL == tlist) {return -1;}
    //make sure it is in range
    if(task_id >= tlist->size) {return -1;}
    if(100 < progress) {progress = 100;}
    
    struct task_t* task = tlist->data[task_id];
    if(NULL == task) {return -1;}

    task->progress = progress;
    task_tree_tlist_task_progress_update_from_children(tlist, task_id);
    return 0;
}

//calculates progress from children and updates the progress of {tlist[task_id]} parents
int8_t task_tree_tlist_task_progress_update_from_children(struct tlist_t* tlist, uint32_t task_id)
{
    if(NULL == tlist) {return -1;}
    //make sure it is in range
    if(task_id >= tlist->size) {return -1;}
    struct task_t* task = tlist->data[task_id];
    if(NULL == task) {return -1;}

    uint16_t progress_sum = 0;
    for (uint32_t i = 0; i < task->children_id_list_size; i++)
    {
        struct task_t* child = tlist->data[task->children_id_list[i]];
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

/****************************************** tlist_task_search... ********************************************/

//returns {id} of task with {tname} and sizeof(task_t->id) if not
uint32_t task_tree_tlist_search_name(struct tlist_t *tlist, const char *tname)
{
    if(NULL == tlist || NULL == tname || '\0' == tname[0]) return sizeof(tlist->data[0]->id);

    for(uint32_t i = 0; i < tlist->size; i++)
    {
        if(0 == strcmp(tlist->data[i]->name, tname))
        {
            return i;
        }
    }

    return sizeof(tlist->data[0]->id);
}

/***************************************************************************************************/
/****************************************** tlist_file.. *******************************************/
/***************************************************************************************************/

//============ file structure
//============ uint8_t version[3] - tlist->size
//============ tlist->data[0].id - tlist->data[0].name - tlist->data[0].progress
//============ .
//============ .
//============ .
//============ tlist->data[tlist->size].id - tlist->data[tlist->size].name - tlist->data[tlist->size].progress

//saves tlist data onto the file provided
//returns 0 on success and -1 on failure
int8_t task_tree_tlist_file_save(struct tlist_t *tlist, const char *path)
{
    if(NULL == tlist || NULL == path) return -1;

    FILE *fp = fopen(path, "wb");
    if(NULL == fp) return -1;

    uint8_t version[3] = {1, 0, 0};
    fwrite(version, sizeof(version[0]), sizeof(version) / sizeof(version[0]), fp);
    fwrite(&tlist->size, sizeof(tlist->size), 1, fp);

    for(uint32_t i = 0; i < tlist->size; i++)
    {
        struct task_t *task = tlist->data[i];
        fwrite(&task->id, sizeof(task->id), 1, fp);
        fwrite(&task->name[0], sizeof(task->name[0]), sizeof(task->name) / sizeof(task->name[0]), fp);
        fwrite(&task->parents_id_list_size, sizeof(task->parents_id_list_size), 1, fp);
        fwrite(task->parents_id_list, sizeof(task->parents_id_list[0]), task->parents_id_list_size, fp);
        fwrite(&task->children_id_list_size, sizeof(task->children_id_list_size), 1, fp);
        fwrite(task->children_id_list, sizeof(task->children_id_list[0]), task->children_id_list_size, fp);
    }
    fclose(fp);
    return 0;
}

//loads tlist data from the file provided
//returns 0 on success and -1 on failure
int8_t task_tree_tlist_file_load(struct tlist_t *tlist, const char *path)
{
    if(NULL == tlist || NULL == path) return -1;

    task_tree_tlist_free(tlist);
    FILE *fp = fopen(path, "rb");

    if(NULL == fp) return -1;

    uint8_t version[3];
    fread(version, sizeof(version[0]), sizeof(version) / sizeof(version[0]), fp);
    fread(&tlist->size, sizeof(tlist->size), 1, fp);

    task_tree_tlist_resize(tlist, tlist->size);
    for(uint32_t i = 0; i < tlist->size; i++)
    {
        struct task_t *task = task_tree_task_new("bismi_allah");
        tlist->data[i] = task;
        fread(&task->id, sizeof(task->id), 1, fp);
        
        char task_name_buffer[sizeof(task->name)];
        fread(task_name_buffer, sizeof(task->name[0]), sizeof(task->name) / sizeof(task->name[0]), fp);
        task_tree_task_set_name(task, task_name_buffer);

        fread(&task->parents_id_list_size, sizeof(task->parents_id_list_size), 1, fp);
        task->parents_id_list = (uint32_t*)malloc(task->parents_id_list_size * sizeof(task->id));
        fread(task->parents_id_list, sizeof(task->id), task->parents_id_list_size, fp);
        fread(&task->children_id_list_size, sizeof(task->children_id_list_size), 1, fp);
        task->parents_id_list = (uint32_t*)malloc(task->children_id_list_size * sizeof(task->id));
        fread(task->children_id_list, sizeof(task->id), task->children_id_list_size, fp);
    }

    fclose(fp);
}

