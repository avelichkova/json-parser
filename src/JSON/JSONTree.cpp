#include "JSONTree.h"

TreeNode::~TreeNode()
{
    delete[] this->type;

    for (std::size_t i = 0; i < this->children.size(); i++)
    {
        delete this->children[i];
    }
    

    delete[] this->parent;
}

TreeNode::TreeNode(std::string str, Value* type, std::vector<TreeNode *> children, TreeNode* parent)
        : str(str), type(type), children(children), parent(parent) {}

JSONTree::JSONTree(const std::string &filename) : tokenizer(filename) {}

// JSONTree::JSONTree(const JSONTree& other) : root(this->copy(other.root)){}



JSONTree::~JSONTree()
{
    this->deallocate(this->root);
}

JSONTree::JSONTree() : root(nullptr){}

JSONTree& JSONTree::operator=(const JSONTree& other) 
{
    if (&other != this)
    {
        this->deallocate(this->root);
        this->root = this->copy(other.root);
    }

    return *this;
}

TreeNode* JSONTree::copy(TreeNode* copy)
{
    if(!copy) return copy;

    return new TreeNode(copy->str, copy->type, copy->children, copy->parent);
}

void JSONTree::deallocate(TreeNode* root)
{
    if (!root)
    {
        return;
    }

    for (std::size_t i = 0; i < root->children.size(); ++i)
    {
        deallocate(root->children[i]);
    }

    delete root->parent;
    delete root;
}
void JSONTree::generateTree(TreeNode*& node, std::stack<std::pair<Token, dataType> > &parserStack, Token token) {

    while(!parserStack.empty())
    {
        switch (token.type) {
            case TokenType::LBrace: 
            {
                Value* newObject = new JSONObject();

                if (!node) 
                {
                    node = new TreeNode("{}");
                    node->type = newObject;
                    node->parent = nullptr;
                    token = tokenizer.getNextToken();
                    generateTree(node, parserStack, token);
                    break;
                } else {
                    TreeNode* newNode = new TreeNode("{}");
                    newNode->type = newObject;
                    newNode->parent = node;
                    parserStack.push({token, dataType::SpecialSymb});
                    node->children.push_back(newNode);
                    token = tokenizer.getNextToken();
                    generateTree(newNode, parserStack, token);
                    break;
                }
            }
            case TokenType::RBrace : 
            {
                // JSONObject* currObj = new JSONObject();

                while (!parserStack.empty() && parserStack.top().first.type != TokenType::LBrace) 
                {
                    parserStack.pop();
                    if (parserStack.empty()) 
                    {
                        throw std::runtime_error("Error: Invalid JSON format.");
                    }
                }
                if(parserStack.top().first.type == TokenType::LBrace)
                {
                    parserStack.pop();//removing from the stack and the '{' token
                }

                if(parserStack.empty() && node->parent == nullptr)
                {
                    return;
                } else if(parserStack.top().second == dataType::Key)
                {
                    token = tokenizer.getNextToken();
                    generateTree(node->parent->parent, parserStack, token);
                    break;
                } else if(parserStack.top().first.type == TokenType::LBracket)
                {
                    token = tokenizer.getNextToken();
                    generateTree(node->parent, parserStack, token);
                    break;
                }
            }
            case TokenType::LBracket : 
            {
                if (!node) 
                {
                    throw std::runtime_error("Error: Invalid JSON format.");

                } else {

                    TreeNode* newNode = new TreeNode("[]");
                    parserStack.push({token, dataType::SpecialSymb});
                    newNode->parent = node;
                    Value* currArr = new JSONArray();
                    newNode->type = currArr;
                    node->children.push_back(newNode);
                    generateTree(newNode, parserStack, tokenizer.getNextToken());
                    break;
                }
                
            }
            case TokenType::RBracket : 
            {
                // JSONArray *currArr = new JSONArray();

                if (parserStack.empty()) {
                    throw std::runtime_error("Error: Invalid JSON format.");
                }

                while (!parserStack.empty() && parserStack.top().first.type != TokenType::LBracket) {
                    parserStack.pop();
                    if (parserStack.empty()) {
                        throw std::runtime_error("Error: Invalid JSON format.");
                    }
                }

                parserStack.pop(); // removing the "[" token
                if(parserStack.top().second == dataType::Key)
                {
                    generateTree(node->parent->parent, parserStack, tokenizer.getNextToken());
                    break;
                } else if(parserStack.top().second == dataType::SpecialSymb && parserStack.top().first.type == TokenType::LBracket)
                {
                    generateTree(node->parent, parserStack, tokenizer.getNextToken());
                    break;
                } else {
                    throw std::runtime_error("Error: Invalid JSON format.");
                }
                
            }
            case TokenType::String : 
            {
                Token t = tokenizer.getNextToken();
                if (t.type == TokenType::Colon) 
                {
                    
                    TreeNode* newNode = new TreeNode(token.value);
                    parserStack.push({token, dataType::Key});
                    newNode->parent = node;
                    newNode->isKey = true;
                    node->children.push_back(newNode);
                    token = tokenizer.getNextToken();
                    generateTree(newNode, parserStack, token);
                    break;

                } else {
                    TreeNode* newNode = new TreeNode(token.value);
                    newNode->parent = node;
                    node->children.push_back(newNode);
                    if(parserStack.top().second == dataType::Key)
                    {
                        parserStack.push({token, dataType::Field});
                        generateTree(node->parent, parserStack, t);
                        break;
                    } else if(parserStack.top().second == dataType::SpecialSymb || parserStack.top().second == dataType::Field)
                    {
                        parserStack.push({token, dataType::Field});
                        generateTree(node, parserStack, t);
                        break;
                    } else 
                    {
                        throw std::runtime_error("Error: Invalid JSON format.");
                    }
                }
            }
            case TokenType::Comma : 
            {
                token = tokenizer.getNextToken();
                generateTree(node, parserStack, token);
                break;
            }
            case TokenType::True :
            case TokenType::False :
            case TokenType::Null :
            case TokenType::Number : 
            {
                TreeNode* newNode = new TreeNode(token.value);
                    newNode->parent = node;
                    node->children.push_back(newNode);
                    if(parserStack.top().second == dataType::Key)
                    {
                        parserStack.push({token, dataType::Field});
                        token = tokenizer.getNextToken();
                        generateTree(node->parent, parserStack, token);
                        break;
                    } else if(parserStack.top().second == dataType::SpecialSymb)
                    {
                        parserStack.push({token, dataType::Field});
                        token = tokenizer.getNextToken();
                        generateTree(node, parserStack, token);
                        break;
                    } else 
                    {
                        throw std::runtime_error("Error: Invalid JSON format.");
                    }
            }
            default:
                break;
        }
    }
}

