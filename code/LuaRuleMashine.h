#pragma once
#include <lua.hpp>
#include <string>
#include <vector>
#include "Object.h"

class LuaRuleMashine {
public:
    LuaRuleMashine(std::string fileName);
	~LuaRuleMashine();
	
    Object::PropertyFields getPropery(const Object& obj);

private:
	lua_State *L_;
    const char* L_FIELDS_TYPES_ = "fieldTypes";
	const int L_STACK_TOP_ = -1;
	const int L_STACK_DOWN_ = 1;
    std::vector<std::string> field_;

    void initVectField_();
};
