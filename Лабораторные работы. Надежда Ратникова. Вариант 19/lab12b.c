#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *word;
    struct Node *prev;
    struct Node *next;
} Node;

// Функция для создания нового узла
Node* create_node(const char *word) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->word = strdup(word);
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

// Функция для добавления слова в список
void add_node(Node **head, const char *word) {
    Node *new_node = create_node(word);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->prev = temp;
    }
}

// Функция для вывода списка
void print_list(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%s ", temp->word);
        temp = temp->next;
    }
    printf("\n");
}

// Функция для удаления слов, начинающихся с заданной буквы
void remove_words_starting_with(Node **head, char letter) {
    Node *temp = *head;
    while (temp != NULL) {
        if (temp->word[0] == letter) {
            Node *to_delete = temp;
            if (temp->prev) {
                temp->prev->next = temp->next;
            } else {
                *head = temp->next;
            }
            if (temp->next) {
                temp->next->prev = temp->prev;
            }
            temp = temp->next;
            free(to_delete->word);
            free(to_delete);
        } else {
            temp = temp->next;
        }
    }
}

int main() {
    char input[1000];
    char letter;
    
    printf("Введите строку: ");
    fgets(input, sizeof(input), stdin);
    
    input[strcspn(input, ".")] = '\0';

    printf("Введите букву для удаления слов, начинающихся с неё: ");
    scanf("%c", &letter);

    Node *head = NULL;
    char *word = strtok(input, " ");
    while (word != NULL) {
        add_node(&head, word);
        word = strtok(NULL, " ");
    }

    printf("Исходный список: ");
    print_list(head);

    remove_words_starting_with(&head, letter);

    printf("Список после модификации: ");
    print_list(head);

    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->word);
        free(temp);
    }

    return 0;
}