TreeNode* JSONTree::generateTree() {

    TreeNode* root = nullptr;
    std::stack<std::pair<Token, dataType> > parserStack;
    Token token = tokenizer.getNextToken();
    parserStack.push({token, dataType::SpecialSymb});

    generateTree(root, parserStack, token);

    this->root = root;

    return root;
}

std::string JSONTree::distance(unsigned int d)
{
    std::string str = "";

    for (std::size_t i = 0; i < d; i++)
    {
        str += " ";
    }
    
    return str;
}

void JSONTree::print(TreeNode *root, unsigned int tab) {

    if (!root) 
    {
        return;
    }
    
    if(root->str == "{}" || root->str == "[]")
    {
        ++tab;
    } else if (root->isKey)
    {
        if(root->parent->str == "{}")
        {
            ++tab;
            std::cout<< distance(tab) << root->str << ':';
        } else std::cout << root->str << ':';
    }
    else 
    {
        std::cout << root->str << " ";
    }

    for (TreeNode* child: root->children) {
        if(root->str == "{}")
        {
            std::cout << '\n';
        } 
        if(child->str == "{}")
        {
            std::cout << '\n' << distance(tab) << '{';
        }
        if(child->str == "[]")
        {
            std::cout << '\n' << distance(tab) << '[';
        }

        print(child, tab);

        if(child->str == "{}")
        {
            std::cout << '\n' << distance(tab) << '}';
        }
        if(child->str == "[]")
        {
            std::cout << '\n' << distance(tab) << ']';
        }
    }
}

void JSONTree::getElementsByKey(const std::string key, TreeNode* root, std::vector<TreeNode* >& v) const
{

    if(!root) return;

    if(root->str == key)
    {
        v.push_back(root->children[0]);
    } 

    for (TreeNode* child: root->children) {
        
        getElementsByKey(key, child, v);
    }
    
}

void JSONTree::printElementsByKey(std::vector<TreeNode*>& v) 
{
    std::cout << '[' << '\n';

    for (std::size_t i = 0; i < v.size() - 1; i++)
    {
        if(v[i]->str == "{}") 
        {
            std::cout << "{";
            print(v[i], 1);
            std::cout << "\n }";
        }else if(v[i]->str == "[]"){
            std::cout << "[";
            print(v[i], 1);
            std::cout << "\n ]";
        } else std::cout << ' ' << v[i]->str << ", \n";
    }

    if(v[v.size() - 1]->str == "{}") 
    {
        std::cout << " {";
        print(v[v.size() - 1], 1);
        std::cout << "\n }";
    }else if (v[v.size() - 1]->str == "[]")
    {
        print(v[v.size() - 1], 1);
    } else std::cout << ' ' << v[v.size() - 1]->str << "\n";

    std::cout << '\n' << ']';
}

void JSONTree::writeToFile(TreeNode *root, unsigned int tab, std::string filename)
{
    std::ofstream myFile(filename);
    std::string h = "hello";
    myFile << 'h';

    if (!root) 
    {
        return;
    }
    
    if(root->str == "{}" || root->str == "[]")
    {
        ++tab;
    } else if (root->isKey)
    {
        if(root->parent->str == "{}")
        {
            ++tab;
            // myFile << distance(tab) << root->str << ':';
            // myFile << root->str << ':';
            myFile << ':';
        } else 
        {
            myFile << root->str;
            myFile << ':';
        }
    }
    else 
    {
        myFile << root->str << " ";
    }

    for (TreeNode* child: root->children) {
        if(root->str == "{}")
        {
            myFile << std::endl;
        } 
        if(child->str == "{}")
        {
            // myFile << '\n' << distance(tab) << '{';
            myFile << std::endl << '{';
        }
        if(child->str == "[]")
        {
            // myFile << '\n' << distance(tab) << '[';
            myFile << std::endl << '[';
        }

        print(child, tab);

        if(child->str == "{}")
        {
            // myFile << '\n' << distance(tab) << '}';
            myFile << std::endl << '}';
        }
        if(child->str == "[]")
        {
            // myFile << '\n' << distance(tab) << ']';
            myFile << std::endl << ']';
        }
    }

    myFile.close();
}
