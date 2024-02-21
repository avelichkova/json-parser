#pragma once

#include "ValueType.h"
#include "JSONElement.h"
#include <vector>

/**
 * @brief Class representing a JSON object.
 * 
 * The JSONObject class is a concrete implementation of the Value class,
 * representing a JSON object in a JSON document.
 */
class JSONObject : public Value {
private:

    std::vector<JSONElement *> elements; /**< Vector of JSONElement pointers representing key-value pairs in the object */
    ValueType type;                       /**< Type of the JSON object (Obj) */

public:
    /**
     * @brief Adds a key-value pair to the JSON object.
     * 
     * @param key The key for the new element.
     * @param element Pointer to the value (JSONElement) associated with the key.
     */
    void addElement(const std::string &key, Value *element);

    /**
     * @brief Prints the JSON object.
     * 
     * Implements the print function declared in the base Value class.
     */
    void print() const override;

    /**
     * @brief Gets the type of the JSON object.
     * 
     * Implements the getType function declared in the base Value class.
     * 
     * @return ValueType representing the type of the JSON object (Obj).
     */
    ValueType getType() const override;

    /**
     * @brief Virtual destructor for JSONObject.
     * 
     * Ensures proper destruction of derived classes when using polymorphism.
     */
    virtual ~JSONObject() = default;
};
