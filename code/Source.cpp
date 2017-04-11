#include "LuaRuleMashine.h"
#include "ObjectLoader.h"

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ObjectLoader loader("..\\resourse\\objects.txt");
    std::vector<Object> objects = loader.getObjects();

    LuaRuleMashine luaRuleMashine("..\\resourse\\DrawRule.lua");

    for (auto& it : objects) {
        it.setDrawProperty(luaRuleMashine.getPropery(it));
    }
    
    // - OUT - //
    for (auto& it : objects) {
        cout << it.getName() << " " << it.getType() << "\n";
        for (auto& itc : it.getCoordinates()) {
            cout << itc.first << " " << itc.second << "\n";
        }
        for (int i(0); i < it.getDrawProperty().size(); ++i) {
            cout << it.getDrawProperty()[i].first << ": " << it.getDrawProperty()[i].second << "\n";
        }
        cout << endl;
    }

    system("PAUSE");
    return 0;
}