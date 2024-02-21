#pragma once
#include "JSONTree.h"

/**
 * @brief Class representing a JSON path for manipulation of a JSONTree.
 * 
 * The JSONPath class provides functionality for modifying the values
 * and structure of a JSONTree based on a specified path.
 */
class JSONPath
{
private:
    std::string path;   /**< The JSON path string */
    TreeNode* root;     /**< Pointer to the root node of the associated JSONTree */

    /**
     * @brief Private helper function to change the value at a specified path.
     * 
     * @param path Reference to the path string.
     * @param root Reference to the root node of the JSONTree.
     * @param newValue Reference to the new value to be set.
     * @param currentKey The current key being processed in the path.
     */
    void changeValue(std::string& path, TreeNode*& root, std::string& newValue, std::string currentKey);

    /**
     * @brief Private helper function to add an object at a specified path.
     * 
     * @param path Reference to the path string.
     * @param root Reference to the root node of the JSONTree.
     * @param key The key of the new object to be added.
     * @param value The value of the new object to be added.
     * @param currentKey The current key being processed in the path.
     */
    void addObject(std::string& path, TreeNode*& root, std::string key, std::string value, std::string currentKey);

    /**
     * @brief Private helper function to delete an element at a specified path.
     * 
     * @param path Reference to the path string.
     * @param root Reference to the root node of the JSONTree.
     * @param element The element to be deleted.
     * @param currentKey The current key being processed in the path.
     */
    void deleteElement(std::string& path, TreeNode* root, std::string element, std::string currentKey);

public:
    /**
     * @brief Constructor for JSONPath.
     * 
     * @param path The JSON path string.
     * @param root Pointer to the root node of the associated JSONTree.
     */
    JSONPath(std::string path, TreeNode* root);

    /**
     * @brief Changes the value at the specified path.
     * 
     * @param newValue The new value to be set.
     */
    void changeValue(std::string newValue);

    /**
     * @brief Adds an object at the specified path.
     * 
     * @param key The key of the new object to be added.
     * @param value The value of the new object to be added.
     */
    void addObject(std::string key, std::string value);

    /**
     * @brief Deletes an element at the specified path.
     * 
     * @param element The element to be deleted.
     */
    void deleteElement(std::string element);
};
