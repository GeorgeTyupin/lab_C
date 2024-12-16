#include <stdio.h>
#include <string.h>
#include <ctype.h>

void extractWord(const char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= '0' && input[i] <= '9')) {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
}

int isWord(const char *str) {
    return str[0] == '[' && str[strlen(str) - 1] == ']';
}

int isValidWord(const char *word) {
    if ( strlen(word) > 10)
        return 0;

    for (int i = 0; word[i] != '\0'; i++) {
        if (!isalnum(word[i])) { // Если символ не является буквой или цифрой
            return 0; // Невалидное слово
        }
    }
    return 1; // Валидное слово
}

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
    }

    return count;
}

int checkBrackets(const char *str) {
    int balance = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '[') {
            balance++;
        } else if (str[i] == ']') {
            balance--;
        }
    }
    return balance == 0; // Баланс должен быть нулевым
}

int main() {
    char input[300];
    char output[300];

    printf("Введите строку:\n");
    fgets(input, 300, stdin);

    printf("Исходная строка: %s\n", input);
    
    int wordCount = countWords(input);
    if (wordCount < 1 || wordCount > 30) {
        printf("Ошибка: количество слов в строке должно быть от 1 до 30! Вы ввели %d слов.\n", wordCount);
        return 1;
    }

    if (!checkBrackets(input)) {
        printf("Ошибка: некорректный ввод квадратных скобок.\n");
        return 1;
    }

    // Находим первую точку и обрезаем строку до неё
    char *dot = strchr(input, '.');
    if (dot != NULL) {
        *dot = '\0'; // Обрезаем строку на первой точке
    } else {
        puts("Строка не содержит точку");
        return 0;
    }

    size_t len = strlen(input);
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    char *token = strtok(input, " ");
    printf("Найденные слова:\n");
    while (token != NULL) {
        if (isWord(token)) {
            extractWord(token, output); // Извлекаем слово внутри скобок

            if (isValidWord(output)) {
                printf("%s\n", output);
            } else {
                printf("Слово '%s' невалидно: превышена длина или содержит недопустимые символы.\n", output);
            }
        }
        token = strtok(NULL, " ");
    }

    return 0;
}
