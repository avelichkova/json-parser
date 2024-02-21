#include "Tokenizer.h"

std::string JSONTokenizer::readNull(std::ifstream& file) {
    char ch;
    while (file.get(ch) && ch != 'l');
    file.get(ch);
    return "null";
}

std::string JSONTokenizer::readTrue(std::ifstream& file) {
    char ch;
    while (file.get(ch) && ch != 'e');
    return "true";
}

std::string JSONTokenizer::readFalse(std::ifstream& file) {
    char ch;
    while (file.get(ch) && ch != 'e');
    return "false";
}

std::string JSONTokenizer::readString(std::ifstream& file) {
    char ch;
    std::string buffer;
    while (file.get(ch) && ch != '"') {
        buffer += ch;
    }
    return buffer ;
}

std::string JSONTokenizer::readNumber(std::ifstream& file) {
    char ch;
    std::string buffer;
    while (file.get(ch) && (isdigit(ch) || ch == '.' || ch == '-')) {
        buffer += ch;
    }
    file.putback(ch);
    return buffer;
}


// public

JSONTokenizer::JSONTokenizer(const std::string& filename) 
{
    file.open(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}     

Token JSONTokenizer::getNextToken() {

    char ch;

    // Skip whitespace
    while (file.get(ch) && isspace(ch));

    if (file.eof()) {
        closeFile();
        return {TokenType::Invalid, ""};
    }

    switch (ch) {
        case '{':
            return {TokenType::LBrace, "{"};
        case '}':
            return {TokenType::RBrace, "}"};
        case '[':
            return {TokenType::LBracket, "["};
        case ']':
            return {TokenType::RBracket, "]"};
        case ':':
            return {TokenType::Colon, ":"};
        case ',':
            return {TokenType::Comma, ","};
        case '"':
            return {TokenType::String, readString(file)};
        case 't':
            return {TokenType::True, readTrue(file)};
        case 'f':
            return {TokenType::False, readFalse(file)};
        case 'n':
            return {TokenType::Null, readNull(file)};
        default:
            if (isdigit(ch) || ch == '-') {
                file.putback(ch);
                return {TokenType::Number, readNumber(file)};
            } else {
                file.putback(ch);
                return {TokenType::Invalid, ""};
            }
    }
}

void JSONTokenizer::closeFile()
{
    file.close();
}

