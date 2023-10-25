#include <stdio.h>

int main(){
    int i = 13;
    setbuf(stdout,NULL);
    // setbuf(stdin, NULL);
     scanf("%d", &i);
    printf("hello world\n");
    printf("i = %d", i);
    return 0;
}