#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    char x[9] = "shawanyi\n";
    x[8]=0;
    printf("%d\n",strlen(x));
    printf("%s\n", x);
}