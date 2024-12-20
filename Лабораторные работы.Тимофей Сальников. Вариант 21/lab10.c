#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void consoleCreateFile(const char* filename, const int num_numbers) {
    double input_number;
    FILE* file = fopen(filename, "w");

    if (!file) {
        perror("Ошибка при создании файла");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_numbers; i++) {
        puts("Введите само число:");
        scanf("%lf", &input_number);

        fprintf(file, "%d\n", (int)input_number);
    }

    fclose(file);
}

// Функция для обработки файла: вычисление суммы модулей и вставка перед элементом с номером N
void processFile(const char* filename, int N) {
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

    int number, count = 0;
    double sum = 0;

    // Вычисляем сумму модулей всех чисел
    while (fscanf(file, "%d", &number) != EOF) {
        sum += fabs(number);
        count++;
    }

    // Проверяем, что N корректно
    if (N < 1 || N > count) {
        printf("Ошибка: номер элемента N выходит за пределы диапазона (1-%d)\n", count);
        fclose(file);
        fclose(temp);
        remove("temp.txt");
        exit(EXIT_FAILURE);
    }

    rewind(file); // Возвращаемся в начало файла

    // Переписываем данные в новый файл, добавляя сумму перед элементом с номером N
    count = 0;
    while (fscanf(file, "%d", &number) != EOF) {
        count++;
        if (count == N) {
            fprintf(temp, "%.2f\n", sum); // Записываем сумму модулей
        }
        fprintf(temp, "%d\n", number);
    }

    fclose(file);
    fclose(temp);

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
    double d_number;
    printf("Содержимое файла '%s':\n", filename);
    while (fscanf(file, "%lf", &d_number) != EOF) {
        // Если число целое, выводим без десятичных знаков
        if (d_number == (int)d_number) {
            printf("%d\n", (int)d_number);
        } else {
            printf("%.2f\n", d_number);
        }
    }

    fclose(file);
}

int main() {
    int choice;
    const char *filename = "numbers.txt";
    double num_numbers, N;

    puts("Введите количество чисел: ");
    scanf("%lf", &num_numbers);
    if (num_numbers <= 0 || num_numbers != (int)num_numbers) {
        printf("*Ошибка:* Число должно быть натуральным.\n");
        return 0;
    }
    consoleCreateFile(filename, (int)num_numbers);



    printf("\nВведите номер элемента (N), перед которым нужно вставить сумму модулей: ");
    scanf("%lf", &N);
    if (N <= 0 || N != (int)num_numbers) {
        printf("*Ошибка:* Число должно быть целым и не меньше чем 1.\n");
        return 0;
    }

    printf("Исходный файл:\n");
    displayFile(filename);

    processFile(filename, N);
    
    printf("\nФайл после обработки:\n");
    displayFile(filename);

    return 0;
}
