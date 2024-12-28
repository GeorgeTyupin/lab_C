#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Для функции islower

// Определение структуры узла двусвязного списка
typedef struct Node {
    char *word;            // Указатель на строку (слово)
    struct Node *prev;     // Указатель на предыдущий узел
    struct Node *next;     // Указатель на следующий узел
} Node;

// Функция для создания нового узла списка
Node* create_node(const char *word) {
    Node *new_node = (Node *)malloc(sizeof(Node)); // Выделяем память для узла
    new_node->word = strdup(word); // Копируем строку в новый узел
    new_node->prev = NULL; // Устанавливаем предыдущий указатель в NULL
    new_node->next = NULL; // Устанавливаем следующий указатель в NULL
    return new_node;       // Возвращаем указатель на созданный узел
}

// Функция для добавления слова в конец списка
void add_node(Node **head, const char *word) {
    Node *new_node = create_node(word); // Создаем новый узел
    if (*head == NULL) { // Если список пуст
        *head = new_node; // Новый узел становится головой списка
    } else {
        Node *temp = *head; // Указатель для перемещения по списку
        while (temp->next != NULL) { // Ищем последний узел
            temp = temp->next;
        }
        temp->next = new_node; // Добавляем новый узел в конец
        new_node->prev = temp; // Устанавливаем обратную связь
    }
}

// Функция для вывода всех слов из списка
void print_list(Node *head) {
    Node *temp = head; // Указатель для перемещения по списку
    while (temp != NULL) { // Пока не достигли конца списка
        printf("%s ", temp->word); // Выводим слово
        temp = temp->next; // Переходим к следующему узлу
    }
    printf("\n"); // Завершаем строку
}

// Функция для удаления слов, начинающихся с заданной буквы
void remove_words_starting_with(Node **head, char letter) {
    Node *temp = *head; // Указатель для перемещения по списку
    while (temp != NULL) { // Пока есть узлы в списке
        if (temp->word[0] == letter) { // Если слово начинается с заданной буквы
            Node *to_delete = temp; // Сохраняем указатель на текущий узел
            if (temp->prev) { // Если узел не первый
                temp->prev->next = temp->next; // Перенаправляем следующий указатель предыдущего узла
            } else { // Если узел первый
                *head = temp->next; // Голова списка смещается на следующий узел
            }
            if (temp->next) { // Если узел не последний
                temp->next->prev = temp->prev; // Перенаправляем предыдущий указатель следующего узла
            }
            temp = temp->next; // Переходим к следующему узлу
            free(to_delete->word); // Освобождаем память для строки
            free(to_delete);       // Освобождаем память для узла
        } else {
            temp = temp->next; // Переходим к следующему узлу
        }
    }
}

// Проверка на корректность строки (только строчные латинские буквы, пробелы и точка)
int validate_string(const char *str) {
    int length = strlen(str);

    // Проверка, заканчивается ли строка точкой
    if (length == 0 || str[length - 1] != '.') {
        return 0; // Строка не заканчивается точкой
    }

    // Проверка символов строки (игнорируем последнюю точку)
    for (int i = 0; i < length - 1; i++) {
        if (!islower(str[i]) && str[i] != ' ') {
            return 0; // Найден недопустимый символ
        }
    }

    return 1; // Строка корректна
}

int main() {
    char input[1000]; // Буфер для ввода строки
    char letter;      // Буква, по которой будет производиться фильтрация

    // Ввод строки от пользователя
    printf("Введите строку: ");
    fgets(input, sizeof(input), stdin); // Считываем строку с пробелами

    // Удаляем символ новой строки, если он есть
    input[strcspn(input, "\n")] = '\0';

    // Проверяем строку на корректность
    if (!validate_string(input)) {
        printf("Ошибка: строка должна состоять только из строчных латинских букв, пробелов и содержать точку в конце.\n");
        return 1; // Завершаем программу с кодом ошибки
    }

    // Удаляем точку ('.') в конце строки
    input[strcspn(input, ".")] = '\0';

    // Ввод буквы для фильтрации
    printf("Введите букву для удаления слов, начинающихся с неё: ");
    scanf(" %c", &letter);

    Node *head = NULL; // Указатель на начало списка (изначально NULL)

    // Разделяем строку на слова с помощью strtok и добавляем их в список
    char *word = strtok(input, " "); // Получаем первое слово
    while (word != NULL) { // Пока есть слова
        add_node(&head, word); // Добавляем слово в список
        word = strtok(NULL, " "); // Получаем следующее слово
    }

    // Выводим исходный список
    printf("Исходный список: ");
    print_list(head);

    // Удаляем слова, начинающиеся с заданной буквы
    remove_words_starting_with(&head, letter);

    // Выводим список после модификации
    printf("Список после модификации: ");
    print_list(head);

    // Освобождаем память, выделенную под список
    Node *temp;
    while (head != NULL) {
        temp = head;        // Сохраняем текущий узел
        head = head->next;  // Переходим к следующему узлу
        free(temp->word);   // Освобождаем память для строки
        free(temp);         // Освобождаем память для узла
    }

    return 0; // Успешное завершение программы
}
