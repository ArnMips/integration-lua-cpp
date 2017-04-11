#include "LuaRuleMashine.h"

LuaRuleMashine::LuaRuleMashine(std::string fileName)
    : L_(luaL_newstate()) {
    luaL_openlibs(L_);
    luaL_dofile(L_, fileName.c_str());
    initVectField_();
}

LuaRuleMashine::~LuaRuleMashine() {
    lua_close(L_);
}

Object::PropertyFields LuaRuleMashine::getPropery(const Object & obj) {
    Object::PropertyFields drawProperty(field_.size());

    //TODO: Как-то оптимизировать для различного числа полей параметров (lable, color, ets...)
    //TODO: Что делать, если не будет найдено соответствие ? ;
    //TODO: Добавить обработку ошибок

    for (size_t i(0); i < field_.size(); ++i) {
        lua_getglobal(L_, obj.getName().c_str());			            /// stack: table
        lua_getfield(L_, L_STACK_TOP_, field_[i].c_str());			    /// stack: table.key
        drawProperty[i] = { field_[i], lua_tostring(L_, L_STACK_TOP_) };
        lua_pop(L_, L_STACK_TOP_);							            /// stack: 'empty'
    }
    return drawProperty;
}

void LuaRuleMashine::initVectField_() {
    //TODO: Как это можно реализовать без лишних удалений/добавлений в стек таблицы
    lua_getglobal(L_, L_FIELDS_TYPES_);                                   ///stack: table    
    const size_t numOfFields = luaL_len(L_, L_STACK_TOP_);        
    lua_pop(L_, 1);                                                      ///stack: 

    for (int i(1); i <= numOfFields; ++i) {
        lua_getglobal(L_, L_FIELDS_TYPES_);                               ///stack: table 
        lua_rawgeti(L_, L_STACK_TOP_, i);                                 ///stack: table[i] 
        std::string nameField = lua_tostring(L_, L_STACK_TOP_);
        field_.push_back(nameField);                        
        lua_pop(L_, 1);                                                  ///stack: 
    }
}
