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

        // std::string getUsername() const;
        // std::string getPassword() const;
        // std::string getEmail() const;
        // int getAge() const;
        // int getId() const;
        // bool isPublisher() const;
    protected:
        std::string username;
        std::string password;
        std::string email;
        int age;
        int id;
        bool is_publisher;
};

#endif