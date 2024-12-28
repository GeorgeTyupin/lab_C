#include <stdio.h>
#include <stdlib.h>

void consoleCreateFile(const char* filename, const int num_numbers) {
    double input_number;
    FILE* file = fopen(filename, "w");

    if (!file) {
        perror("Ошибка при создании файла");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_numbers; i++) {
        puts("Введите само число (целое) :");
        scanf("%lf", &input_number);

        if ( input_number != (int)input_number ) {
            puts("Число не целое");
            exit(EXIT_FAILURE);
        }

        fprintf(file, "%d\n", (int)input_number);
    }

    fclose(file);
}

// Функция для обработки файла: вычисление произведения и вставка перед элементом с номером N
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
    long long product = 1;

    // Вычисляем произведение всех чисел
    while (fscanf(file, "%d", &number) != EOF) {
        product *= number;
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

    // Переписываем данные в новый файл, добавляя произведение перед элементом с номером N
    count = 0;
    while (fscanf(file, "%d", &number) != EOF) {
        count++;
        if (count == N) {
            fprintf(temp, "%lld\n", product); // Записываем произведение
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
    printf("Содержимое файла '%s':\n", filename);
    while (fscanf(file, "%d", &number) != EOF) {
        printf("%d\n", number);
    }

    fclose(file);
}

int main() {
    const char *filename = "numbers.txt";
    double num_numbers, N;

    puts("Введите количество чисел: ");
    scanf("%lf", &num_numbers);
    if (num_numbers <= 0 || num_numbers != (int)num_numbers) {
        printf("*Ошибка:* Число должно быть натуральным.\n");
        return 1;
    }
    consoleCreateFile(filename, num_numbers);

    printf("\nВведите номер элемента (N), перед которым нужно вставить произведение: ");
    scanf("%lf", &N);
    if (N > num_numbers) {
        printf("Ошибка. N не может быть больше чем число компонент в файле\n");
        return 1;
    }
    if (N <= 0 || N != (int)N) {
        printf("*Ошибка:* Число должно быть целым и не меньше чем 1.\n");
        return 1;
    }

    printf("Исходный файл:\n");
    displayFile(filename);

    processFile(filename, (int)N);

    printf("\nФайл после обработки:\n");
    displayFile(filename);

    return 0;
}
