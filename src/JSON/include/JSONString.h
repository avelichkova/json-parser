#pragma once

#include <vector>
#include <string>
#include "JSONElement.h"

/**
 * @brief Class representing a JSON string value.
 * 
 * The JSONString class is a concrete implementation of the Value class,
 * representing a string literal in a JSON document.
 */
class JSONString : public Value {
private:

    std::string value;      /**< String value of the JSON string literal */
    ValueType type;         /**< Type of the JSON string literal (StringLiteral) */

public:
    /**
     * @brief Constructor for JSONString.
     * 
     * @param val The string value to be stored in the JSONString object.
     */
    explicit JSONString(const std::string &val);

    /**
     * @brief Prints the JSON string value.
     * 
     * Implements the print function declared in the base Value class.
     */
    void print() const override;

    /**
     * @brief Gets the type of the JSON string value.
     * 
     * Implements the getType function declared in the base Value class.
     * 
     * @return ValueType representing the type of the JSON string value (StringLiteral).
     */
    ValueType getType() const override;

    /**
     * @brief Virtual destructor for JSONString.
     * 
     * Ensures proper destruction of derived classes when using polymorphism.
     */
    virtual ~JSONString() = default;
};
