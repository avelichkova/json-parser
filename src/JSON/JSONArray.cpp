#include "JSONArray.h"

void JSONArray::addElement(Value* element) {
    elements.push_back(element);
}

void JSONArray::print() const{
    std::cout << "Array:" << std::endl;
    for (const auto& element : elements) {
        element->print();
    }
}

ValueType JSONArray::getType() const {
    return this->type;
}
