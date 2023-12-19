#include <stdio.h>
#include "forHW8.h"

static int IsFull(stack_t * stack){
    return (stack->top == MAX * MAX);
}

static int IsEmpty(stack_t * stack){
    return (stack->top == -1);
}

pos_t Pop(stack_t * stack){
    if(IsEmpty(stack)){
        pos_t temp = {-1, -1};
        printf("can't pop any more!\n");
        return temp;
    } 
    pos_t temp = stack->element[stack->top];
    stack->top--;
    return temp;
    // return stack -> element[stack->top--];
}

void Push(stack_t * stack, pos_t elem){
    if(IsFull(stack)){
        printf("can't push any more!\n");
        return;
    } 
    stack->top++;
    stack->element[stack->top] = elem;
    return;
    // return stack->element[stack->++top] = elem;
} 