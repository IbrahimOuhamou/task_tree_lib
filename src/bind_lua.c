//in the name of Allah
//la ilaha illa Allah mohammed rassoul Allah


#include "../include/task_t.h"
#include "../include/tlist.h"
#include "../include/bind_lua.h"

//return 0 on success and -1 on failure
uint8_t task_tree_lua_init(lua_State *L)
{
    luaL_dostring(L, "task_tree = {}");
    lua_getglobal(L, "task_tree")
}


