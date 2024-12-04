#include <stdio.h>
#include <string.h>
#include <ctype.h>

void processWord(const char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (isdigit(input[i])) {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
}

int main() {
    char input[300];
    char copy[300];
    char output[300];

    printf("Введите строку:\n");
    fgets(input, 300, stdin);

    size_t len = strlen(input);
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    printf("Исходная строка: %s\n", input);

    strcpy(copy, input);

    char *token = strtok(copy, " ");
    char *lastWord = NULL;

    while (token != NULL) {
        lastWord = token;
        token = strtok(NULL, " ");
    }

    strcpy(copy, input);
    token = strtok(copy, " ");

    printf("Слова, содержащие цифры (преобразованные):\n");
    while (token != NULL && token != lastWord) {
        if (strcmp(token, lastWord) != 0) { // Игнорируем последнее слово
            processWord(token, output);
            if (strlen(output) > 0) { // Если в слове есть цифры
                printf("%s\n", output);
            }
        }
        token = strtok(NULL, " ");
    }
    return 0;
}
