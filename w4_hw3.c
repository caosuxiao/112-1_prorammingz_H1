#include <stdio.h>

int main(){
    for(int k = 0; k < 7; k+=3){
        for(int j = 1; j <= 9; j++){
            for(int i = 1; i < 4; i++)
                printf("%d x %d = %2d      ", i+k, j, (k+i)*j);
            if(j != 9 )
                printf("\n");
        }
        if(k < 4)
            printf("\n\n\n");
    }
}