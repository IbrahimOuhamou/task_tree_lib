//بسم الله الرحمن الرحيم

#include "../../include/task_t.h"
#include "../../include/ttree.h"
#include "../../include/task_tree_lua.h"
#include <lualib.h>
#include <lauxlib.h>


int8_t task_tree_lua_init(lua_State* L)
{
    //luaL_dofile(L, "src/task_tree.lua");
    luaL_dostring(L, "task_tree = require(\"src.task_tree\")");
    lua_getglobal(L, "task_tree");
    if(lua_istable(L, -1))
    {
        lua_pushliteral(L, "task_new");
        lua_pushcfunction(L, task_tree_lua_task_new);
        lua_settable(L, -3);

        lua_pushliteral(L, "task_get_name");
        lua_pushcfunction(L, task_tree_lua_task_get_name);
        lua_settable(L, -3);
    }
    else 
    {
        printf("[C] 'lua_init' tried to access a table but it is not a table\n");
    }lua_pop(L, 1);

    return 0;
}

int task_tree_lua_task_new(lua_State* L)
{
    const char* name = lua_tostring(L, 1);
    struct task_t* task = task_tree_task_new(name);
    
    struct task_t** task_ptr = (struct task_t**)lua_newuserdata(L, sizeof(struct task_t*));
    *task_ptr = task; 
    return 1;//return last pushed element
}

int task_tree_lua_task_get_name(lua_State* L)
{
    struct task_t** task_ptr = (struct task_t**)lua_touserdata(L, 1);
    struct task_t* task = *task_ptr;
    lua_pushstring(L, task_tree_task_get_name(task));
    return 1;
}


