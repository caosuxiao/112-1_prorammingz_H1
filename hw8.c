#include <stdio.h>
#include <stdlib.h>
#include "forHW8.h"

#define IN_BOARD(x, y) (x >= 0 && x < MAX && y >= 0 && y < MAX)

// int maze[MAX][MAX] ={    //斷掉
//   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
//   { 0, 0, 0, 1, 1, 0, 1, 1, 0, 1 },
//   { 1, 0, 1, 1, 0, 0, 0, 0, 0, 1 },
//   { 1, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
//   { 1, 1, 1, 0, 1, 1, 0, 1, 1, 1 },
//   { 1, 0, 1, 1, 1, 0, 0, 1, 0, 1 },
//   { 1, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
//   { 1, 0, 1, 1, 1, 1, 1, 0, 0, 1 },
//   { 1, 0, 0, 0, 1, 0, 0, 0, 1, 1 },
//   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }};

int maze[MAX][MAX] ={    //接得起來
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 0, 0, 0, 1, 1, 0, 1, 1, 0, 1 },
  { 1, 0, 1, 1, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
  { 1, 1, 1, 0, 1, 1, 0, 1, 1, 1 },
  { 1, 0, 1, 1, 1, 0, 0, 1, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
  { 1, 0, 1, 1, 1, 1, 1, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }};

pos_t InAndOut(pos_t * exit){
    int count = 0;
    pos_t ent;
    for(int i=0; i<MAX; i++){
        int flag1 = 0, flag2 = 0, j;
        if(i == 0 || i == MAX - 1){  // 水平牆壁
            for(j=0; j<MAX; j++)
                if(maze[i][j] == 0){
                    flag1 = 1;
                    count++;
                } 
        }                            
        else                         // 垂直牆壁
            if(maze[i][0] == 0 || maze[i][MAX - 1] == 0){
                flag2 = 1;
                count++;
            } 
        if((flag1 || flag2) && count == 1){         // 搞入口
            if(flag1) ent.x = i, ent.y = j;
            else{
                if(maze[i][0] == 0) ent.x = i, ent.y = 0;
                else ent.x = i, ent.y = MAX - 1;
            }
        }
        else if((flag1 || flag2) && count == 2){    // 搞出口
            if(flag1) exit->x = i, exit->y = j;
            else{
                if(maze[i][0] == 0) exit->x = i, exit->y = 0;
                else exit->x = i, exit->y = MAX - 1;
            }
            break;
        }
    }
    return ent;
}

void Direction(pos_t target, stack_t * stack){
    int direc[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    for(int i=0; i<4; i++){
        int x = target.x + direc[i][0], y = target.y + direc[i][1];
        if(IN_BOARD(x, y) && maze[x][y] == 0){
            pos_t temp = {x, y};
            Push(stack, temp);
        }
        // stack->element->x, stack->element->y;
        //為甚麼element的成員不是用'.'取用
    }
}

pos_t Move(stack_t * stack){
    pos_t temp = Pop(stack);
    // Pop(stack)-> 沒有東西接還可以獲取成員嗎？
    if(temp.x == -1 && temp.y == -1)
        return temp;
    printf("now: (%d, %d)\n", temp.x, temp.y);
    return temp;
}

void PassBy(pos_t mouse){
    maze[mouse.x][mouse.y] = 7;
}

void PrintMaze(pos_t * ent, pos_t * exit){
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
            if(i == ent->x && j == ent->y){
                if(i == 0) printf("vv");
                else if(i == MAX - 1) printf("^^");
                else if(j == 0) printf("->");
                else if(j == MAX - 1) printf("<-");
            }
            else if(i == exit->x && j == exit->y) printf("!!");
            else if(maze[i][j] == 7)
                printf(" .");
            else printf("  ");
        }
        printf("\n");
    }
}

void main(){
    pos_t ent, mouse;
    pos_t * exit = (pos_t *)malloc(sizeof(pos_t));
    stack_t * stack = (stack_t *)malloc(sizeof(stack_t));
    Init(stack);
    ent = mouse = InAndOut(exit);
    printf("Starts from: (%d, %d)\n", mouse.x, mouse.y);
    while (!(mouse.x == exit->x && mouse.y == exit->y)){
        PassBy(mouse);
        Direction(mouse, stack);
        mouse = Move(stack);
        if(mouse.x == -1 && mouse.y == -1) break;
    }   // 已經empty了且也互不等於為什麼還會進去
    if(mouse.x == exit->x && mouse.y == exit->y)
        printf("finds the exit.\n");
    else
        printf("doesn't find the exit.\n");
    printf("Ends at: (%d, %d)\n", exit->x, exit->y);
    PrintMaze(&ent, exit);
    free(exit), free(stack);
    // 77, 78沒加malloc也沒提醒?
    return ;
}