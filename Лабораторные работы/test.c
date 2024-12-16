#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    // 117 + 70*256 + 7*256^2 + 0*256^3
    double x = 1.2;


    printf("x = %d", (int)x % 2 == 0);
    
    return 0;
}
