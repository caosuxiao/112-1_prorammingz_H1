#include <stdio.h>

int _chess, _x, _y;
int isEmpty(int board[8][8]){
    if(board[_x][_y] == 0) return 1; 
    else return 0;
}
void direction(int board[8][8]){
    int x = _x, y = _y, do_it = 0;  
    // 以下的8個if(-else)可以用loop代替
    // 如果要用do_it就不能用else if(if配else if只會在整個系統裡擇一進入)
    if((x-1 >= 0))                                   // top
        if(YesOrNo(board, -1, 0) != 0) do_it++;
    if((do_it == 0) && ((x-1 >= 0) && (y+1 <= 7)))   // top left
        if(YesOrNo(board, -1, +1) != 0) do_it++;
    if((do_it == 0) && (y+1 <= 7))                   // left
        if(YesOrNo(board, 0, +1) != 0) do_it++;
    if((do_it == 0) && ((x+1 <= 7) && (y+1 <= 7)))   // botton left
        if(YesOrNo(board, +1, +1) !=0) do_it++;
    if((do_it == 0) && (x+1 <= 7))                   // botton
        if(YesOrNo(board, +1, 0) != 0) do_it++;
    if((do_it == 0) && ((x+1 <= 7) && (y-1 >= 0)))   // botton right
        if(YesOrNo(board, +1, -1) != 0) do_it++;
    if((do_it == 0) && (y-1 >= 0))                   // right
        if(YesOrNo(board, 0, -1) != 0) do_it++;
    if((do_it == 0) && ((x-1 >= 0) && (y-1 >= 0)))   // top right
        if(YesOrNo(board, -1, -1) != 0) do_it++;
    if(do_it == 0) printf("It's a invalid coordinate!\n");
}   //direction
int YesOrNo(int board[8][8], int dx, int dy){
    int x = _x + dx, y = _y + dy, n = 0, target, flag = 1;
    if((board[x][y] == 0) || (board[x][y] == _chess)) return 0; //空格或自己的棋
    if(_chess == 1) target = 2;
    else target = 1;
    while(board[x][y] == target){
        if((x > 7) || (x < 0) || (y > 7) || (y < 0)){
            flag = 0; 
            break; 
        } 
        x += dx, y += dy, n++;
    }
    if(flag == 0){
        board[_x+n*dx][_y+n*dy] == 0;   //WTF??? this is for what???
        return 0;
    }   //出界
    else if((board[x][y] == 0)) return 0;   //沒被包夾
    else{
        printf("Nice! You find a good coordinate.\nn = %d\n", n);
        return n;
    } 
}   //YesOrNo
void main(){
    int board[8][8] = {0};
    printf("input a game\n");
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++) 
            scanf("%d", board[i][j]);
    printf("input a coordinate and a color(black = 1; white = 2)\n");
    // char c = '2' or 2 + '0'; (%d)1, (%d)50->(acsii); (%d)1, (%c)2;
    scanf("%d%d%d", &_x, &_y, &_chess);    //靠阿 要記得在變數前加'&', and % 和% 之間不需要逗號...
    if(isEmpty(board))
        direction(board);
    else printf("color%d occupied here!\n", board[_x][_y]);
}