#pragma once

#include "JSONTree.h"
#include "JSONPath.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

const unsigned int TAB_INDEX_START = 1;

/**
 * @brief Class representing commands for interacting with JSON data.
 * 
 * The Commands class provides functionality for processing commands and interacting with JSON data.
 */
class Commands {

private:

    std::ifstream file;     /**< Input file stream */
    std::string fileName;   /**< Name of the input file */

public:

    /**
     * @brief Default constructor for Commands.
     */
    Commands() = default;

    /**
     * @brief Converts a string to lowercase.
     * 
     * @param str Reference to the string to be converted.
     */
    void toLower(std::string& str);

    /**
     * @brief Opens a JSON file for processing.
     * 
     * @param str The name of the JSON file to be opened.
     */
    void open(const std::string& str);

    /**
     * @brief Processes a command related to JSON data.
     * 
     * @param command The command to be processed.
     */
    void process(const std::string& command);

    /**
     * @brief Displays help information for available commands.
     */
    void help() const;
};
