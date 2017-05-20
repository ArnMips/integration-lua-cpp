#include <iostream>
#include <vector>
#include <string>

#include "LuaRuleMashine.h"
#include "Object.h"

using namespace std;

void printProperty(const string& objName, const Property& property);
void cleanObjects(vector<Object*> obj);

int main() {
    LuaRuleMashine lrm("DrawRule.lua");
    vector<Object*> obj = getObjectsFromFile("objects.txt");

    for (auto it : obj) {
        Property objProperty = lrm.getPropery(it);
        
        printProperty(it->getName(), objProperty);
    }

    cleanObjects(obj);
    return 0;
}

void printProperty(const string & objName, const Property & property) {
    cout << "\n----- " << objName
        << "\ntype: " << property.getObjType().toString()
        << "\ncolor: " << hex << property.getColor() << dec
        << "\ncaracter: " << property.getCaracter()
        << endl;
}

void cleanObjects(vector<Object*> obj) {
    for (auto& it : obj) {
        delete it;
    }
}