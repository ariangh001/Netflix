#ifndef AI_H
#define AI_H
#include <vector>
#include "UsersRepository.h"
#include "MovieRepository.h"
#include "Movie.h"
#include "User.h"
typedef unsigned int Counter;
class AI
{
    public:
        void makeMatrix(std::vector<Movie*> temp);
        std::vector<Movie*> recommendMovie(int film_id,
                std::vector<Movie*> temp,std::vector<Movie*> purchased);
        bool isPurchased(std::vector<Movie*> purchased,int film_id);
        void updateMatrix(int index1, int index2);
    private:
        std::vector<std::vector<int>> matrix;
};
#endif