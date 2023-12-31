//بسم الله الرحمن الرحيم

#include <stdlib.h>
#include <lua5.4/lua.h>

//binds the c functions to lua
//
//Allah knows if I'm gonna use another function or just this one
int8_t task_tree_lua_init(lua_State* L);
int task_tree_lua_task_new(lua_State* L);
int task_tree_lua_task_get_name(lua_State* L);

