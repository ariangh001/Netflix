#include "InputHandler.h"

InputHandler::InputHandler()
{
    start();
}

void InputHandler::start()
{
    while(true)
    {
        try
        {
            getInput();
        }
        catch(std::exception e)
        {
            std::cout << e.what() << '\n';
        }
    }
}

void InputHandler::getInput()
{
    input line;
    getline(std::cin,line);
    std::vector<std::string> words = seperateString(line);
    checkSyntaxErrors(words);
}

void InputHandler::checkSyntaxErrors(std::vector<std::string> words)
{
    checkFirstParameter(words[0]);
    commandExists(words);
    checkParameters(words);
}

void InputHandler::checkParameters(std::vector<std::string> words)
{

}

void InputHandler::commandExists(std::vector<std::string> words)
{

}

void InputHandler::checkFirstParameter(std::string command)
{
    if(command != "POST"
    && command != "GET"
    && command != "DELETE"
    && command != "PUT")
        throw BadRequest();
}

std::vector<std::string> InputHandler::seperateString(std::string line)
{

}