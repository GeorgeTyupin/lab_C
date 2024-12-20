#include <stdio.h>
#include <ctype.h>
#include <string.h>

int countWords(const char *str) {
    int count = 0;
    int inWord = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (!isspace(str[i]) && !inWord) {
            inWord = 1;
            count++;
        } else if (isspace(str[i])) {
            inWord = 0;
        }
        printf("слово str[i] = %d, inWord = %d, count = %d\n", str[i], inWord, count );
    }

    return count;
}


int main() {
    const char *s = "Привет форывпжлыф цукшжюаврсТБЫ";
    int x = countWords(s);
    printf("строка = %s, x = %d\n", s, x);
    
    return 0;
}
