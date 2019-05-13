#include "InputHandler.h"
using namespace std;

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
        catch(exception e)
        {
            cout << e.what() << '\n';
        }
    }
}

void InputHandler::getInput()
{
    input line;
    getline(cin,line);
    CommandList words = seperateString(line);
    checkSyntaxErrors(words);

}

void InputHandler::checkSyntaxErrors(CommandList words)
{
    checkFirstParameter(words[COMMAND_TYPE_INDEX]);
    commandExists(words);
    checkParameters(words);
}

void InputHandler::checkParameters(CommandList words)
{
    if(questionMarkExists(words) == true)
    {
        int question_index = -1;
        for(Counter i=0; i<words.size(); i++)
            if(words[i] == "?")
                question_index = i;
        if(isEven(words.size() - question_index - 1) == false)
            throw BadRequest();
    }
    else
    {
        if(isEven(words.size()) == false)
            throw BadRequest();
    }
}

void InputHandler::commandExists(CommandList words)
{
    if(questionMarkExists(words) == true)
    {
        if(words[2] == "?")
        {
            if(words[COMMAND_TYPE_INDEX] == POST_COMMAND)
            {
                if(words[1] != "signup"
                && words[1] != "login"
                && words[1] != "films"
                && words[1] != "replies"
                && words[1] != "followers"
                && words[1] != "money"
                && words[1] != "buy"
                && words[1] != "rate"
                && words[1] != "comments")
                    throw NotFound();
            }
            else if(words[COMMAND_TYPE_INDEX] == PUT_COMMAND)
            {
                if(words[1] != "films"
                && words[1] != "signup")
                    throw NotFound();
            }
            else if(words[COMMAND_TYPE_INDEX] == GET_COMMAND)
            {
                if(words[1] != "published"
                && words[1] != "films"
                && words[1] != "purchased")
                    throw NotFound();
            }
            else if(words[COMMAND_TYPE_INDEX] == DELETE_COMMAND)
            {
                if(words[1] != "comments"
                && words[1] != "films")
                    throw NotFound();
            }
        }
        else if(words[3] == "?")
        {
            if(!(words[1] == "notifications" && words[2] == "read"))
                throw NotFound();
        }
        else
            throw NotFound();
    }
    else
    {
        if(words[COMMAND_TYPE_INDEX] == POST_COMMAND)
        {
            if(words[1] != "money")
                throw NotFound();
        }
        else if(words[COMMAND_TYPE_INDEX] == PUT_COMMAND)
        {
            throw NotFound();
        }
        else if(words[COMMAND_TYPE_INDEX] == GET_COMMAND)
        {
            if(words[1] != "followers"
            && words[1] != "notitfications")
                throw NotFound();
        }
        else if(words[COMMAND_TYPE_INDEX] == DELETE_COMMAND)
        {
            throw NotFound();
        }
    }
}

void InputHandler::checkFirstParameter(string first_command)
{
    if(first_command != "POST"
    && first_command != "GET"
    && first_command != "DELETE"
    && first_command != "PUT")
        throw BadRequest();
}

CommandList InputHandler::seperateString(string line)
{
    stringstream input_stream(line);
    return vector<string>(istream_iterator<string>(input_stream),
                                        istream_iterator<string>());
}

bool InputHandler::questionMarkExists(CommandList words)
{
    for(Counter i=0; i<words.size(); i++)
        if(words[i] == "?")
            return true;
    return false;
}

bool InputHandler::isEven(int number)
{
    if(number % 2 == 0)
        return true;
    return false;
}