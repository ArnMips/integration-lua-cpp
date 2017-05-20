#pragma once
#pragma optimize("", off) 

#include <string>
#include <vector>

// Класс, ответственный за работу с типом объекта
class ObjType {
public:
    enum Types {
        Lighthouse,
        Rock,
        Underwater_rock,
        Coastline
    };
    ObjType(Types type);
    ObjType(std::string type); ///Внимание, используется поиск и сравнение строк
    ObjType(size_t type);

    static size_t getNumOfTypes();
    Types toEnum() const;
    int toInt() const;
    std::string toString() const;

private:
    Types type_;
    static std::string stringTypes_[];
};

// Структура свойст для отрисовки объекта
class Property {
public:
    Property(ObjType objtype, unsigned int color, char caracter);
    ObjType getObjType() const;
    unsigned int getColor() const;
    char getCaracter() const;
private:
    ObjType objtype;
    unsigned int color;
    char caracter;
};


// ---- Классы объектов ---- 

class Object {
public:
    Object(const ObjType& t, const std::string& n);
    std::string getName() const;

    ObjType getType() const;

private:
    ObjType type_;
    std::string name_;
};

class Lighthouse : public Object {
public:
    Lighthouse(const std::string& n);
    unsigned int getColor() const;
    double getBrightness() const;
    void setColor(const unsigned int c);
    void setBrightness(const double b);

private:
    unsigned int color_;
    double brightness_;
};

class Rock : public Object {
public:
    Rock(const std::string& n);
    double getAltitude() const;
    bool isVolcano() const;
    void setAltitude(const double a);
    void setVolcano(const bool v);

private:
    double altitude_;
    bool isVolcano_;
};

class UnderwaterRock : public Object {
public:
    UnderwaterRock(const std::string& n);
    double getDepth() const;
    void setDepth(const double d);

private:
    double depth_;
};

class Coastline : public Object {
public:
    Coastline(const std::string& n);
    double getLength() const;
    std::string getTypeOfBeach() const;
    void setLength(const double l);
    void setTypeOfBeach(const std::string& t);

private:
    double length_;
    //TODO: Изменить тип типа поверхности на enum?
    std::string typeOfBeach_;
};


//Загрузка объектов из файла
std::vector<Object*> getObjectsFromFile(const std::string& fileName);