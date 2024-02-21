#include "JSONObject.h"

void JSONObject::addElement(const std::string &key, Value *element) {
    elements.push_back(new JSONElement(key, element));
}

void JSONObject::print() const {

    std::cout << "Obj:" << std::endl;

    for (const auto &element: elements) {
        element->print();
}

}

ValueType JSONObject::getType() const {
    return this->type;
}
