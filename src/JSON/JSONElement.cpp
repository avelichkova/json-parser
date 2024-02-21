#include "JSONElement.h"

const std::string& JSONElement::getKey() const {

    return key;

}

ValueType JSONElement::getValueType() const {
    return value->getType();
}

void JSONElement::print() const {
    std::cout << key << ": ";
    value->print();
}

JSONElement::~JSONElement() {
    delete[] this->value;
}