#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функция для создания исходного файла с целыми числами
void createFile(const char* filename, const int num_numbers) {
    double input_number;
    FILE* file = fopen(filename, "w");

    if (!file) {
        perror("Ошибка при создании файла");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_numbers; i++) {
        puts("Введите само число (целое) :");
        scanf("%lf", &input_number);

        if (input_number != (int)input_number) {
            puts("Число не целое");
            exit(EXIT_FAILURE);
        }

        fprintf(file, "%d\n", (int)input_number);
    }

    fclose(file);
}

// Функция для обработки файла и добавления количества квадратов нечётных чисел в начало
void processFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return;
    }

    int *buffer = malloc(sizeof(int) * 100);
    if (buffer == NULL) {
        perror("Ошибка выделения памяти");
        fclose(file);
        return;
    }

    int size = 0;
    int capacity = 100;
    int number;
    while (fscanf(file, "%d", &number) != EOF) {
        if (size >= capacity) {
            capacity *= 2;
            buffer = realloc(buffer, sizeof(int) * capacity);
            if (buffer == NULL) {
                perror("Ошибка выделения памяти");
                fclose(file);
                return;
            }
        }
        buffer[size++] = number;
    }
    fclose(file);

    // Подсчёт квадратов нечётных чисел
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (buffer[i] % 2 != 0) { // Нечётное число
            int root = (int)sqrt(buffer[i]);
            if (root * root == buffer[i]) {
                count++;
            }
        }
    }

    // Запись количества в начало файла
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Ошибка при открытии файла для записи");
        free(buffer);
        return;
    }

    fprintf(file, "%d\n", count);
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", buffer[i]);
    }

    fclose(file);
    free(buffer);
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

int main() {
    const char *filename = "numbers.txt";
    double num_numbers;

    puts("Введите количество чисел: ");
    scanf("%lf", &num_numbers);
    if (num_numbers <= 0 || num_numbers != (int)num_numbers) {
        printf("*Ошибка:* Число должно быть натуральным.\n");
        return 0;
    }
    createFile(filename, (int)num_numbers);

    printf("Исходный файл:\n");
    displayFile(filename);

    processFile(filename);

    printf("\nФайл после обработки:\n");
    displayFile(filename);

    return 0;
}
