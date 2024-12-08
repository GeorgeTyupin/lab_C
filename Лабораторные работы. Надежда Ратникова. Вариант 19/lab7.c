#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void extractWord(const char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= '0' && input[i] <= '9')) {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
}

bool isWord(const char *str) {
    return str[0] == '[' && str[strlen(str) - 1] == ']';
}

int main() {
    char input[300];
    char output[300];

    printf("Введите строку:\n");
    fgets(input, 300, stdin);

    size_t len = strlen(input);
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    printf("Исходная строка: %s\n", input);

    char *token = strtok(input, " ");
    printf("Найденные слова:\n");
    while (token != NULL) {
        if (isWord(token)) {
            extractWord(token + 1, output); // Извлекаем слово внутри скобок
            output[strlen(output) - 1] = '\0'; // Убираем закрывающую скобку
            printf("%s\n", output);
        }
        token = strtok(NULL, " ");
    }

    return 0;
}
