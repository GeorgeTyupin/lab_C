#include <stdio.h>
#include <stdlib.h>

// Функция для создания исходного файла с целыми числами
void createFile(const char* filename, const int num_numbers) {
    int input_number;
    FILE* file = fopen(filename, "w");

    if (!file) {
        perror("Ошибка при создании файла");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_numbers; i++) {
        printf("Введите целое число: ");
        if (scanf("%d", &input_number) != 1) {
            puts("Ошибка ввода числа");
            fclose(file);
            exit(EXIT_FAILURE);
        }
        fprintf(file, "%d\n", input_number);
    }

    fclose(file);
}

// Функция для подсчёта чётных и нечётных чисел и добавления их в конец файла
void processFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла");
        return;
    }

    int even_count = 0;
    int odd_count = 0;
    int number;

    // Подсчёт чётных и нечётных чисел
    while (fscanf(file, "%d", &number) != EOF) {
        if (number % 2 == 0) {
            even_count++;
        } else {
            odd_count++;
        }
    }

    fclose(file);

    // Открытие файла для добавления данных
    file = fopen(filename, "a");
    if (!file) {
        perror("Ошибка открытия файла для записи");
        return;
    }

    fprintf(file, "Чётных чисел: %d\n", even_count);
    fprintf(file, "Нечётных чисел: %d\n", odd_count);

    fclose(file);
}

// Функция для вывода содержимого файла
void displayFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка при открытии файла для чтения");
        exit(EXIT_FAILURE);
    }

    int number;
    char line[256];
    printf("Содержимое файла '%s':\n", filename);
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

int main() {
    const char *filename = "numbers.txt";
    double num_numbers;

    printf("Введите количество чисел: ");
    scanf("%lf", &num_numbers);
    if (num_numbers <= 0 || num_numbers != (int)num_numbers) {
        printf("*Ошибка:* Число должно быть натуральным.\n");
        return 1;
    }

    createFile(filename, num_numbers);

    printf("\nИсходный файл:\n");
    displayFile(filename);

    processFile(filename);

    printf("\nФайл после обработки:\n");
    displayFile(filename);

    return 0;
}
