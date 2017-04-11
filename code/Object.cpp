#include "Object.h"

void Object::setType(std::string& objectType) {
	type_ = objectType;
}

void Object::setName(std::string& objectName) {
	name_ = objectName;
}

void Object::setCoordinates(const std::vector<std::pair<double, double>>& objectCoordinates) {
	coordinates_ = objectCoordinates;
}

void Object::setDrawProperty(const PropertyFields& objectDrawProperty) {
	drawProperty_ = objectDrawProperty;
}

std::string Object::getType() const {
	return type_;
}

std::string Object::getName() const {
	return name_;
}

std::vector<std::pair<double, double>> Object::getCoordinates() const {
	return coordinates_;
}

std::vector<std::pair<std::string, std::string>> Object::getDrawProperty() const {
	return drawProperty_;
}