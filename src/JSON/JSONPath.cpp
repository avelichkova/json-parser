#include "JSONPath.h"

JSONPath::JSONPath(std::string path, TreeNode* root) : path(path), root(root){}

void JSONPath::changeValue(std::string& path, TreeNode*& root, std::string& newValue, std::string currentKey)
{
    if(!root) 
    {
        std::cout << "No such path";
        return;
    }

    if(path.empty())
    {
        root->children[0]->str = newValue;
        return;
    }

    for (std::size_t i = 0; i < root->children.size(); i++)
    {
        if(root->children[i]->str == currentKey)
        {
            if(path.find('/') != std::string::npos)
            {
                    std::size_t pos = this->path.find('/');
                    std::string currentKey = this->path.substr(0, pos);
                    this->path.erase(0, pos + 1);
                    changeValue(this->path, root->children[i], newValue, currentKey);
                    
            } else 
            {
                    std::string key = this->path;
                    if(root->children[i]->str == this->path)
                    {
                        std::string newPath = "";
                        changeValue(newPath, root->children[i], newValue, key);
                    }

                    changeValue(this->path, root->children[i], newValue, key);
                    
            }
        } else if(root->children[i]->str == "{}" || root->children[i]->str == "[]")
        {
            changeValue(path, root->children[i], newValue, currentKey);
        }
    }
}

void JSONPath::changeValue(std::string newValue)
{
    if(path.find('/') != std::string::npos)
    {
        std::size_t pos = this->path.find('/');
        std::string currentKey = this->path.substr(0, pos);
        this->path.erase(0, pos + 1);

        changeValue(this->path, this->root, newValue, currentKey);
    } else 
    {
        changeValue(this->path, this->root, newValue, this->path);
    }
    
}

void JSONPath::addObject(std::string& path, TreeNode*& root, std::string key, std::string value, std::string currentKey)
{
    if(!root) 
    {
        return;
    }

    if(path.empty() && root->str == "{}")
    {
        TreeNode* newKey = new TreeNode(key);
        newKey->parent = root;
        newKey->isKey = true;
        root->children.push_back(newKey);

        TreeNode* newValue = new TreeNode(value);
        newValue->parent = newKey;
        newKey->children.push_back(newValue);
        return;
    }

    for (std::size_t i = 0; i < root->children.size(); i++)
    {
        if(root->children[i]->str == currentKey)
        {
            if(path.find('/') != std::string::npos)
            {
                    std::size_t pos = this->path.find('/');
                    std::string currentKey = this->path.substr(0, pos);
                    this->path.erase(0, pos + 1);
                    addObject(this->path, root->children[i], key, value, currentKey);
                    
            } else 
            {
                    std::string currK = this->path;
                    if(root->children[i]->str == this->path)
                    {
                        std::string newPath = "";
                        addObject(newPath, root->children[i], key, value, currK);
                    }

                    addObject(this->path, root->children[i], key, value, currK);
                    
            }
        } else if(root->children[i]->str == "{}" || root->children[i]->str == "[]")
        {
            addObject(path, root->children[i], key, value, currentKey);
        }
    }
}

void JSONPath::addObject(std::string key, std::string value)
{
    if(path.find('/') != std::string::npos)
    {
        std::size_t pos = this->path.find('/');
        std::string currentKey = this->path.substr(0, pos);
        this->path.erase(0, pos + 1);

        addObject(this->path, this->root, key, value, currentKey);
    } else 
    {
        addObject(this->path, this->root, key, value, this->path);
    }
}

// void JSONPath::deleteElement(std::string& path, TreeNode* root, std::string element, std::string currentKey)
// {
//     if(!root)
//     {
//          return;
//     }
//     if(path.empty() && root->str == element)
//     {
//         delete[] root;
//     }
//     for (std::size_t i = 0; i < root->children.size(); i++)
//     {
//         if(root->children[i]->str == currentKey)
//         {
//             if(path.find('/') != std::string::npos)
//             {
//                     std::size_t pos = this->path.find('/');
//                     std::string currentKey = this->path.substr(0, pos);
//                     this->path.erase(0, pos + 1);
//                     deleteElement(this->path, root->children[i], element, currentKey);
                    
//             } else 
//             {
//                     std::string currK = this->path;
//                     if(root->children[i]->str == this->path)
//                     {
//                         std::string newPath = "";
//                         deleteElement(newPath, root->children[i], element, currK);
//                     }

//                     deleteElement(this->path, root->children[i], element, currK);
                    
//             }
//         } else if(root->children[i]->str == "{}" || root->children[i]->str == "[]")
//         {
//             deleteElement(path, root->children[i], element, currentKey);
//         }
//     }
// }

// void JSONPath::deleteElement(std::string element)
// {
//     if(path.find('/') != std::string::npos)
//     {
//         std::size_t pos = this->path.find('/');
//         std::string currentKey = this->path.substr(0, pos);
//         this->path.erase(0, pos + 1);

//         changeValue(this->path, this->root, element, currentKey);
//     } else 
//     {
//         changeValue(this->path, this->root, element, this->path);
//     }
// }