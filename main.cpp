#include <iostream>
#include <vector>
#include <utility>
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

void add_snake(std::vector<std::pair<int,int>>& snake, std::vector<int>& bg, const int& nx, const int& ny){
  /*
    your code here
  */
}

void remove_snake(std::vector<std::pair<int,int>>& snake, std::vector<int>& bg, const int& nx, const int& ny){
  /*
    your code here
  */
}

void snake_movement(char key, int dxdy[2]){
  /*
    your code here
  */
}

bool verifyBorder(std::vector<std::pair<int,int>>& snake, const int& nx, const int& ny){
  /*
    your code here
  */
}

std::vector<std::pair<int,int>> setupSnake( const int snake_len ){
  /*
    your code here
  */
}

void update_snake_coordinates(std::vector<std::pair<int,int>>& snake, const int & snl, int dxdy[2]){
  /*
    your code here
  */
}

void startGame(const int& lap, const int& nx, const int& ny, int & snl, std::vector<std::pair<int,int>>& snake, std::vector<int>& bg){
    char key;
    int dxdy[2] = {1,0};
    int food[2] = {0,0};

    createFood( bg, food, nx, ny );

    while( true ){
        internal::frameSleep(lap);
        if( internal::keyEvent() ){
            std::cin >> key; 
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
    const int lap=200;

    int snake_len = 3;

    
    std::vector<int> background = backgroundSetup(nx, ny);
    printFrame(nx,ny, background);


    std::vector<std::pair<int,int>> snake = setupSnake(snake_len);

    
    startGame(lap, nx, ny, snake_len, snake, background);
    
   return 0;
}



