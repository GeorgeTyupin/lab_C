#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Функция для проверки, является ли строка числом
int isNumber(const char *str) {
    if (str == NULL || *str == '\0') return 0; // Пустая строка не является числом
    
    char *endptr;
    strtod(str, &endptr); // Преобразуем строку в число
    return *endptr == '\0'; // Проверяем, остались ли нечисловые символы
}

// Функция для создания исходного файла с целыми числами
void createFile(const char* filename, const int num_numbers) {
    double input_number; // Переменная для ввода числа
    char input_str[100]; // Строка для хранения пользовательского ввода
    FILE* file = fopen(filename, "w"); // Открываем файл для записи

    if (!file) { // Проверяем успешность открытия файла
        perror("Ошибка при создании файла");
        exit(EXIT_FAILURE); // Завершаем программу в случае ошибки
    }

    for (int i = 0; i < num_numbers; i++) {
        while (1) { // Бесконечный цикл для проверки ввода
            puts("Введите само число:"); // Просим пользователя ввести число
            scanf("%s", input_str); // Считываем ввод как строку

            // Проверяем, является ли ввод числом
            if (isNumber(input_str)) {
                input_number = atof(input_str); // Преобразуем строку в число
                fprintf(file, "%d\n", (int)input_number); // Записываем число в файл
                break; // Выходим из цикла, если ввод корректен
            } else {
                puts("Ошибка: введено не число. Попробуйте снова.");
            }
        }
    }

    fclose(file); // Закрываем файл
}

// Функция для обработки файла: удаляет числа после последнего максимального
void processFile(const char* filename) {
    FILE* file = fopen(filename, "r"); // Открываем файл для чтения
    if (file == NULL) { // Проверяем успешность открытия файла
        perror("Ошибка открытия файла");
        return;
    }

    int *buffer = malloc(sizeof(int) * 100); // Выделяем начальную память для хранения чисел
    if (buffer == NULL) { // Проверяем успешность выделения памяти
        perror("Ошибка выделения памяти");
        fclose(file);
        return;
    }

    int size = 0;       // Текущее количество чисел в буфере
    int capacity = 100; // Начальная ёмкость буфера
    int number;

    // Считываем числа из файла
    while (fscanf(file, "%d", &number) != EOF) {
        if (size >= capacity) { // Проверяем, нужно ли увеличить ёмкость буфера
            capacity *= 2; // Увеличиваем ёмкость вдвое
            buffer = realloc(buffer, sizeof(int) * capacity); // Перевыделяем память
            if (buffer == NULL) { // Проверяем успешность перевыделения
                perror("Ошибка выделения памяти");
                fclose(file);
                return;
            }
        }
        buffer[size++] = number; // Добавляем число в буфер
    }
    fclose(file); // Закрываем файл

    // Определяем последнее вхождение максимального числа
    int max_value = buffer[0];
    int last_max_pos = 0;
    for (int i = 1; i < size; i++) {
        if (buffer[i] >= max_value) {
            max_value = buffer[i];
            last_max_pos = i;
        }
    }

    file = fopen(filename, "w"); // Открываем файл для записи
    if (file == NULL) { // Проверяем успешность открытия файла
        perror("Ошибка при открытии файла для записи");
        free(buffer); // Освобождаем память
        return;
    }

    // Записываем только числа до последнего максимального включительно
    for (int i = 0; i < size; i++) {
        if (i <= last_max_pos || buffer[i] <= 0) { // Проверяем условие записи
            fprintf(file, "%d\n", buffer[i]); // Записываем число в файл
        }
    }

    fclose(file); // Закрываем файл
    free(buffer); // Освобождаем память
}

// Функция для вывода содержимого файла на экран
void displayFile(const char* filename) {
    FILE* file = fopen(filename, "r"); // Открываем файл для чтения
    if (!file) { // Проверяем успешность открытия файла
        perror("Ошибка при открытии файла для чтения");
        exit(EXIT_FAILURE); // Завершаем программу в случае ошибки
    }

    int number; // Переменная для хранения текущего числа
    printf("Содержимое файла '%s':\n", filename);
    while (fscanf(file, "%d", &number) != EOF) { // Считываем числа из файла
        printf("%d\n", number); // Выводим число
    }

    fclose(file); // Закрываем файл
}

int main() {
    const char *filename = "numbers.txt"; // Имя файла для работы
    char input_str[100]; // Строка для хранения пользовательского ввода
    int num_numbers; // Количество чисел, которые нужно ввести

    // Ввод количества чисел
    while (1) {
        puts("Введите количество чисел: ");
        scanf("%s", input_str); // Считываем ввод как строку

        // Проверяем, является ли ввод числом
        if (isNumber(input_str)) {
            num_numbers = atoi(input_str); // Преобразуем строку в целое число
            if (num_numbers > 0) { // Проверяем, является ли число натуральным
                break; // Выходим из цикла, если ввод корректен
            } else {
                puts("Ошибка: Число должно быть натуральным. Попробуйте снова.");
            }
        } else {
            puts("Ошибка: Введено не число. Попробуйте снова.");
        }
    }

    createFile(filename, num_numbers); // Создаём исходный файл

    printf("Исходный файл:\n");
    displayFile(filename); // Выводим содержимое исходного файла

    processFile(filename); // Обрабатываем файл

    printf("\nФайл после обработки:\n");
    displayFile(filename); // Выводим содержимое файла после обработки

    return 0; // Успешное завершение программы
}
