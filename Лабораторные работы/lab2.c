#include <stdio.h>

#define MAX_STR_LEN 300

// Функция для проверки наличия цифр в слове
int hasDigits(const char *word) {
    while (*word) {
        if (*word >= '0' && *word <= '9') {
            return 1;
        }
        word++;
    }
    return 0;
}

// Функция для удаления всех символов, кроме цифр
void extractDigits(const char *word, char *result) {
    while (*word) {
        if (*word >= '0' && *word <= '9') {
            *result++ = *word;
        }
        word++;
    }
    *result = '\0'; // Завершаем строку
}

// Основная программа
int main() {
    char str[MAX_STR_LEN];
    char word[MAX_STR_LEN];
    int i = 0, j = 0;

    // Ввод строки
    printf("Введите строку (не более %d символов):\n", MAX_STR_LEN - 1);
    fgets(str, MAX_STR_LEN, stdin);

    // Вывод исходной строки
    printf("Исходная строка:\n%s", str);

    printf("Результат:\n");

    // Разбор строки на слова
    while (str[i] != '\0') {
        if (str[i] != ' ' && str[i] != '.') {
            word[j++] = str[i]; // Добавляем символ в текущее слово
        } else {
            if (j > 0) { // Если слово не пустое
                word[j] = '\0'; // Завершаем строку
                j = 0;

                // Обрабатываем слово, если оно не последнее и содержит цифры
                if (str[i] != '.' && hasDigits(word)) {
                    char digits[MAX_STR_LEN];
                    extractDigits(word, digits);
                    printf("%s\n", digits);
                }
            }
        }
        i++;
    }
    
    return 0;
}
