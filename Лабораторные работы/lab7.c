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

int isValidWord(const char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!isalnum(word[i])) { // Если символ не является буквой или цифрой
            return 0; // Невалидное слово
        }
    }
    return 1; // Валидное слово
}

int main() {
    char input[300];
    char copy[300];
    char output[300];

    printf("Введите строку:\n");
    fgets(input, 300, stdin);

    // Находим первую точку и обрезаем строку до неё
    char *dot = strchr(input, '.');
    if (dot != NULL) {
        *dot = '\0'; // Обрезаем строку на первой точке
    }

    size_t len = strlen(input);
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    printf("Исходная строка (без части после точки): %s\n", input);

    strcpy(copy, input);

    char *token = strtok(copy, " ");
    char *lastWord = NULL;

    // Находим последнее слово
    while (token != NULL) {
        lastWord = token;
        token = strtok(NULL, " ");
    }

    strcpy(copy, input);
    token = strtok(copy, " ");

    printf("Слова, содержащие цифры (преобразованные):\n");
    while (token != NULL) {
        // Если длина слова больше 10, выводим ошибку
        if (strlen(token) > 10) {
            printf("Ошибка: слово \"%s\" слишком длинное (больше 10 символов)!\n", token);
            token = strtok(NULL, " ");
            continue;
        }

        // Проверяем, что слово состоит только из букв и цифр
        if (!isValidWord(token)) {
            printf("Ошибка: слово \"%s\" содержит недопустимые символы!\n", token);
            token = strtok(NULL, " ");
            continue;
        }

        // Если текущее слово - это последнее слово перед точкой, игнорируем его
        if (token == lastWord) {
            token = strtok(NULL, " ");
            continue;
        }

        // Если в слове есть цифры, преобразуем его
        processWord(token, output);
        if (strlen(output) > 0) { // Если в слове есть цифры
            printf("%s\n", output);
        }
        token = strtok(NULL, " ");
    }
    return 0;
}
