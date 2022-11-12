#include <vector>
#include <deque>
#include <utility>

#include "stdlib.h"

void createFood(std::vector<int>& bg, int food[2], const int& nx, const int& ny){
    if( food[0] == 0){
        food[0] = rand()%(nx-2) + 1;
        food[1] = rand()%(ny-2) + 1;
        bg[food[1]*nx+food[0]] = 2;

    }
}

bool eatFood(int food[2], std::deque<std::pair<int,int>>& snake){
    if( (food[0]== std::get<0>(snake[0])) && (food[1] == std::get<1>(snake[0])) ){
        food[0] = 0;
        food[1] = 0;
        return true;
    }
    return false;
}