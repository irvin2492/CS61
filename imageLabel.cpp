/*
  Author:Irvin Samuel
  Date: April 22, 2019
  Purpose: To Label components of an image using two different algorithms–Breadth-first search and depth-first search


  Sample Use
  Input the dimensions of the image (value between 5 and 25)
6
Input the density of the image in decimal form (value between 0 and 1)
.4

Depth-First Search Grid
(0,0) (1,0) (0,0) (0,0) (1,0) (0,0)
(0,0) (1,0) (1,0) (0,0) (1,0) (1,0)
(1,0) (0,0) (0,0) (0,0) (0,0) (0,0)
(0,0) (0,0) (0,0) (0,0) (0,0) (0,0)
(0,0) (1,0) (1,0) (1,0) (0,0) (1,0)
(1,0) (0,0) (1,0) (0,0) (0,0) (1,0)

Breadth-First Search Grid
(0,0) (1,0) (0,0) (0,0) (1,0) (0,0)
(0,0) (1,0) (1,0) (0,0) (1,0) (1,0)
(1,0) (0,0) (0,0) (0,0) (0,0) (0,0)
(0,0) (0,0) (0,0) (0,0) (0,0) (0,0)
(0,0) (1,0) (1,0) (1,0) (0,0) (1,0)
(1,0) (0,0) (1,0) (0,0) (0,0) (1,0)


After Scanning

Depth-First Search Grid
(0,0) (2,1) (0,0) (0,0) (3,1) (0,0)
(0,0) (2,2) (2,3) (0,0) (3,2) (3,3)
(4,1) (0,0) (0,0) (0,0) (0,0) (0,0)
(0,0) (0,0) (0,0) (0,0) (0,0) (0,0)
(0,0) (5,1) (5,2) (5,3) (0,0) (6,1)
(7,1) (0,0) (5,4) (0,0) (0,0) (6,2)

Breadth-First Search Grid
(0,0) (2,1) (0,0) (0,0) (3,1) (0,0)
(0,0) (2,2) (2,3) (0,0) (3,2) (3,3)
(4,1) (0,0) (0,0) (0,0) (0,0) (0,0)
(0,0) (0,0) (0,0) (0,0) (0,0) (0,0)
(0,0) (5,1) (5,2) (5,3) (0,0) (6,1)
(7,1) (0,0) (5,4) (0,0) (0,0) (6,2)


*/




#include "make2dArray.h"
#include <iostream>
#include <cstdlib>
#include <stack>

#include <queue>

struct Position{
  int row;
  int col;
  int label;
  int order;
  Position(int newR,int newC, int lab){
    row=newR;
    col=newC;
    label = lab;
    order =0;
  }
  Position(){
    row=col=label=order=0;
  }
};


void getValues(int& dimension,double& density);
void scanGrids(Position**& dfs, Position**&bfs,const int& dimension);
void DFS(Position**& grid,const int& row,const int& col,const int& lab);
void BFS(Position**& grid,const int& row,const int& col,const int& lab);
void fillImage(Position**& dfs, Position**& bfs,const int& dimension, const double& dens);
void printImage(Position**& dfs, Position**& bfs, const int& dimension);

int main(){
  int dimension=0;
  Position** dfGrid;
  Position** bfGrid;
  double density=0.0;
  getValues(dimension,density);
  fillImage(dfGrid,bfGrid,dimension,density);
  printImage(dfGrid,bfGrid,dimension);
  scanGrids(dfGrid,bfGrid,dimension);
  cout<<"\nAfter Scanning\n";
  printImage(dfGrid,bfGrid,dimension);



  return 0;
}

void getValues(int& dimension,double& density){
  do{
    cout<<"Input the dimensions of the image (value between 5 and 25)\n";
    cin>>dimension;
  }while(dimension<5||dimension>25);

  do{
    cout<<"Input the density of the image in decimal form (value between 0 and 1)\n";
    cin>>density;
  }while(density>1||density<0);

}


void fillImage(Position**& dfs,Position**& bfs,const int& dimension, const double& dens){
  srand(time(NULL));
  int r=0;
  double myR=0.0;

  make2dArray(dfs,dimension+2,dimension+2);
  make2dArray(bfs,dimension+2,dimension+2);


  for(int i=0;i<dimension+2;i++){
    dfs[0][i].label=dfs[dimension+1][i].label=0;//top and bottom wall of 0's
    dfs[i][0].label=dfs[i][dimension+1].label=0;//right and left wall of 0's
    bfs[0][i].label=bfs[dimension+1][i].label=0;//top and bottom wall of 0's
    bfs[i][0].label=bfs[i][dimension+1].label=0;//right and left wall of 0's
  }

  for(int a=1;a<dimension+1;a++){
    for(int b=1;b<dimension+1;b++){
      r=rand()%100;
      myR=(1.0*r)/100;
      dfs[a][b].row=a;//gives each position its row
      dfs[a][b].col=b;//gives each position its column
      bfs[a][b].row=a;//gives each position its row
      bfs[a][b].col=b;//gives each position its column
      if(myR<dens){
        dfs[a][b].label=1;
        bfs[a][b].label=1;

      }
      else{
        dfs[a][b].label=0;
        bfs[a][b].label=0;
      }
    }

  }

}

