#include <stdio.h>

int main(){
    for(int i = 1; i < 4; i++){
        for(int j = 1; j < 10; j++){
            for(int k = 0; k < 7; k+=3)
                printf("%d x %d = %2d      ", i+k, j, (k+i)*j);
            if(j != 9)
                printf("\n");
        }
        if(i < 3)
            printf("\n\n\n");
    }
}