#pragma once
#include <vector>

/**
 * @brief Enum representing different types of values.
 * 
 * This enum defines three possible types for values: StringLiteral, Obj, and Array.
 */
enum ValueType {
    StringLiteral, Obj, Array
};

/**
 * @brief Abstract base class for representing values.
 * 
 * This class serves as the base class for various types of values. It declares
 * pure virtual functions for printing the value and retrieving its type.
 */
class Value {

public:
    /**
     * @brief Virtual destructor for the Value class.
     * 
     * Ensures proper destruction of derived classes when using polymorphism.
     */
    virtual ~Value() = default;

    /**
     * @brief Pure virtual function to print the value.
     * 
     * Subclasses must implement this function to provide a way to print the
     * specific type of value.
     */
    virtual void print() const = 0;

    /**
     * @brief Pure virtual function to get the type of the value.
     * 
     * Subclasses must implement this function to return the ValueType of the
     * specific type of value.
     * 
     * @return ValueType representing the type of the value.
     */
    virtual ValueType getType() const = 0;
};
