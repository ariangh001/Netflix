#ifndef AI_H
#define AI_H
#include <vector>
#include "Movie.h"
typedef unsigned int Counter;
class AI
{
    public:
        void makeMatrix(std::vector<Movie*> temp);
        std::vector<Movie*> recommendMovie(int film_id,std::vector<Movie*> temp);
        void deletePurchases(std::vector<Movie*> purchased);
    private:
        std::vector<std::vector<int>> matrix;
};
#endif