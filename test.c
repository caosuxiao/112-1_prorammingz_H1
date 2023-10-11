#include <stdio.h>

int main(){
    int i = 0;
    while(scanf("%d", &i) != EOF){
        printf("i = %d\n", i);
    }
    printf("ending");
}