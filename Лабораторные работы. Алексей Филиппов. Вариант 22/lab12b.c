#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

// Функция для поиска слова с минимальной длиной
Node* find_min_length_word(Node *head) {
    Node *min_node = head;
    while (head != NULL) {
        if (strlen(head->word) < strlen(min_node->word)) {
            min_node = head;
        }
        head = head->next;
    }
    return min_node;
}

// Функция для поиска слова с максимальной длиной
Node* find_max_length_word(Node *head) {
    Node *max_node = head;
    while (head != NULL) {
        if (strlen(head->word) > strlen(max_node->word)) {
            max_node = head;
        }
        head = head->next;
    }
    return max_node;
}

// Функция для проверки, одинаковы ли длины всех слов
int all_words_same_length(Node *head) {
    if (head == NULL) return 1; // Пустой список считается одинаковым

    size_t length = strlen(head->word);
    head = head->next;

    while (head != NULL) {
        if (strlen(head->word) != length) {
            return 0; // Найдено слово с другой длиной
        }
        head = head->next;
    }
    return 1; // Все слова имеют одинаковую длину
}

// Функция для вставки нового узла перед заданным узлом
void insert_before(Node **head, Node *node, const char *word) {
    Node *new_node = create_node(word);
    new_node->next = node;
    new_node->prev = node->prev;

    if (node->prev != NULL) {
        node->prev->next = new_node;
    } else {
        *head = new_node; // Если вставляем перед головой списка
    }

    node->prev = new_node;
}

// Функция для вывода всех слов из списка
void print_list(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%s ", temp->word);
        temp = temp->next;
    }
    printf("\n");
}

// Освобождение памяти, выделенной под список
void free_list(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->word);
        free(temp);
    }
}

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

    // Ввод строки от пользователя
    printf("Введите строку: ");
    fgets(input, sizeof(input), stdin); // Считываем строку с пробелами

    // Удаляем символ новой строки и точку
    input[strcspn(input, "\n")] = '\0';

    // Проверяем строку на корректность
    if (!validate_string(input)) {
        printf("Ошибка: строка должна состоять только из строчных латинских букв, пробелов и содержать точку в конце.\n");
        return 1; // Завершаем программу с кодом ошибки
    }

    input[strcspn(input, ".")] = '\0';

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

    // Проверяем, одинаковы ли длины всех слов
    if (!all_words_same_length(head)) {
        // Находим слова с минимальной и максимальной длиной
        Node *min_node = find_min_length_word(head);
        Node *max_node = find_max_length_word(head);

        // Вставляем перед максимальным словом копию минимального слова
        if (min_node != NULL && max_node != NULL) {
            insert_before(&head, max_node, min_node->word);
        }

        // Выводим список после модификации
        printf("Список после модификации: ");
        print_list(head);
    } else {
        printf("Все слова имеют одинаковую длину. Список не изменен.\n");
        print_list(head);
    }

    // Освобождаем память, выделенную под список
    free_list(head);

    return 0;
}
