#pragma once
#pragma optimize("", off) 

#include <lua.hpp>
#include <string>
#include <vector>

#include "Object.h"

class LuaRuleMashine {
public:
    LuaRuleMashine(std::string fileName);
	~LuaRuleMashine();
	
    Property getPropery(Object* obj);

private:
	lua_State *L_;
	const int L_STACK_TOP_ = -1;
	const int L_STACK_DOWN_ = 1;
    
    //Извлекает с вершины стека структуру Property объекта
    Property getPropertyFromStack(lua_State* L);

    // Берет из Lua-стека таблицу и возвращает эквивалентную ей структуру Param
    static int l_getParam(lua_State* L);

    //Добавляет в Lua-скрипт структуру с определенными константами
    void loadObjectsParam(lua_State* L);
};
