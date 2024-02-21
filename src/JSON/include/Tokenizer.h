#pragma once

#include "TokenType.h"
#include <string>
#include <iostream>
#include <fstream>

/**
 * @brief Struct representing a token in a JSON document.
 * 
 * This struct holds information about a token, including its type and value.
 */
struct Token {

    TokenType type;     /**< Type of the token (e.g., LBrace, String, Number) */
    std::string value;  /**< Value associated with the token (for String and Number tokens) */

};

/**
 * @brief Class for tokenizing a JSON document.
 * 
 * This class provides functionality to tokenize a JSON document, extracting
 * individual tokens for further processing.
 */
class JSONTokenizer {

private:

    std::ifstream file; /**< Input file stream for reading JSON content */

    /**
     * @brief Private helper function to read a null literal from the file.
     * 
     * @param file Input file stream.
     * @return The read null literal as a string.
     */
    std::string readNull(std::ifstream& file);

    /**
     * @brief Private helper function to read a true literal from the file.
     * 
     * @param file Input file stream.
     * @return The read true literal as a string.
     */
    std::string readTrue(std::ifstream& file);

    /**
     * @brief Private helper function to read a false literal from the file.
     * 
     * @param file Input file stream.
     * @return The read false literal as a string.
     */
    std::string readFalse(std::ifstream& file);

    /**
     * @brief Private helper function to read a string from the file.
     * 
     * @param file Input file stream.
     * @return The read string.
     */
    std::string readString(std::ifstream& file);

    /**
     * @brief Private helper function to read a number from the file.
     * 
     * @param file Input file stream.
     * @return The read number as a string.
     */
    std::string readNumber(std::ifstream& file);

public:
    /**
     * @brief Default constructor for JSONTokenizer.
     */
    JSONTokenizer() = default;

    /**
     * @brief Constructor for JSONTokenizer with a specified filename.
     * 
     * @param filename Name of the JSON file to be tokenized.
     */
    JSONTokenizer(const std::string &filename);

    /**
     * @brief Destructor for JSONTokenizer.
     * 
     * Closes the file if it is open.
     */
    ~JSONTokenizer()
    {
        if (file.is_open()) {
            file.close();
        }
    }

    /**
     * @brief Get the next token from the JSON document.
     * 
     * @return The next token in the document.
     */
    Token getNextToken();

    /**
     * @brief Close the JSON file.
     * 
     * Closes the file associated with the JSONTokenizer instance.
     */
    void closeFile();
};