void printImage(Position**& dfs,Position**& bfs, const int& dimension){
  int a,b;
  a=b=0;
  cout<<"\nDepth-First Search Grid"<<endl;
  for(a=1;a<dimension+1;a++){
    for(b=1;b<dimension+1;b++){
      cout<<'('<<dfs[a][b].label<<','<<dfs[a][b].order<<") ";
    }
    cout<<endl;
  }
  cout<<endl;

  cout<<"Breadth-First Search Grid"<<endl;
  for( a=1;a<dimension+1;a++){
    for( b=1;b<dimension+1;b++){
      cout<<'('<<bfs[a][b].label<<','<<bfs[a][b].order<<") ";
    }
    cout<<endl;
  }
  cout<<endl;
}


void scanGrids(Position**& dfs, Position**&bfs,const int& dimension){
  int componentLabel=1;
  for(int row=1;row<=dimension;row++){
    for(int col=1;col<=dimension;col++){
      if(dfs[row][col].label==1){
        componentLabel++;
        dfs[row][col].order =1;
        DFS(dfs,row,col,componentLabel);
        BFS(bfs,row,col,componentLabel);
      }

    }
  }

}

void DFS(Position**& grid,const int& row,const int& col,const int& lab){
  stack<Position> s1;
  Position here =grid[row][col];
  int numOrder =2;//after finding the first component pixel, the next one will have the next num
  s1.push(here);
  Position next;
  grid[row][col].label=lab;//initial position
  int r,c;//new row and column to be checked
  r=c=0;
  int moveCheck,lastMove;
  moveCheck=0;
  lastMove=3;
  Position moves[4];//––the lab part is arbitrary
  moves[0]=Position(0,1,lab);//col+1 (right)
  moves[1]=Position(1,0,lab);//row+1 (down)
  moves[2]=Position(0,-1,lab);//col-1 (left)
  moves[3]=Position(-1,0,lab);//row-1 (up)

  while(!s1.empty()){
    while(moveCheck<=lastMove){//iteration through each possible directional move
      r=here.row+moves[moveCheck].row;
      c=here.col+moves[moveCheck].col;
      if(grid[r][c].label==1){ //if pixel is found, stop checking other directions
        break;
      }
      moveCheck++;
    }
    if(moveCheck<=lastMove){//if you found another pixel next to it
      grid[r][c].label=lab;//mark it as one of the components
      grid[r][c].order=numOrder++;
      s1.push(here);//pushing it on the stack means its already checked and part of the component
      here=grid[r][c];
      moveCheck=0;
    }
    else{
      next=s1.top();
      if(next.row==here.row){
        moveCheck=2+(next.col-here.col);
      }
      else{
        moveCheck=1+(next.row-here.row);
      }
      s1.pop();
      here =next;
    }
  }


}
void BFS(Position**& grid,const int& row,const int& col,const int& lab){
  queue<Position> q1;
  Position moves[4];
  grid[row][col].label=lab;//initial position
  Position here =grid[row][col];
  grid[row][col].order=1;//first pixel found
  int newOrder=2;
  bool isRunning = true;
  int r,c;//new row and column to be checked
  r=c=0;
  int moveCheck,lastMove;
  moveCheck=0;
  lastMove=3;
  moves[0]=Position(0,1,lab);//col+1 (right)
  moves[1]=Position(1,0,lab);//row+1 (down)
  moves[2]=Position(0,-1,lab);//col-1 (left)
  moves[3]=Position(-1,0,lab);//row-1 (up)
  do{
    while(moveCheck<=lastMove){//iteration through each possible directional move
      r=here.row+moves[moveCheck].row;
      c=here.col+moves[moveCheck].col;
      if(grid[r][c].label==1){//if find a pixel
        grid[r][c].label=lab;
        grid[r][c].order = newOrder++;
        q1.push(grid[r][c]);//if neighbor, it's put onto queue
      }

      moveCheck++;
    }

    if(!q1.empty()){
      here=q1.front(); //pops neighbors off queue and checks its neighbors
      q1.pop();
      moveCheck=0;
    }
    else{
      isRunning = false;//if there's no neighbor, it exits
    }

  }while(isRunning);
}
