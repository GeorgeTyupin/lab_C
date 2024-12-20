#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Функция для проверки, содержит ли слово цифры
int containsDigit(const char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (isdigit(word[i])) {
            return 1; // Слово содержит хотя бы одну цифру
        }
    }
    return 0; // Цифр нет
}

// Функция для переворачивания строки
void reverseWord(const char *input, char *output) {
    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        output[i] = input[len - 1 - i];
    }
    output[len] = '\0';
}

int main() {
    char input[300];
    char copy[300];
    char reversed[300];

    printf("Введите строку:\n");
    fgets(input, 300, stdin);

    // Удаление символа новой строки, если он есть
    size_t len = strlen(input);
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    printf("Исходная строка: %s\n", input);

    // Проверка на количество слов
    int wordCount = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isspace(input[i]) && (i == 0 || isspace(input[i - 1]))) {
            wordCount++;
        }
    }

    if (wordCount < 1 || wordCount > 30) {
        printf("Ошибка: количество слов в строке должно быть от 1 до 30! Вы ввели %d слов.\n", wordCount);
        return 1;
    }

    // Поиск точки и обрезка строки
    char *dot = strchr(input, '.');
    if (dot != NULL) {
        *dot = '\0';
    } else {
        printf("Ошибка: строка должна заканчиваться точкой.\n");
        return 1;
    }

    strcpy(copy, input);
    char *token = strtok(copy, " ");

    printf("Слова, содержащие цифры (перевернутые):\n");
    while (token != NULL) {
        // Проверка длины слова
        if (strlen(token) > 10) {
            printf("Ошибка: слово \"%s\" слишком длинное (больше 10 символов)!\n", token);
            token = strtok(NULL, " ");
            continue;
        }

        // Проверка на допустимые символы
        int valid = 1;
        for (int i = 0; token[i] != '\0'; i++) {
            if (!isalnum(token[i])) {
                valid = 0;
                break;
            }
        }
        if (!valid) {
            printf("Ошибка: слово \"%s\" содержит недопустимые символы!\n", token);
            token = strtok(NULL, " ");
            continue;
        }

        // Если слово содержит цифры, переворачиваем его
        if (containsDigit(token)) {
            reverseWord(token, reversed);
            printf("%s\n", reversed);
        }

        token = strtok(NULL, " ");
    }

    return 0;
}
