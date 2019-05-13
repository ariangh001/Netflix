#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include <string>
#include <iostream>
#include <vector>
#include "ExceptionHandler.h"
#define POST_COMMAND "POST"
#define PUT_COMMAND "PUT"
#define DELETE_COMMAND "DELETE"
#define GET_COMMAND "GET"
#define COMMAND_INDEX 0
typedef std::string input;
typedef unsigned int Counter;

class InputHandler
{
    public:
        InputHandler();
        void start();
    private:
        void getInput();
        std::vector<std::string> seperateString(input line);
        void checkSyntaxErrors(std::vector<std::string> words);
        void commandExists(std::vector<std::string> words);
        void checkParameters(std::vector<std::string> words);
        void checkFirstParameter(std::string command);
        bool questionMarkExists(std::vector<std::string> words);
};



































/*
// typedef struct signUpInput SignUpInput;
// struct signUpInput
// {
//     input email;
//     input username;
//     input password;
//     input age;
//     input is_publisher;
// };

// typedef struct loginInput LoginInput;
// struct loginInput
// {
//     input username;
//     input password;
// };

// typedef struct submissionInput SubmissionInput;
// struct submissionInput
// {
//     input name;
//     input year;
//     input length;
//     input price;
//     input summary;
//     input director;
// };

// typedef struct editDetailsInput EditDetailsInput;
// struct editDetailsInput
// {
//     input film_id;
//     input name;
//     input year;
//     input length;
//     input summary;
//     input director;
// };

// typedef struct deleteFilmInput DeleteFilmInput;
// struct deleteFilmInput
// {
//     input film_id;
// };

// typedef struct publishedInput PublishedInput;
// struct publishedInput
// {
//     input name;
//     input min_rate;
//     input min_year;
//     input price;
//     input max_year;
//     input director;
// };

// typedef struct replyInput ReplyInput;
// struct replyInput
// {
//     input film_id;
//     input comment_id;
//     input content;
// };

// typedef struct deleteCommentInput DeleteCommentInput; 
// struct deleteCommentInput
// {
//     input film_id;
//     input comment_id;
// };

// typedef struct followInput FollowInput;
// struct followInput
// {
//     input user_id;
// };

// typedef struct chargeInput chargeInput;
// struct chargeInput
// {
//     input amount;
// };

// typedef struct searchInput SearchInput;
// struct searchInput
// {
//     input name;
//     input min_rate;
//     input min_year;
//     input price;
//     input max_year;
//     input director;
// };

// typedef struct viewDetailsInput ViewDetailsInput;
// struct viewDetailsInput
// {
//     input film_id;
// };

// typedef struct buyInput BuyInput;
// struct buyInput
// {
//     input film_id;
// };

// typedef struct rateInput RateInput;
// struct rateInput
// {
//     input film_id;
//     input score;
// };

// typedef struct commentInput commentInput;
// struct commentInput
// {
//     input film_id;
//     input content;
// };

// typedef struct purchasedInput PurchasedInput;
// struct purchasedInput
// {
//     input name;
//     input price;
//     input min_year;
//     input max_year;
//     input director;
// };

// typedef struct viewNotificationsInput ViewNotificationsInput;
// struct viewNotificationsInput
// {
//     input limit;
// };
*/
#endif