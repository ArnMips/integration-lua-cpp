#include <fstream>

#include "ObjectLoader.h"

ObjectLoader::ObjectLoader(const std::string& fileName) {
	std::ifstream in;
	in.open(fileName);

	std::string objectType;
	std::string objectName;
	double x, y;

	std::vector<std::pair<double, double>> coordinates;
	coordinates.reserve(2);

	while (!in.eof()) {
		Object object;
		in >> objectType >> objectName >> x >> y;
		coordinates.clear();
		coordinates.push_back(std::pair<double, double>(x, y));

		if (objectType != "point") {
			in >> x >> y;
			coordinates.push_back(std::pair<double, double>(x, y));
		}

		object.setType(objectType);
		object.setName(objectName);
		object.setCoordinates(coordinates);

		objects_.push_back(object);
	}

	in.close();
}

std::vector<Object> ObjectLoader::getObjects() const {
	return objects_;
}

