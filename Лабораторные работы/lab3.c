#include <stdio.h>
#include <stdlib.h>

// Функция для создания исходного файла с целыми числами
void createFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Ошибка при создании файла");
        exit(EXIT_FAILURE);
    }

    int numbers[] = {10, -3, 8, 15, -20, 7, 2, 0, -1};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", numbers[i]);
    }

    fclose(file);
}

// Функция для удаления из файла всех четных положительных чисел
void processFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка при открытии файла для чтения");
        exit(EXIT_FAILURE);
    }

    FILE* temp = fopen("temp.txt", "w");
    if (!temp) {
        perror("Ошибка при создании временного файла");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    int number;
    while (fscanf(file, "%d", &number) != EOF) {
        // Записываем только те числа, которые не являются четными положительными
        if (!(number > 0 && number % 2 == 0)) {
            fprintf(temp, "%d\n", number);
        }
    }

    fclose(file);
    fclose(temp);

    // Заменяем исходный файл временным
    if (remove(filename) != 0 || rename("temp.txt", filename) != 0) {
        perror("Ошибка при замене файла");
        exit(EXIT_FAILURE);
    }
}

// Функция для вывода содержимого файла
void displayFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка при открытии файла для чтения");
        exit(EXIT_FAILURE);
    }

    int number;
    printf("Содержимое файла '%s':\n", filename);
    while (fscanf(file, "%d", &number) != EOF) {
        printf("%d\n", number);
    }

    fclose(file);
}

// Основная программа
int main() {
    const char *filename = "numbers.txt";

    // Создание исходного файла
    createFile(filename);

    // Вывод содержимого исходного файла
    printf("Исходный файл:\n");
    displayFile(filename);

    // Обработка файла
    processFile(filename);

    // Вывод результата
    printf("\nФайл после обработки:\n");
    displayFile(filename);

    return 0;
}
