#ifndef __FORHW8_H__
#define __FORHW8_H__


#define MAX 10

typedef struct pos{
    int x;
    int y;
} pos_t;

typedef struct stack{
    pos_t element[MAX * MAX];
    int top;
} stack_t;

pos_t Pop(stack_t * stack);
void Push(stack_t * stack, pos_t elem);


#endif