#include "AI.h"

void AI::makeMatrix(std::vector<Movie*> temp)
{
    for(Counter i=0; i<temp.size(); i++)
        matrix.push_back(std::vector<int>(temp.size(),-1));
}

void AI::updateMatrix(int index1, int index2)
{
    matrix[index1][index2]++;
}
std::vector<Movie*> AI::recommendMovie(int film_id,std::vector<Movie*> temp,std::vector<Movie*> purchased)
{
    std::vector<Movie*> recommended;
    int movie_index = 0, new_movie = 0, max_sold = -1;
    bool is_finished = true;
    movie_index = getMovieIndex(temp,film_id);
    checkMatrix(temp,purchased,movie_index);
    for(Counter i=0; i < 4; i++)
    {
        max_sold = -1;
        for(Counter k=0; k<matrix[movie_index].size(); k++)
            if(matrix[movie_index][k] != -1)
                is_finished = false;
        if(is_finished == true)
            break;
        for(Counter j=0; j<matrix[movie_index].size(); j++)
            if(matrix[movie_index][j] > max_sold)
            {
                max_sold = matrix[movie_index][j];
                new_movie = j;
            }
        recommended.push_back(temp[new_movie]);
        matrix[movie_index][new_movie] = -1;
        is_finished = true;
    }
    return recommended;
}

bool AI::isPurchased(std::vector<Movie*> purchased,int film_id)
{
    for(Counter i=0; i<purchased.size(); i++)
        if(purchased[i]->getId() == film_id)
            return true;
    return false;
}

void AI::checkMatrix(std::vector<Movie*> temp,std::vector<Movie*> purchased,int movie_index)
{
    for(Counter i=0; i<matrix[movie_index].size(); i++)
        if(isPurchased(purchased,temp[i]->getId()) == true
        || temp[i]->isDeleted() == true)
            matrix[movie_index][i] = -1;
}

int AI::getMovieIndex(std::vector<Movie*> temp,int film_id)
{
    for(Counter i=0; i<temp.size(); i++)
        if(temp[i]->getId() == film_id)
            return i;
}