#include <iostream>
#include <vector>
#include <deque>
#include <utility>
#include <conio.h>
//#include "sys/ioctl.h"

#include "stdlib.h"

#include "internals.h"
#include "display.h"
#include "food.h"


std::vector<int> backgroundSetup( const int& nx, const int& ny ){
  std::vector<int> bg(nx*ny, 0);
  int i;
  for( i=0; i<nx; i++){
      bg[i] = 1;
  }
  for( i=0; i<nx; i++){
      bg[(ny-1)*nx + i] = 1;
  }
  for( i=0; i<ny; i++){
      bg[i*nx] = 1;
  }
  for( i=0; i<ny; i++){
      bg[i*nx+nx-1] = 1;
  }


  return bg; 
}

void add_snake(std::deque<std::pair<int,int>>& snake, std::vector<int>& bg, const int& nx, const int& ny){
  for(auto const & elem : snake)
  {
    bg[std::get<1>(elem)*nx+std::get<0>(elem)] = 2;
  }
}

void remove_snake(std::deque<std::pair<int,int>>& snake, std::vector<int>& bg, const int& nx, const int& ny){
  for(auto const & elem : snake)
  {
    bg[std::get<1>(elem)*nx+std::get<0>(elem)] = 0;
  }
}

void snake_movement(char key, int dxdy[2]){
  int vect = 1;
  switch(key)
  {
    case 'q': vect = -1;
    case 'd': 
      if(dxdy[0] == -vect) return;
      dxdy[1] = 0;
      dxdy[0] = vect;
      break;
    case 'z': vect = -1;
    case 's':
      if(dxdy[1] == -vect) return;
      dxdy[0] = 0;
      dxdy[1] = vect; 
      break;
    default: ;
  }
}

bool verifyBorder(std::deque<std::pair<int,int>>& snake, const int& nx, const int& ny){
  /*
    your code here
  */
  return true;
}

std::deque<std::pair<int,int>> setupSnake( const int snake_len ){
  std::deque<std::pair<int,int>> snake;
  std::pair<int,int> p = {25,12};
  snake.push_back(p);
  for(int i = 1; i < snake_len; i++)
  {
    std::pair<int,int> elem = snake.back();
    snake.push_back(std::pair<int,int>{std::get<0>(elem)+1,std::get<1>(elem)});
  }
  return snake;
}

void update_snake_coordinates(std::deque<std::pair<int,int>>& snake, const int & snl, int dxdy[2]){
  if(snl == snake.size())
    snake.pop_back();
  snake.push_front(std::pair<int,int>{std::get<0>(snake[0])+dxdy[0],std::get<1>(snake[0])+dxdy[1]});
}

void startGame(const int& lap, const int& nx, const int& ny, int & snl, std::deque<std::pair<int,int>>& snake, std::vector<int>& bg){
    char key;
    int dxdy[2] = {1,0};
    int food[2] = {0,0};

    createFood( bg, food, nx, ny );

    while( true ){
        internal::frameSleep(lap);
        if( internal::keyEvent() ){
            //std::cin >> key; 
            key = _getch();//std::cin.get();
            snake_movement(key, dxdy);
        }
        backgroundClear();
        add_snake( snake, bg, nx, ny );
        printFrame(nx, ny, bg);
        remove_snake(snake, bg, nx, ny);
        bool out =  verifyBorder(snake, nx, ny);
        if( out == false){
            std::cerr << "" << std::endl;
            exit(1);
        }
        bool eat = eatFood(food, snake);
        if(eat){
            createFood(bg, food, nx, ny);
            snl++;
        }
        update_snake_coordinates(snake, snl, dxdy);

    }
}



int main(){
    const int nx = 50;
    const int ny = 25;
    const int lap=20;//200

    int snake_len = 3;

    
    std::vector<int> background = backgroundSetup(nx, ny);
    printFrame(nx,ny, background);


    std::deque<std::pair<int,int>> snake = setupSnake(snake_len);

    
    startGame(lap, nx, ny, snake_len, snake, background);
    
   return 0;
}



