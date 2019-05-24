#include "AI.h"

void AI::makeMatrix(std::vector<Movie*> temp)
{
    for(Counter i=0; i<temp.size(); i++)
        matrix.push_back(std::vector<int>(temp.size(),0));
    for(Counter i=0; i<temp.size(); i++)
        for(Counter j=0; j<temp.size(); j++)
            if(i != j)
                matrix[i][j] = temp[i]->getSold() + temp[j]->getSold();
}

std::vector<Movie*> AI::recommendMovie(int film_id,std::vector<Movie*> temp)
{
    std::vector<Movie*> recommended;
    int movie_index = 0, new_movie = 0, max_sold = 0;
    bool is_zero = true;
    for(Counter i=0; i<temp.size(); i++)
        if(temp[i]->getId() == film_id)
            movie_index = i;
    for(Counter i=0; i < 4; i++)
    {
        for(Counter k=0; k<matrix[movie_index].size(); k++)
            if(matrix[movie_index][k] != 0)
                is_zero = false;
        if(is_zero == true)
            break;
        for(Counter j=0; j<matrix[movie_index].size(); j++)
            if(matrix[movie_index][j] > max_sold)
            {
                max_sold = matrix[movie_index][j];
                new_movie = j;
            }
        recommended.push_back(temp[new_movie]);
        matrix[movie_index][new_movie] = 0;
        is_zero = true;
    }
    makeMatrix(temp);
    return recommended;
}

void AI::deletePurchases(std::vector<Movie*> purchased)
{
    for(Counter i=0; i<matrix.size(); i++)
        for(Counter j=0; j<matrix[i].size(); j++)
            if()
}