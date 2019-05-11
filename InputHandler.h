#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include <string>
typedef std::string input;


input getInput(input line);//ye while(getline(cin,input))
//ke toosh getline,erasespace,checkstring,pass be function dare;
std::string checkString(std::string line);
std::string eraseSpaces(std::string line);



typedef struct signUpInput SignUpInput;
struct signUpInput
{
    input email;
    input username;
    input password;
    input age;
    input is_publisher;
};

typedef struct loginInput LoginInput;
struct loginInput
{
    input username;
    input password;
};

typedef struct submissionInput SubmissionInput;
struct submissionInput
{
    input name;
    input year;
    input length;
    input price;
    input summary;
    input director;
};

typedef struct editDetailsInput EditDetailsInput;
struct editDetailsInput
{
    input film_id;
    input name;
    input year;
    input length;
    input summary;
    input director;
};

typedef struct deleteFilmInput DeleteFilmInput;
struct deleteFilmInput
{
    input film_id;
};

typedef struct publishedInput PublishedInput;
struct publishedInput
{
    input name;
    input min_rate;
    input min_year;
    input price;
    input max_year;
    input director;
};

typedef struct replyInput ReplyInput;
struct replyInput
{
    input film_id;
    input comment_id;
    input content;
};

typedef struct deleteCommentInput DeleteCommentInput; 
struct deleteCommentInput
{
    input film_id;
    input comment_id;
};

typedef struct followInput FollowInput;
struct followInput
{
    input user_id;
};

typedef struct chargeInput chargeInput;
struct chargeInput
{
    input amount;
};

typedef struct searchInput SearchInput;
struct searchInput
{
    input name;
    input min_rate;
    input min_year;
    input price;
    input max_year;
    input director;
};

typedef struct viewDetailsInput ViewDetailsInput;
struct viewDetailsInput
{
    input film_id;
};

typedef struct buyInput BuyInput;
struct buyInput
{
    input film_id;
};

typedef struct rateInput RateInput;
struct rateInput
{
    input film_id;
    input score;
};

typedef struct commentInput commentInput;
struct commentInput
{
    input film_id;
    input content;
};

typedef struct purchasedInput PurchasedInput;
struct purchasedInput
{
    input name;
    input price;
    input min_year;
    input max_year;
    input director;
};

typedef struct viewNotificationsInput ViewNotificationsInput;
struct viewNotificationsInput
{
    input limit;
};

#endif