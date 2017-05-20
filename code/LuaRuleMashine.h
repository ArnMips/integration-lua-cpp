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
    
    //��������� � ������� ����� ��������� Property �������
    Property getPropertyFromStack(lua_State* L);

    // ����� �� Lua-����� ������� � ���������� ������������� �� ��������� Param
    static int l_getParam(lua_State* L);

    //��������� � Lua-������ ��������� � ������������� �����������
    void loadObjectsParam(lua_State* L);
};
