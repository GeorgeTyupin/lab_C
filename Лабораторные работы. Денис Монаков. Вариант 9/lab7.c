#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Функция для сравнения строк в qsort
int compareStrings(const void *a, const void *b) {
    return strcmp(*(char **)a, *(const char **)b);
}

int main() {
    char input[500];
    char *words[50]; // Массив указателей на слова
    int wordCount = 0;

    printf("Введите строку (до 30 слов, разделенных запятыми, с точкой в конце):\n");
    fgets(input, 500, stdin);

    // Удаление символа новой строки, если он есть
    size_t len = strlen(input);
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    // Проверка наличия точки в конце строки
    if (len < 2 || input[len - 1] != '.') {
        printf("Ошибка: строка должна заканчиваться точкой.\n");
        return 1;
    }

    // Убираем точку
    input[len - 1] = '\0';

    // Проверка на отсутствие запятых
    int hasComma = 0;
    for (size_t i = 0; i < len - 1; i++) {
        if (input[i] == ',') {
            hasComma = 1;
            if (i == 0 || input[i + 1] == ',' || input[i + 1] == '\0') {
                printf("Ошибка: некорректное расположение запятых в строке.\n");
                return 1;
            }
        } else if (isspace((unsigned char)input[i])) {
            printf("Ошибка: между словами не должно быть пробелов, только запятые.\n");
            return 1;
        }
    }

    if (!hasComma) {
        printf("Ошибка: строка должна содержать хотя бы одну запятую.\n");
        return 1;
    }

    // Разделение строки на слова по запятым
    char *token = strtok(input, ",");
    while (token != NULL) {
        // Убираем лишние пробелы в начале и конце слова
        while (isspace((unsigned char)*token)) token++;
        char *end = token + strlen(token) - 1;
        while (end > token && isspace((unsigned char)*end)) *end-- = '\0';

        // Проверяем длину слова
        if (strlen(token) < 1 || strlen(token) > 10) {
            printf("Ошибка: слово \"%s\" имеет недопустимую длину.\n", token);
            return 1;
        }

        words[wordCount++] = token;
        token = strtok(NULL, ",");
    }

    // Проверяем количество слов
    if (wordCount < 1 || wordCount > 30) {
        printf("Ошибка: количество слов в строке должно быть от 1 до 30! Вы ввели %d слов.\n", wordCount);
        return 1;
    }

    // Сортируем слова в алфавитном порядке
    qsort(words, wordCount, sizeof(char *), compareStrings);

    // Выводим отсортированные слова
    printf("Слова в алфавитном порядке:\n");
    for (int i = 0; i < wordCount; i++) {
        printf("%s\n", words[i]);
    }

    return 0;
}
