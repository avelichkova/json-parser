#include "JSONTree.h"
#include "Tokenizer.h"
#include <iostream>
#include "Runner.h"

int main() {

    try {
        Runner::run();

    } catch (std::exception& e) {
        
        std::cout << e.what() << std::endl;
    }

    return 0;
}
