#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция для создания исходного файла с целыми числами
void createFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Ошибка при создании файла");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    int num_numbers = rand() % 11 + 5;

    for (int i = 0; i < num_numbers; i++) {
        int random_number = rand() % 101 - 50;  // [ -50, 50 ]
        fprintf(file, "%d\n", random_number);
    }

    fclose(file);
}

// Функция для удаления из файла всех четных положительных чисел
void processFile(const char* filename) {
    /*FILE* file = fopen(filename, "r");
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
        if (!(number > 0 && number % 2 == 0)) {
            fprintf(temp, "%d\n", number);
        }
    }

    fclose(file);
    fclose(temp);

    if (remove(filename) != 0 || rename("temp.txt", filename) != 0) {
        perror("Ошибка при замене файла");
        exit(EXIT_FAILURE);
    }*/
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

    int max_value = buffer[0];
    int last_max_pos = 0;
    for (int i = 1; i < size; i++) {
        if (buffer[i] >= max_value) {
            max_value = buffer[i];
            last_max_pos = i;
        }
    }

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Ошибка при открытии файла для записи");
        free(buffer);
        return;
    }

    for (int i = 0; i < size; i++) {
        if (i <= last_max_pos || buffer[i] <= 0) {
            fprintf(file, "%d\n", buffer[i]);
        }
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
    createFile(filename);

    printf("Исходный файл:\n");
    displayFile(filename);

    processFile(filename);

    printf("\nФайл после обработки:\n");
    displayFile(filename);

    return 0;
}
