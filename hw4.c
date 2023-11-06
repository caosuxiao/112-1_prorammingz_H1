#include <stdio.h>
#define IN_BOARD(x, y) (x >= 0 && x <= 7 && y >= 0 && y <= 7)
#define IS_EMPTY(x) (x == 0)

int _BandW[2][64][3] = {-1};
// int isEmpty(int board[8][8]){
//     if(board[_x][_y] == 0) return 1; 
//     else return 0;
//     //以上兩行可寫成:
//     return (board[_x][_y] == 0);
// }        //短的副程式可以直接用寫成define
void direction(int board[8][8], int x, int y){
    int sum = 0;  
    int direc[8][2] = {{-1, 0}, {-1, +1}, {0, +1}, {+1, +1},
                       {+1, 0}, {+1, -1}, {0, -1}, {-1, -1}};
    for(int chess=1; chess<3; chess++){
        sum = 0;
        for(int i=0; i<8; i++){
            int tx = x + direc[i][0], ty = y + direc[i][1];
            if(IN_BOARD(tx, ty) && !IS_EMPTY(board[tx][ty]))
                if(YesOrNo(board, chess,x, y, direc[i][0], direc[i][1]) > 0)
                    sum += YesOrNo(board, chess, x, y, direc[i][0], direc[i][1]); 
        }
        if(sum > 0){
            if(chess == 1)
                _BandW[0][x * 8 + y][0] = x, _BandW[0][x * 8 + y][1] = y, _BandW[0][x * 8 + y][2] = sum;
            else
                _BandW[1][x * 8 + y][0] = x, _BandW[1][x * 8 + y][1] = y, _BandW[1][x * 8 + y][2] = sum;
        }
    }
}   //direction
int YesOrNo(int board[8][8], int chess, int x, int y, int dx, int dy){   //找單一方向
    x = x + dx, y = y + dy;
    int n = 0, target = 3 - chess, flag = 1;
    while(board[x][y] == target){
        if(!IN_BOARD(x, y)) break;    //可以直接在這return? yes
        x += dx, y += dy, n++;
    }
    if(!board[x][y] || !IN_BOARD(x, y)) return 0;
    else return n;
}   //YesOrNo
void PrintPosition(){
    printf("where white can go:\n");
    for(int i=0; i<64; i++)
        if(_BandW[1][i][2] > 0)
            printf("(%d, %d) ", _BandW[1][i][0], _BandW[1][i][1]);
    printf("\nwhere black can go:\n");
    for(int i=0, count=0; i<64; i++)
        if(_BandW[0][i][2] > 0)
            printf("(%d, %d) ", _BandW[0][i][0], _BandW[0][i][1]);
}   //PrintPosition
void main(){
    // int board[8][8] = {{0, 0, 2, 0, 2, 0, 2, 0},
    //                    {1, 0, 1, 2, 1 ,2, 0, 0},
    //                    {1, 0, 2, 2, 2 ,2, 0, 0},
    //                    {1, 2, 1, 1, 1, 1, 0, 0},
    //                    {0, 0, 2, 1, 1, 0, 0, 0},
    //                    {0, 0, 1, 2, 1, 2, 0, 0},
    //                    {0, 0, 0, 0, 2, 0, 0, 0},                                                                                                              
    //                    {0, 0, 1, 1, 1, 0, 0, 0}}; //pic1
    int board[8][8] = {0}; 
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            scanf("%d", &board[i][j]);
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            if(IS_EMPTY(board[i][j]))
                direction(board, i, j);
    PrintPosition();
    printf("\n(2, 6) can get %d chesses", _BandW[0][22][2]);
}