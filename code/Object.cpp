#include "Object.h"
#include <fstream>
#include <iostream>

std::string ObjType::stringTypes_[] = { "Lighthouse", "Rock", "Underwater_rock", "Coastline" };

Lighthouse::Lighthouse(const std::string & n)
    : Object(ObjType(ObjType::Lighthouse), n) {
}

unsigned int Lighthouse::getColor() const {
    return color_;
}

double Lighthouse::getBrightness() const {
    return brightness_;
}

void Lighthouse::setColor(const unsigned int c) {
    color_ = c;
}

void Lighthouse::setBrightness(const double b) {
    brightness_ = b;
}

Rock::Rock(const std::string & n)
    : Object(ObjType(ObjType::Rock), n) {
}

double Rock::getAltitude() const {
    return altitude_;
}

bool Rock::isVolcano() const {
    return isVolcano_;
}

void Rock::setAltitude(const double a) {
    altitude_ = a;
}

void Rock::setVolcano(const bool v) {
    isVolcano_ = v;
}

UnderwaterRock::UnderwaterRock(const std::string & n)
    : Object(ObjType(ObjType::Underwater_rock), n) {
}

double UnderwaterRock::getDepth() const {
    return depth_;
}

void UnderwaterRock::setDepth(const double d) {
    depth_ = d;
}

Coastline::Coastline(const std::string & n)
    : Object(ObjType(ObjType::Coastline), n) {
}

double Coastline::getLength() const {
    return length_;
}

void Coastline::setLength(const double l) {
    length_ = l;
}

void Coastline::setTypeOfBeach(const std::string & t) {
    typeOfBeach_ = t;
}

std::string Coastline::getTypeOfBeach() const {
    return typeOfBeach_;
}

Object::Object(const ObjType & t, const std::string & n)
    : type_(t), name_(n) 
{
}

std::string Object::getName() const {
    return name_;
}

ObjType Object::getType() const {
    return type_;
}

std::vector<Object*> getObjectsFromFile(const std::string & fileName) {
    std::ifstream in;
    in.open(fileName);
    std::vector<Object*> objects;
    std::string objectType, objectName;

    while (!in.eof()) {
        in >> objectType >> objectName;

        if (objectType == "lighthouse") {
            unsigned int color;
            double brightness;
            in >> std::hex >> color >> std::dec >> brightness;
            Lighthouse* t = new Lighthouse(objectName);
            t->setColor(color);
            t->setBrightness(brightness);
            objects.push_back(t);

        } else if (objectType == "rock") {
            double atitude;
            bool volcano;
            in >> atitude >> volcano;
            Rock* t = new Rock(objectName);
            t->setAltitude(atitude);
            t->setVolcano(volcano);
            objects.push_back(t);

        } else if (objectType == "underwater_rock") {
            double depth;
            in >> depth;
            UnderwaterRock* t = new UnderwaterRock(objectName);
            t->setDepth(depth);
            objects.push_back(t);

        } else if (objectType == "coastline") {
            double length;
            std::string typeOfBeach;
            in >> length >> typeOfBeach;
            Coastline* t = new Coastline(objectName);
            t->setLength(length);
            t->setTypeOfBeach(typeOfBeach);
            objects.push_back(t);
        }
    }
    in.close();

    return objects;
}

Property::Property(ObjType objtype, unsigned int color, char caracter)
     : objtype(objtype), color(color), caracter(caracter)
{
}

ObjType Property::getObjType() const {
    return objtype;
}

unsigned int Property::getColor() const {
    return color;
}

char Property::getCaracter() const {
    return caracter;
}

ObjType::ObjType(Types type)
: type_(type)
{
}

ObjType::ObjType(std::string type) {    
    const size_t numOfTypes = sizeof(stringTypes_) / sizeof(std::string);
    for (size_t i(0); i < numOfTypes; ++i) {
        if (type == stringTypes_[i]) {
            switch (i) {
                case 0:
                    type_ = Lighthouse;
                    break;
                case 1:
                    type_ = Rock;
                    break;
                case 2:
                    type_ = Underwater_rock;
                    break;
                case 3:
                    type_ = Coastline;
                    break;
            }
            break;
        }
        //Если не найдено соответствие типа в строковом представлении
        if (i == numOfTypes-1)
            throw "Error: ObjType::ObjType(std::string type)\n type does not exists";
    }
}

ObjType::ObjType(size_t type) {
    switch (type) {
        case 0:
            type_ = Lighthouse;
            break;
        case 1:
            type_ = Rock;
            break;
        case 2:
            type_ = Underwater_rock;
            break;
        case 3:
            type_ = Coastline;
            break;
        default:
            throw "Error: ObjType::ObjType(std::string type)\n type does not exists";
    }
}

size_t ObjType::getNumOfTypes() {
    return sizeof(stringTypes_) / sizeof(std::string);
}

ObjType::Types ObjType::toEnum() const {
    return type_;
}

int ObjType::toInt() const {
    return static_cast<int>(type_);
}

std::string ObjType::toString() const {
    if (type_ > sizeof(stringTypes_) / sizeof(std::string)) {
        throw "Error:  ObjType::toString() \ntype_ size > stringTypes_ size";
    }
    return stringTypes_[type_];
}
