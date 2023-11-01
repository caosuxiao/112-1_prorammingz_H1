#include <stdio.h>
#define IN_BOARD(x, y) (x >= 0 && x <= 7 && y >= 0 && y <= 7)
#define IS_EMPTY(x) (x == 0)

void direction(int board[8][8], int x, int y, int chess){
    int sum = 0;  
    int direc[8][2] = {{-1, 0}, {-1, +1}, {0, +1}, {+1, +1},
                       {+1, 0}, {+1, -1}, {0, -1}, {-1, -1}};
    for(int i=0; i<8; i++){
        int tx = x + direc[i][0], ty = y + direc[i][1];
        if(IN_BOARD(tx, ty) && !IS_EMPTY(board[tx][ty]))
            if(YesOrNo(board, chess,x, y, direc[i][0], direc[i][1])){
                sum += YesOrNo(board, chess, x, y, direc[i][0], direc[i][1]);
                int n = YesOrNo(board, chess, x, y, direc[i][0], direc[i][1]);
                flip(board, chess, x, y, direc[i][0], direc[i][1], n);
            }
    }
    if(sum > 0){
        board[x][y] = chess;
        printf("You got %d chesses.\n", sum);
    } 
}   //direction
int YesOrNo(int board[8][8], int chess, int x, int y, int dx, int dy){
    x = x + dx, y = y + dy;
    int n = 0, target = 3 - chess;
    while(board[x][y] == target){
        if(!IN_BOARD(x, y)) break;    //可以直接在這return? yes
        x += dx, y += dy, n++;
    }
    if(!board[x][y] || !IN_BOARD(x, y)) return 0;
    else return n;
}   //YesOrNo
void flip(int board[8][8], int chess, int x, int y,int dx, int dy, int n){
    for(int i=1; i<=n; i++)
        board[x + i * dx][y + i * dy] = chess;
}  
void PrintBoard(int board[8][8]){
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++)
            printf("%d ", board[i][j]);
        printf("\n");
    }   
}
void main(){
    printf("======================This is a program that flips the board once. w ======================\n");
    int board[8][8] = {0}, x, y ,chess;
    // int x, y ,chess;
    // int board[8][8] = {{1, 0, 1, 0, 0, 0, 0, 0},
    //                    {0, 1, 1, 0, 2 ,0, 0, 0},
    //                    {0, 2, 1, 1, 2 ,1, 0, 0},
    //                    {0, 1, 1, 1, 2, 1, 1, 0},
    //                    {0, 0, 1, 1, 2, 0, 1, 0},
    //                    {0, 2, 2, 2, 2, 2, 2, 2},
    //                    {0, 0, 0, 0, 0, 0, 1, 0},                                                                                                              
    //                    {0, 0, 0, 0, 1, 1, 1, 1}};   //pic7
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            scanf("%d", &board[i][j]);
    printf("where do u want to go and what's your color?\n");
    scanf("%d %d %d", &x, &y, &chess);
    if(IS_EMPTY(board[x][y])){
        direction(board, x, y, chess);
        PrintBoard(board);
    }  
}