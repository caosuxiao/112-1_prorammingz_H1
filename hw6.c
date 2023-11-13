#include <stdio.h>
#include <stdlib.h>
#define IN_BOARD(x, y) (x >= 0 && x <= 7 && y >= 0 && y <= 7)
#define IS_EMPTY(x) (x == 0)

// int _RecordW[64][3] = {-1};
int _BandW[2][64][3] = {-1};
int Direction(int board[8][8], int x, int y, int chess,int flip){
    int sum = 0;  
    int direc[8][2] = {{-1, 0}, {-1, +1}, {0, +1}, {+1, +1},
                       {+1, 0}, {+1, -1}, {0, -1}, {-1, -1}};
    for(int i=0; i<8; i++){
        int tx = x + direc[i][0], ty = y + direc[i][1];
        if(IN_BOARD(tx, ty) && !IS_EMPTY(board[tx][ty])){
            int n = YesOrNo(board, chess, x, y, direc[i][0], direc[i][1]);
            sum += n;
            if(flip && n > 0){
                board[x][y] = chess;
                printf("ready to flip...\n");
                Flip(board, x, y, direc[i][0], direc[i][1], n); //wrong position
            }
        }
    }
    if(!flip){   
        if(sum > 0){
            _BandW[chess - 1][x * 8 + y][0] = x, 
            _BandW[chess - 1][x * 8 + y][1] = y, 
            _BandW[chess - 1][x * 8 + y][2] = sum;
            return 1;
        }
        return 0;
    }
    if(flip) return sum;
}   //Direction
int YesOrNo(int board[8][8], int chess, int x, int y, int dx, int dy){   //找單一方向
    x = x + dx, y = y + dy;
    int n = 0, target = 3 - chess, flag = 1;
    while(board[x][y] == target){
        if(!IN_BOARD(x, y)) break;    
        x += dx, y += dy, n++;
    }
    if(!board[x][y] || !IN_BOARD(x, y)) return 0;
    else return n;
}   //YesOrNo
void ClearAll(){
    for(int i=0; i<64; i++){
        _BandW[0][i][0] = _BandW[0][i][1] = _BandW[0][i][2] = -1;
        _BandW[1][i][0] = _BandW[1][i][1] = _BandW[1][i][2] = -1;
    }
        // _RecordW[i][0] = _RecordW[i][1] = _RecordW[i][2] = -1;
}   //ClearAll
int Most(int board[8][8]){
    int max = 0, x = 0, y = 0;
    for(int i=0; i<64; i++)
        if(_BandW[1][i][2] > max)
            max = _BandW[1][i][2], x = i / 8, y = i % 8;
    printf("%d %d (n = %d)\n", x, y, max);
    Direction(board, x, y, 2, 1); 
    return max;    
}   //Most
int CheckNext(int board[8][8],int chess){
    int flag = 0;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            if(IS_EMPTY(board[i][j]))
                if(Direction(board, i, j, chess, 0)){
                    if(chess == 1) return 1;    //for black
                    flag = 1;
                }
    if(flag) return 1;  //for white
    return 0;
}   //CheckNext
void Flip(int board[8][8], int x, int y,int dx, int dy, int n){
    printf("READY dx: %d, dy: %d\n", dx, dy);
    for(int i=1; i<=n; i++){
        if(board[x + i * dx][y + i * dy] == 1)
            board[x + i * dx][y + i * dy] = 2;
        else board[x + i * dx][y + i * dy] = 1;
    }
    printf("flipped %d chessmen\n", n);
}   //Flip
void PrintBoard(int board[8][8]){
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++)
            printf("%d ", board[i][j]);
        printf("\n");
    }  
    // printf("\n");
}   //PrintBoard
int CheckBoard(int board[8][8]){
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            if(IS_EMPTY(board[i][j]))
                return 1;
    return 0;
}   //CheckBoard
void Winner(int board[8][8]){
    int sumB = 0, sumW = 0;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++){
            if(board[i][j] == 1) sumB++;
            else if(board[i][j] == 2) sumW++;
        }
    if(sumB > sumW) printf("Black wins! %d:%d", sumB, sumW);
    else if(sumB < sumW) printf("White wins! %d:%d", sumW, sumB);
    else printf("Tie! %d:%d", sumB, sumW);
}   //Winner
void main(){
    // int board[8][8] = {0};
    int x, y ,chess, round = 0, user, computer, play = 1;
    char first;
    int board[8][8] = {{0, 0, 2, 0, 2, 0, 2, 0},
                       {1, 0, 1, 2, 1 ,2, 0, 0},
                       {1, 0, 2, 2, 2 ,2, 0, 0},
                       {1, 2, 1, 1, 1, 1, 0, 0},
                       {0, 0, 2, 1, 1, 0, 0, 0},
                       {0, 0, 1, 2, 1, 2, 0, 0},
                       {0, 0, 0, 0, 2, 0, 0, 0},                                                                                                              
                       {0, 0, 1, 1, 1, 0, 0, 0}}; //pic1
    // for(int i=0; i<8; i++)
    //     for(int j=0; j<8; j++)
    //         scanf("%d", &board[i][j]);
    printf("Do you want to go first?('y' or 'n'; black is first)\n");
    scanf("%c", &first);
    if(first == 'y') 
        user = 1, computer = 2, round = 1;  //round & 1 為0就是user time
    else if(first == 'n') 
        user = 2, computer = 1;  //round & 1 為0就是user time
    else return;
    // !!!attention!!! 要123行到129行的話 chess要改
    while(play){
        int flagU = 0, flagC = 0, n;
        ClearAll(), PrintBoard(board);
        if(round & 1){
            if(CheckNext(board, 1)){
                printf("your turn: ");
                scanf("%d %d", &x, &y);
                if(x > 7 || y > 7) break;
                if(IS_EMPTY(board[x][y])){
                    n = Direction(board, x, y, 1, 1);
                    printf("U get %d chessmen\n", n);
                }
            }
            else{
                printf("U can't move\n");
                flagU = round;
            } 
        }   //user time
        else{
            if(CheckNext(board,2)){
                printf("Computer's turn: ");
                n = Most(board);
                printf("Computer gets %d chessmen\n", n);   
            } 
            else{
                printf("Computer can't move\n");
                flagC = round;
            } 
        }   //computer time
        round++;
        if(abs(flagC - flagU) == 1 || !CheckBoard(board)){
            printf("The game ends\n");
            break;
        }
    }
    Winner(board);
}