#ifndef USER_H
#define USER_H
#include <string>
class User
{
    public:
        User();
        //void signup(); hamoon constructore
        void login();
        void follow();
        void chargeAccount();
        void searchMovies();
        void viewMovieDetails();
        void buyMovie();
        void rateMovie();
        void postComment();
        void viewPurchases();
        void viewUnreadNotifs();
        void viewNotifs();

        // std::string getUsername();
        // std::string getPassword();
        // std::string getEmail();
        // int getAge();
        // int getId();
        // bool isPublisher();
    protected:
        std::string username;
        std::string password;
        std::string email;
        int age;
        int id;
        bool is_publisher;
};

#endif