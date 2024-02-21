#include "Runner.h"

void Runner::run()
{
    std::cout << "Welcome to JSON parser! \n";

    Commands shell;
    std::string command, generalCommand, secondCommand;

    int counterOfCommands = 0;

    while(command != "exit") {

            shell.toLower(command);

            std::cout << "Please enter a valid command or type \"help\" for more information." << std::endl;

            std::cout << ">";
            std::getline(std::cin, command);

            std::istringstream iss(command);

            iss >> generalCommand >> secondCommand;

            if (counterOfCommands == 0 && generalCommand != "open" && generalCommand != "help") {
                
                throw std::invalid_argument("Please open a file first!");
            }

            shell.process(command);

            std::cout << "------------------" << std::endl;

            // if (command == "close" && shell.close() == false) {
            //     break;
            // }
            
            counterOfCommands++;
        }
}