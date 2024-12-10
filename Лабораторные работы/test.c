#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    // 117 + 70*256 + 7*256^2 + 0*256^3
    int g = 476789;
    char *ptr = (char *)&g;

    // for(int i = 0;i < sizeof(g); ++i) {
    //     printf("%d ", *++ptr);
    // }

    // printf("\n");
    // int x = *ptr++;
    // int x = *++ptr;
    // int x = (*ptr)++;
    // int x = ++(*ptr);

    // printf("x = %d, g = %d, *ptr = %d\n", x, g, *ptr);
    
    return 0;
}
