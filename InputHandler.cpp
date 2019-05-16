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
            handleInput();
        }
        catch(exception &e)
        {
            cout << e.what() << '\n';
        }
    }
}

void InputHandler::handleInput()
{
    input line;
    getline(cin,line);
    if(line.length() != 0)
    {
        CommandList words = seperateString(line);
        checkSyntaxErrors(words);
        //checkFunctions(words);
    }
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
        if(isEven(words.size() - question_index - 1) == false
         || words.size() < 5)
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

void InputHandler::checkFunctions(CommandList words)
{
    if(words[COMMAND_TYPE_INDEX] == POST_COMMAND)
    {
        if(words[FUNCTION_INDEX] == "signup")
            checkSignUp(words);
        else if(words[FUNCTION_INDEX] == "login")
            checkLogin(words);
        else if(words[FUNCTION_INDEX] == "films")
            checkSubmitFilm(words);
        else if(words[FUNCTION_INDEX] == "money")
        {
            if(words.size() == 2)
                checkGetMoney(words);
            else
                checkChargeAccount(words);
        }
        else if(words[FUNCTION_INDEX] == "replies")
            checkReply(words);
        else if(words[FUNCTION_INDEX] == "buy")
            checkBuyFilm(words);
        else if(words[FUNCTION_INDEX] == "rate")
            checkRateMovie(words);
        else if(words[FUNCTION_INDEX] == "comments")
            checkComment(words);
    }
    else if(words[COMMAND_TYPE_INDEX] == PUT_COMMAND)
    {
        if(words[FUNCTION_INDEX] == "films")
            checkEditFilm(words);
    }
    else if(words[COMMAND_TYPE_INDEX] == DELETE_COMMAND)
    {
        if(words[FUNCTION_INDEX] == "films")
            checkDeleteFilm(words);
        else if(words[FUNCTION_INDEX] == "comments")
            checkDeleteComment(words);
    }
    else if(words[COMMAND_TYPE_INDEX] == GET_COMMAND)
    {
        if(words[FUNCTION_INDEX] == "followers")
            checkShowFollowers(words);
        else if(words[FUNCTION_INDEX] == "published")
            checkPublishedFilms(words);
        else if(words[FUNCTION_INDEX] == "films")
        {
            if(words[3] == "film_id")
                checkMovieDetails(words);
            else
                checkSearchMovie(words);
        }
        else if(words[FUNCTION_INDEX] == "purchased")
            checkPurchases(words);
        else if(words[FUNCTION_INDEX] == "notifications")
        {
            if(words[3] == "read")
                checkNotifications(words);
            else
                checkUnreadNotifications(words);
        }
    }
}

void InputHandler::checkSignUp(CommandList words)
{
    Map signUpInput = {{"email","-1"},{"username","-1"},
        {"password","-1"},{"age","-1"},{"is_publisher","-1"}};
    if(words.size() < 11)
        throw BadRequest();
    for(Counter i=FIRST_PARAM_INDEX; i<words.size(); i+=2)
    {
        auto itr = signUpInput.find("");
        if(words[i] == "username")
            itr = signUpInput.find("username");
        else if(words[i] == "password")
            itr = signUpInput.find("password");
        else if(words[i] == "age")
            itr = signUpInput.find("age");
        else if(words[i] == "is_publisher")
            itr = signUpInput.find("is_publisher");
        else if(words[i] == "email")
        {
            checkEmailSyntax(words[i+1]);
            itr = signUpInput.find("email");
        }
        itr->second = words[i+1];
    }
    if(isEmpty(signUpInput) == true)
        throw BadRequest();
    handler.signup(signUpInput);
}

void InputHandler::checkLogin(CommandList words)
{
    Map loginInput = {{"username","-1"},{"password","-1"}};
    if(words.size() < 7)
        throw BadRequest();
    for(Counter i=FIRST_PARAM_INDEX; i<words.size(); i+=2)
    {
        auto itr = loginInput.find("");
        if(words[i] == "username")
            itr = loginInput.find("username");
        else if(words[i] == "password")
            itr = loginInput.find("password");
        itr->second = words[i+1];
    }
    if(isEmpty(loginInput) == true)
        throw BadRequest();
    handler.login(loginInput);
}

void InputHandler::checkSubmitFilm(CommandList words)
{
    Map submissionInput = {{"name","-1"},{"year","-1"},{"length","-1"},
        {"price","-1"},{"summary","-1"},{"director","-1"}};
    if(words.size() < 15)
        throw BadRequest();
    for(Counter i=FIRST_PARAM_INDEX; i<words.size(); i+=2)
    {
        auto itr = submissionInput.find("");
        if(words[i] == "name")
            itr = submissionInput.find("name");
        else if(words[i] == "year")
            itr = submissionInput.find("year");
        else if(words[i] == "length")
            itr = submissionInput.find("length");
        else if(words[i] == "price")
            itr = submissionInput.find("price");
        else if(words[i] == "summary")
            itr = submissionInput.find("summary");
        else if(words[i] == "director")
            itr = submissionInput.find("director");
        itr->second = words[i+1];
    }
    if(isEmpty(submissionInput) == true)
        throw BadRequest();
    handler.checkFunctions("submitFilm",submissionInput);
}

void InputHandler::checkEditFilm(CommandList words)
{
    Map editDetailsInput = {{"film_id","-1"},{"name","-1"},{"year","-1"},
        {"length","-1"},{"price","-1"},{"summary","-1"},{"director","-1"}};
    if(words.size() < 17)
        throw BadRequest();
    for(Counter i=FIRST_PARAM_INDEX; i<words.size(); i+=2)
    {
        auto itr = editDetailsInput.find("");
        if(words[i] == "name")
            itr = editDetailsInput.find("name");
        else if(words[i] == "year")
            itr = editDetailsInput.find("year");
        else if(words[i] == "length")
            itr = editDetailsInput.find("length");
        else if(words[i] == "price")
            itr = editDetailsInput.find("price");
        else if(words[i] == "summary")
            itr = editDetailsInput.find("summary");
        else if(words[i] == "director")
            itr = editDetailsInput.find("director");
        else if(words[i] == "film_id")
            itr = editDetailsInput.find("film_id");
        itr->second = words[i+1];
    }
    if(isEmpty(editDetailsInput) == true)
        throw BadRequest();
    handler.checkFunctions("editFilmDetails",editDetailsInput);
}

void InputHandler::checkDeleteFilm(CommandList words)
{
    Map deleteFilmInput = {{"film_id","-1"}};
    if(words.size() < 5)
        throw BadRequest();
    auto itr = deleteFilmInput.find("film_id");
    itr->second = words[words.size() - 1];
    if(isEmpty(deleteFilmInput) == true)
        throw BadRequest();
    handler.checkFunctions("deleteFilmDetails",deleteFilmInput);
}

void InputHandler::checkPublishedFilms(CommandList words)
{
    Map publishedInput = {{"name","-1"},{"min_rate","-1"},
        {"min_year","-1"},{"price","-1"},{"max_year","-1"},{"director","-1"}};
    if(words.size() < 15)
        throw BadRequest();
    for(Counter i=FIRST_PARAM_INDEX; i<words.size(); i+=2)
    {
        auto itr = publishedInput.find("");
        if(words[i] == "name")
            itr = publishedInput.find("name");
        else if(words[i] == "min_rate")
            itr = publishedInput.find("min_rate");
        else if(words[i] == "min_year")
            itr = publishedInput.find("min_year");
        else if(words[i] == "price")
            itr = publishedInput.find("price");
        else if(words[i] == "max_year")
            itr = publishedInput.find("max_year");
        else if(words[i] == "director")
            itr = publishedInput.find("director");
        itr->second = words[i+1];
    }
    if(isEmpty(publishedInput) == true)
        throw BadRequest();
    handler.checkFunctions("publishedFilms",publishedInput);
}

void InputHandler::checkShowFollowers(CommandList words)
{
    Map viewFollowers;
    if(words.size() != 2)
        throw BadRequest();
    handler.checkFunctions("showFollowers",viewFollowers);
}

void InputHandler::checkGetMoney(CommandList words)
{
    Map getMoney;
    if(words.size() != 2)
        throw BadRequest();
    handler.checkFunctions("showFollowers",getMoney);
}

void InputHandler::checkReply(CommandList words)
{
    Map replyInput = {{"film_id","-1"},{"comment_id","-1"},{"content","-1"}};
    if(words.size() < 9)
        throw BadRequest();
    for(Counter i=FIRST_PARAM_INDEX; i<words.size(); i+=2)
    {
        auto itr = replyInput.find("");
        if(words[i] == "film_id")
            itr = replyInput.find("film_id");
        else if(words[i] == "comment_id")
            itr = replyInput.find("comment_id");
        else if(words[i] == "content")
            itr = replyInput.find("content");
        itr->second = words[i+1];
    }
    if(isEmpty(replyInput) == true)
        throw BadRequest();
    handler.checkFunctions("reply",replyInput);
}

void InputHandler::checkDeleteComment(CommandList words)
{
    Map deleteCommentInput = {{"film_id","-1"},{"comment_id","-1"}};
    if(words.size() < 7)
        throw BadRequest();
    for(Counter i=FIRST_PARAM_INDEX; i<words.size(); i+=2)
    {
        auto itr = deleteCommentInput.find("");
        if(words[i] == "film_id")
            itr = deleteCommentInput.find("film_id");
        else if(words[i] == "comment_id")
            itr = deleteCommentInput.find("comment_id");
        itr->second = words[i+1];
    }
    if(isEmpty(deleteCommentInput) == true)
        throw BadRequest();
    handler.checkFunctions("deleteComment",deleteCommentInput);
}

void InputHandler::checkFollow(CommandList words)
{
    Map followInput = {{"user_id","-1"}};
    if(words.size() < 5)
        throw BadRequest();
    for(Counter i=FIRST_PARAM_INDEX; i<words.size(); i+=2)
    {
        auto itr = followInput.find("");
        if(words[i] == "film_id")
            itr = followInput.find("film_id");
        itr->second = words[i+1];
    }
    if(isEmpty(followInput) == true)
        throw BadRequest();
    handler.checkFunctions("follow",followInput);
}

void InputHandler::checkChargeAccount(CommandList words)
{
    Map chargeInput = {{"amount","-1"}};
    if(words.size() < 5)
        throw BadRequest();
    for(Counter i=FIRST_PARAM_INDEX; i<words.size(); i+=2)
    {
        auto itr = chargeInput.find("");
        if(words[i] == "amount")
            itr = chargeInput.find("amount");
        itr->second = words[i+1];
    }
    if(isEmpty(chargeInput) == true)
        throw BadRequest();
    handler.checkFunctions("chargeAccount",chargeInput);
}

void InputHandler::checkSearchMovie(CommandList words)
{
    Map searchInput = {{"name","-1"},{"min_rate","-1"},
        {"min_year","-1"},{"price","-1"},{"max_year","-1"},{"director","-1"}};
    if(words.size() < 15)
        throw BadRequest();
    for(Counter i=FIRST_PARAM_INDEX; i<words.size(); i+=2)
    {
        auto itr = searchInput.find("");
        if(words[i] == "name")
            itr = searchInput.find("name");
        else if(words[i] == "min_rate")
            itr = searchInput.find("min_rate");
        else if(words[i] == "min_year")
            itr = searchInput.find("min_year");
        else if(words[i] == "price")
            itr = searchInput.find("price");
        else if(words[i] == "max_year")
            itr = searchInput.find("max_year");
        else if(words[i] == "director")
            itr = searchInput.find("director");
        itr->second = words[i+1];
    }
    handler.checkFunctions("searchMovies",searchInput);
}

bool InputHandler::isEmpty(Map words)
{
    for(auto itr = words.begin(); itr != words.end(); itr++)
        if(itr->first != "is_publisher")
            if(itr->second == "-1")
                throw BadRequest();
}

void InputHandler::checkEmailSyntax(std::string email)
{
    int has_error = HAS_ERROR;
    for(Counter i=1; i<email.length(); i++)
    {
        if(email[i] == '@')
        {
            for(Counter j=i+1; j<email.length(); j++)
            {
                if(email[j] == '.' && j != email.length() - 1)
                {
                    has_error = NO_ERROR;
                }
            }
        }
    }
    if(has_error == HAS_ERROR)
        throw BadRequest();
}