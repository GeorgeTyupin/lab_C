#include <stdio.h>

void split_line(char *str) {
    printf("Введите строку: ");
    fgets(*str, sizeof(*str), stdin);
}

int main(void) {
    char str[300];
    // for (int i = 0; str[i] != '\0'; i++) {
    //     printf("%c", str[i]);
    // }
    // return 0;
    split_line(&str);
    printf("Полученная строка %s", *str);
}