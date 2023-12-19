#include <stdio.h>
#include <stdlib.h>
#include "forHW8.h"

#define IN_BOARD(x, y) (x >= 0 && x < MAX && y >= 0 && y < MAX)

int maze[MAX][MAX] ={
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 0, 0, 0, 1, 1, 0, 1, 1, 0, 1 },
  { 1, 0, 1, 1, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
  { 1, 1, 1, 0, 1, 1, 0, 1, 1, 1 },
  { 1, 0, 1, 1, 1, 0, 0, 1, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
  { 1, 0, 1, 1, 1, 1, 1, 0, 0, 1 },
  { 1, 0, 0, 0, 1, 0, 0, 0, 1, 1 },
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
    int direc[4][2] = {{-1, 0}, {0, 1}, (1, 0), {0, -1}};
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
    while(temp.x == -1 || temp.y == -1)
        temp = Pop(stack);
    return temp;
}

void main(){
    pos_t * exit = (pos_t *)malloc(sizeof(pos_t));
    stack_t * stack = (stack_t *)malloc(sizeof(stack_t));
    printf("I'm hereA.\n");
    pos_t mouse = InAndOut(exit);
    printf("I'm hereB.\n");
    int i = 0;
    printf("I'm hereC.\n");
    while (mouse.x != exit->x && mouse.y != exit->y){
        Direction(mouse, stack);
        mouse = Move(stack);
        printf("This is %d\n", i);
        i++; 
    }
    printf("I'm hereD.\n");
    free(exit), free(stack);
    printf("I'm hereE.\n");
    // 沒加malloc也沒提醒?
    return ;
}