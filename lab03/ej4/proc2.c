#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int *y) {
    if (x>=0)
        *y = x;
    else
        *y = -x;
}

int main(void) {
    int a, res, r;
    res = 0;
    a = -98;
    absolute(a, &res);
    printf("%d \n",res);
    r = 0;
    return r;
    return EXIT_SUCCESS;
}

