#pragma once

#include "ValueType.h"
#include "JSONObject.h"

/**
 * @brief Class representing a JSON array.
 * 
 * The JSONArray class is a concrete implementation of the Value class,
 * representing a JSON array in a JSON document.
 */
class JSONArray : public Value {
private:
    
    std::vector<Value*> elements; /**< Vector of Value pointers representing elements in the array */
    ValueType type;               /**< Type of the JSON array (Array) */

public:
    /**
     * @brief Adds an element to the JSON array.
     * 
     * @param element Pointer to the value (Value) to be added to the array.
     */
    void addElement(Value* element);

    /**
     * @brief Prints the JSON array.
     * 
     * Implements the print function declared in the base Value class.
     */
    void print() const override;

    /**
     * @brief Gets the type of the JSON array.
     * 
     * Implements the getType function declared in the base Value class.
     * 
     * @return ValueType representing the type of the JSON array (Array).
     */
    ValueType getType() const override;

    /**
     * @brief Virtual destructor for JSONArray.
     * 
     * Ensures proper destruction of derived classes when using polymorphism.
     */
    virtual ~JSONArray() = default;
};
