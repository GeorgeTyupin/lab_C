#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Функция для удаления всех цифр из слова
void removeDigits(const char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i])) { // Если символ не является цифрой
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
}

// Функция для проверки, состоит ли слово только из латинских букв и/или цифр
int isValidWord(const char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!isalnum(word[i])) { // Если символ не является буквой или цифрой
            return 0; // Невалидное слово
        }
    }
    return 1; // Валидное слово
}

// Функция для подсчёта количества слов в строке
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

int main() {
    char input[300];
    char copy[300];
    char processedWord[300];

    printf("Введите строку:\n");
    fgets(input, 300, stdin);

    // Удаляем символ перевода строки, если он есть
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    // Проверяем наличие точки в конце строки
    char *dot = strchr(input, '.');
    if (dot == NULL || *(dot + 1) != '\0') {
        printf("Ошибка: строка должна оканчиваться точкой.\n");
        return 1;
    }

    // Убираем точку для дальнейшей обработки
    *dot = '\0';

    // Подсчитываем количество слов
    int wordCount = countWords(input);
    if (wordCount < 1 || wordCount > 30) {
        printf("Ошибка: количество слов в строке должно быть от 1 до 30! Вы ввели %d слов.\n", wordCount);
        return 1;
    }

    // Копируем строку для работы с токенами
    strcpy(copy, input);

    char *token = strtok(copy, " ");
    char *lastWord = NULL;

    // Находим последнее слово
    while (token != NULL) {
        lastWord = token;
        token = strtok(NULL, " ");
    }

    if (lastWord == NULL) {
        printf("Ошибка: строка не содержит слов.\n");
        return 1;
    }

    // Обрабатываем слова, отличные от последнего
    printf("Результат:\n");
    strcpy(copy, input);
    token = strtok(copy, " ");

    while (token != NULL) {
        // Проверяем длину слова
        if (strlen(token) > 10) {
            printf("Ошибка: слово \"%s\" слишком длинное (больше 10 символов)!\n", token);
            token = strtok(NULL, " ");
            continue;
        }

        // Проверяем, что слово состоит только из допустимых символов
        if (!isValidWord(token)) {
            printf("Ошибка: слово \"%s\" содержит недопустимые символы!\n", token);
            token = strtok(NULL, " ");
            continue;
        }

        // Если слово не совпадает с последним
        if (strcmp(token, lastWord) != 0) {
            removeDigits(token, processedWord); // Удаляем цифры из слова
            printf("%s\n", processedWord);
        }
        token = strtok(NULL, " ");
    }

    return 0;
}
