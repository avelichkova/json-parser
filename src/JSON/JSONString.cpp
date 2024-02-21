#include "JSONString.h"

JSONString::JSONString(const std::string &val) : value(val) {}

void JSONString::print() const {
    std::cout << "String: " << value << std::endl;
}

ValueType JSONString::getType() const {
    return this->type;
}

