#pragma once

#include <string>
#include <vector>

#include "Object.h"

class ObjectLoader {
public:
	ObjectLoader(const std::string& fileName);
    std::vector<Object> getObjects() const;

private:
	std::vector<Object> objects_;
};
