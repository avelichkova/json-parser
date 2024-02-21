#pragma once

#include "Tokenizer.h"
#include "JSONObject.h"
#include "JSONString.h"
#include "JSONArray.h"
#include <fstream>
#include <vector>
#include <stack>
#include <queue>

/**
 * @brief Enum representing different data types within the JSONTree structure.
 * 
 * This enum defines various data types that can be associated with nodes in the JSONTree,
 * including Field, ObjectType, Arr, Key, and SpecialSymb.
 */
enum class dataType {
    Field,         /**< Field data type */
    ObjectType,    /**< Object type data type */
    Arr,           /**< Array data type */
    Key,           /**< Key data type */
    SpecialSymb    /**< Special symbol data type */
};

/**
 * @brief Struct representing a node in the JSONTree structure.
 * 
 * The TreeNode struct represents a node in the JSONTree, containing information
 * about a JSON entity, its associated value type, and its children nodes.
 */
struct TreeNode {
    std::string str;           /**< String representation of the JSON entity */
    Value* type;               /**< Pointer to the associated value type (Value class) */
    bool isKey = false;        /**< Flag indicating whether the node is a key in a key-value pair */
    std::vector<TreeNode *> children; /**< Vector of child nodes */
    TreeNode* parent = nullptr; /**< Pointer to the parent node */

    /**
     * @brief Constructor for TreeNode.
     * 
     * @param str String representation of the JSON entity.
     * @param type Pointer to the associated value type.
     * @param children Vector of child nodes.
     * @param parent Pointer to the parent node.
     */
    TreeNode(std::string str, Value* type = nullptr, std::vector<TreeNode *> children = std::vector<TreeNode *>(), TreeNode* parent = nullptr);

    /**
     * @brief Destructor for TreeNode.
     */
    ~TreeNode();
};

/**
 * @brief Class representing a JSONTree for parsing and storing JSON structures.
 * 
 * The JSONTree class provides functionality for generating, manipulating, and printing a tree
 * structure that represents the hierarchy of JSON entities in a JSON document.
 */
class JSONTree {
private:

    JSONTokenizer tokenizer; /**< Tokenizer for reading JSON content */

    TreeNode* root;          /**< Pointer to the root node of the JSONTree */

    /**
     * @brief Recursive helper function for generating the tree structure.
     * 
     * @param node Reference to the current node in the recursive process.
     * @param parserStack Stack of tokens and data types used during parsing.
     * @param token Current token being processed.
     */
    void generateTree(TreeNode*& node, std::stack<std::pair<Token, dataType>>& parserStack, Token token);

    /**
     * @brief Recursive helper function for copying a tree structure.
     * 
     * @param copy Pointer to the root of the tree to be copied.
     * @return Pointer to the root of the copied tree.
     */
    TreeNode* copy(TreeNode* copy);

    /**
     * @brief Recursive helper function for deallocating tree nodes.
     * 
     * @param root Pointer to the root node of the tree to be deallocated.
     */
    void deallocate(TreeNode* root);

    /**
     * @brief Helper function for creating indentation based on the level of the tree node.
     * 
     * @param d Level of the tree node in the hierarchy.
     * @return String representing the indentation.
     */
    std::string distance(unsigned int d);

public:
    /**
     * @brief Default constructor for JSONTree.
     */
    JSONTree();

    /**
     * @brief Constructor for JSONTree with a specified filename.
     * 
     * @param filename Name of the JSON file to be parsed and represented as a tree.
     */
    JSONTree(const std::string &filename);

    /**
     * @brief Copy constructor for JSONTree.
     * 
     * @param other Reference to another JSONTree object to be copied.
     */
    JSONTree(const JSONTree& other);

    /**
     * @brief Copy assignment operator for JSONTree.
     * 
     * @param other Reference to another JSONTree object to be copied.
     * @return Reference to the modified JSONTree object.
     */
    JSONTree& operator=(const JSONTree& other);

    /**
     * @brief Generates the tree structure by parsing the JSON document.
     * 
     * @return Pointer to the root node of the generated tree.
     */
    TreeNode* generateTree();

    /**
     * @brief Prints the JSONTree structure recursively.
     * 
     * @param root Pointer to the root node of the tree.
     * @param tab Number of tabs for indentation.
     */
    void print(TreeNode* root, unsigned int tab);

    /**
     * @brief Retrieves all nodes with a specific key from the JSONTree.
     * 
     * @param key The key to search for in the JSONTree.
     * @param root Pointer to the root node of the tree.
     * @param v Vector to store the found nodes.
     */
    void getElementsByKey(const std::string key, TreeNode* root, std::vector<TreeNode*>& v) const;

    /**
     * @brief Prints all nodes with a specific key from the JSONTree.
     * 
     * @param v Vector containing the nodes with the specified key.
     */
    void printElementsByKey(std::vector<TreeNode*>& v);

    /**
     * @brief Writes the JSONTree structure to a file.
     * 
     * @param root Pointer to the root node of the tree.
     * @param tab Number of tabs for indentation.
     * @param filename Name of the file to write the JSONTree structure.
     */
    void writeToFile(TreeNode* root, unsigned int tab, std::string filename);

    /**
     * @brief Destructor for JSONTree.
     * 
     * Deallocates memory used by the JSONTree.
     */
    ~JSONTree();
};
