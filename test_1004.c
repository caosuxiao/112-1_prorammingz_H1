// LOOP範例 兩位數常除法


#include <stdio.h>

int main(){
    int k = 0;
    scanf("%d", &k);

    int count = 0, prev = 0, 
        toPrint = 0, digit = 0;
    
    while (scanf("%d", &digit) != EOF) {
        int value = prev * 10 + digit;
        toPrint = value / k;
        if (!(count == 0 && toPrint == 0)) {
            printf("%d\n", toPrint);
        }
        prev = value % k;
        count++;
    }
    if (count == 2 && toPrint == 0) 
        printf("0\n");
    
    
    

}