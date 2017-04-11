#pragma once

#include <string>
#include <vector>

class Object{
public:
    //PropertyFields: first - key | second - value
    typedef std::vector<std::pair<std::string, std::string> > PropertyFields;

	void setType(std::string& objectType);
	void setName(std::string& objectName);
	void setCoordinates(const std::vector<std::pair<double, double>>& objectCoordinates);
	void setDrawProperty(const PropertyFields& objectDrawProperty);

	std::string getType() const;
	std::string getName() const;
	std::vector<std::pair<double, double>> getCoordinates() const;
    PropertyFields getDrawProperty() const;

private:
	std::vector<std::pair<double, double>> coordinates_;
	std::string name_;
	std::string type_;
    PropertyFields drawProperty_;
};