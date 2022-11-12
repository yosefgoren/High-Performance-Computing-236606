#include <stdio.h>

char a[2][32];

#define toform(x) ((long int)(&(x)))%10000

int main(){
    printf("base[0][0] %ld, base[1][0] %ld, base[0][1] %ld\n", toform(a[0][0]), toform(a[1][0]), toform(a[0][1]));
    return 0;
}