#include "Commands.h"

void Commands::open(const std::string& str)
{
    if (file.is_open()) {

        throw std::invalid_argument("A file is already open!");
    } else {

        std::size_t size = str.size();

        if(str[size - 1] != 'n' && str[size - 2] != 'o' && str[size - 3] != 's' && str[size - 4] != 'j')
        {
            throw std::runtime_error("File is not a .json file!");
        }

        this->fileName = str;

        this->file.open(fileName, std::iostream::in | std::ios::app);

        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open a new file");
        } else 
        {
            std::cout << str << " successfully opened!" << std::endl;
        }
        
    }
}

void Commands::help() const
{
    std::cout << "Available commands:\n"
        << "OPEN <fileName>: Load an JSON file\n"
        << "SEARCH_KEY <key>: Prints the values of a given key\n"
        << "CHANGE <path> <value>: Changes the value of the element, given a path to it\n"
        << "ADD <path> <key> <value>: Adds a new element\n"
        << "HELP: Display this help message\n"
        << "EXIT: Exit the program\n"
        << "PRINT: Print the entire file\n"; 
}


void Commands::toLower (std::string& str) {

    for (size_t i = 0; i < str.length(); i++) {

        if(str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] - 'A' + 'a';
        }

    }
}

void Commands::process(const std::string& command)
{
    std::string generalCommand, generalfileName, key, path, newValue, newKey, value;

    std::istringstream iss(command);
    iss >> generalCommand >> generalfileName;

    std::istringstream iss1(command);
    iss1 >> generalCommand >> key;

    std::istringstream iss2(command);
    iss2 >> generalCommand >> path >> newValue;

    std::istringstream iss3(command);
    iss3 >> generalCommand >> path >> newKey >> value;

    toLower(generalCommand);

    if(generalCommand == "open") {
        this->fileName = generalfileName;
        try{
            open(generalfileName);
        } catch(const std::invalid_argument& e) {
            
            std::cout << e.what() << std::endl;

        } catch (const std::runtime_error& e) {

            std::cout << e.what() << std::endl;
        }
    } else if (generalCommand == "print")
    {
        JSONTree js(this->fileName);
        try
        {
            TreeNode* root = js.generateTree();
            js.print(root, TAB_INDEX_START);
        } catch (const std::runtime_error& e)
        {
            std::cout << e.what() << std::endl;
        }
        // TreeNode* root = openTree(this->fileName);
        
    } else if(generalCommand == "search_key")
    {
        JSONTree js(this->fileName);
        TreeNode* root = js.generateTree();
        std::vector<TreeNode* > result;
        js.getElementsByKey(key, root, result);
        js.printElementsByKey(result);
    } else if(generalCommand == "help")
    {
        help();
    } else if(generalCommand == "change")
    {
        JSONTree js(this->fileName);
        TreeNode* root = js.generateTree();

        JSONPath jsp(path, root);
        jsp.changeValue(newValue);

        js.print(root, TAB_INDEX_START);
    } else if(generalCommand == "add")
    { 
        JSONTree js(this->fileName);
        
        TreeNode* root = js.generateTree();

        JSONPath jsp(path, root);
        jsp.addObject(newKey, value);

        js.print(root, TAB_INDEX_START);
    }
}
