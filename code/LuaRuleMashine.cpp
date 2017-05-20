#include "LuaRuleMashine.h"

#include <iostream>

LuaRuleMashine::LuaRuleMashine(std::string fileName)
    : L_(luaL_newstate()) {
  // open standart libs
    luaL_openlibs(L_); 
  //add function to Lua-script
    lua_pushcfunction(L_, l_getParam); 
    lua_setglobal(L_, "getParam");
  //add table with obj param
    loadObjectsParam(L_);
  //add empty table, with function on property of objects
    lua_newtable(L_);
    lua_setglobal(L_, "Property");
  //do file
    luaL_dofile(L_, fileName.c_str());

 // загружаем таюлицу параметров отрисовки в стек луа
    lua_getglobal(L_, "Property");                      ///stack: Property[]
}

LuaRuleMashine::~LuaRuleMashine() {
    lua_close(L_);
}

Property LuaRuleMashine::getPropery(Object* obj) {
    std::string type = obj->getType().toString();
    lua_rawgeti(L_, L_STACK_TOP_, obj->getType().toInt()); /// stack: 'objType' (имя функции соответствующее типу объекта
    lua_pushlightuserdata(L_, obj);                        /// stack: 'objType',  obj
    lua_pcall(L_, 1, 1, 0);                                /// stack: 'objPropert' (структура параметров отрисовки объекта)
    
    return getPropertyFromStack(L_);
}

Property LuaRuleMashine::getPropertyFromStack(lua_State * L) {
    int type;
    unsigned int color;
    char caracter;                                      /// stack: propertyTable[]

    lua_getfield(L, L_STACK_TOP_, "objtype");           /// stack: propertyTable[], propertyTable.objtype
    type = lua_tointeger(L, L_STACK_TOP_);
    lua_pop(L, 1);                                      /// stack: propertyTable[]
    
    lua_getfield(L, L_STACK_TOP_, "color");            /// stack: propertyTable[], propertyTable.color
    color = lua_tointeger(L, L_STACK_TOP_);
    lua_pop(L, 1);                                     /// stack: propertyTable[]
    
    lua_getfield(L, L_STACK_TOP_, "caracter");        /// stack: propertyTable[], propertyTable.caracter
    caracter = (!lua_isnil(L, L_STACK_TOP_)) 
        ? std::string(lua_tostring(L, L_STACK_TOP_))[0] 
        : '\0';
    lua_pop(L, 1);                                     /// stack: propertyTable[]

    lua_pop(L, 1);                                     /// stack: 
    return Property(ObjType(type), color, caracter);
}

int LuaRuleMashine::l_getParam(lua_State * L) {
    Object* obj = (Object*)lua_touserdata(L, 1);
    const int numOfParam = lua_tonumber(L, 2);

    switch (obj->getType().toEnum()) {
        case ObjType::Lighthouse : {
            const Lighthouse* l = static_cast<const Lighthouse*>(obj);
            switch (numOfParam) {
                case 0: lua_pushinteger(L, l->getColor()); break;
                case 1: lua_pushnumber(L, l->getBrightness()); break;
            }
        } break;

        case ObjType::Rock : {
            const Rock* l = static_cast<const Rock*>(obj);
            switch (numOfParam) {
                case 0: lua_pushnumber(L, l->getAltitude()); break;
                case 1: lua_pushboolean(L, l->isVolcano()); break;
            }
        } break;

        case ObjType::Underwater_rock : {
            const UnderwaterRock* l = static_cast<const UnderwaterRock*>(obj);
            switch (numOfParam) {
                case 0: lua_pushnumber(L, l->getDepth()); break;
            }
        } break;

        case ObjType::Coastline : {
            const Coastline* l = static_cast<const Coastline*>(obj);
            switch (numOfParam) {
                case 0: lua_pushlstring(L, l->getTypeOfBeach().c_str(), l->getTypeOfBeach().size()); break;
                case 1: lua_pushnumber(L, l->getLength()); break;
            }
        } break;
    }

    return 1;
}

void LuaRuleMashine::loadObjectsParam(lua_State * L) {
    const char* objTableName = "Obj";
    const char* paramTableName = "Prm";


    //создает пустую таблицу и помещает в стек (будущая Obj)
    lua_newtable(L);                                                                                                    /// stack: table(obj)

    //Добавляем в таблиц table(obj) n полей
    for (int i(0); i < ObjType::getNumOfTypes(); ++i) {
       
        //Таблица, создаваемая для каждоо типа объекта с его индивидуальными параметрами
        lua_newtable(L);                                                                                               /// stack: table(obj), table(objType)
        
        //Добавляем ID объекта    
        ObjType tmptype(i);
        lua_pushinteger(L, i); /*value*/                                                                                /// stack: table(obj), table(objType),  value
        lua_setfield(L, L_STACK_TOP_-1, "ID");                                                                          /// stack: table(obj), table(objType)

        //Добавляем параметры у каждого объекта 
        lua_newtable(L);                                                                                                /// stack: table(obj), table(objType), table(objPrm)

        switch (tmptype.toEnum()) {
            case ObjType::Lighthouse : {
                lua_pushinteger(L, 0);                                                                                 /// stack: table(obj), table(objType), table(objParam), val,
                lua_setfield(L, L_STACK_TOP_-1, "COLOR");                                                              /// stack: table(obj), table(objType), table(objParam),
                lua_pushinteger(L, 1);                                                                                 /// stack: table(obj), table(objType), table(objParam), val,
                lua_setfield(L, L_STACK_TOP_-1, "BRIGHTNESS");                                                         /// stack: table(obj), table(objType), table(objParam),
            } break;
            case ObjType::Rock : {
                lua_pushinteger(L, 0);
                lua_setfield(L, L_STACK_TOP_-1, "ALTITUDE");
                lua_pushinteger(L, 1);
                lua_setfield(L, L_STACK_TOP_-1, "IS_VOLCANO");
            } break;
            case ObjType::Underwater_rock : {
                lua_pushinteger(L, 0);
                lua_setfield(L, L_STACK_TOP_-1, "DEPTH");
            } break;
            case ObjType::Coastline : {
                lua_pushinteger(L, 0);
                lua_setfield(L, L_STACK_TOP_-1, "LENGTH");
                lua_pushinteger(L, 1);
                lua_setfield(L, L_STACK_TOP_-1, "TYPE_OF_BEACH");
            } break;
        }

        //добавляем таблицу с параметрами Param в таблицу со свойствами property объекта
        lua_setfield(L, L_STACK_TOP_ - 1, paramTableName);                                                               /// stack: table(obj), table(objType),

        //добавляем таблицу  со свойствами property объекта в общую таблицу объектов obj
        lua_setfield(L, L_STACK_TOP_ - 1, tmptype.toString().c_str());                                              /// stack: table(obj), 
    }

    // загружаем таблицу в Lua-скрипт
    lua_setglobal(L, objTableName);
}
