#pragma once

#include <string>
#include <iostream>
#include "ValueType.h"

/**
 * @brief Class representing a key-value pair in a JSON object.
 * 
 * The JSONElement class encapsulates a key-value pair within a JSON object.
 */
class JSONElement {
private:

    std::string key;   /**< The key of the key-value pair */
    Value* value;      /**< Pointer to the value (of type Value) associated with the key */

public:
    /**
     * @brief Constructor for JSONElement.
     * 
     * @param k The key for the key-value pair.
     * @param v Pointer to the value (Value) associated with the key.
     */
    JSONElement(const std::string &k, Value *v) : key(k), value(v) {}

    /**
     * @brief Destructor for JSONElement.
     * 
     * Deletes the value associated with the key-value pair.
     */
    ~JSONElement();

    /**
     * @brief Prints the key-value pair.
     */
    void print() const;

    /**
     * @brief Gets the key of the key-value pair.
     * 
     * @return Reference to the key string.
     */
    const std::string& getKey() const;

    /**
     * @brief Gets the value type of the key-value pair.
     * 
     * @return ValueType representing the type of the value associated with the key.
     */
    ValueType getValueType() const;
};
