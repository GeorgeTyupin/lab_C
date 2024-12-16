#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char* word;
    struct Node* prev;
    struct Node* next;
} Node;

// Функция для создания нового узла
Node* createNode(const char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->word = strdup(word);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Функция для добавления узла в конец списка
void appendNode(Node** head, Node** tail, const char* word) {
    Node* newNode = createNode(word);
    if (*tail) {
        (*tail)->next = newNode;
        newNode->prev = *tail;
        *tail = newNode;
    } else {
        *head = *tail = newNode;
    }
}

// Функция для вывода списка
void printList(Node* head) {
    Node* current = head;
    while (current) {
        printf("%s ", current->word);
        current = current->next;
    }
    printf("\n");
}

// Проверка, начинается ли слово с гласной
int startsWithVowel(const char* word) {
    if (!word || word[0] == '\0') return 0;
    
    char first = tolower((char)word[0]);

    return first == 'a' || first == 'e' || first == 'i' || first == 'o' || first == 'u' || first == 'y';
}

// Разделение списка на два
void splitList(Node* head, Node** vowelsHead, Node** vowelsTail, Node** consonantsHead, Node** consonantsTail) {
    Node* current = head;
    while (current) {
        if (startsWithVowel(current->word)) {
            appendNode(vowelsHead, vowelsTail, current->word);
        } else {
            appendNode(consonantsHead, consonantsTail, current->word);
        }
        current = current->next;
    }
}

int main() {
    char input[256];
    Node* head = NULL;
    Node* tail = NULL;

    printf("Введите строку:\n");
    fgets(input, sizeof(input), stdin);

    // Удаляем точку и разбиваем строку на слова
    char* token = strtok(input, " .\n");
    while (token) {
        appendNode(&head, &tail, token);
        token = strtok(NULL, " .\n");
    }

    printf("Исходный список:\n");
    printList(head);

    // Разделяем список
    Node *vowelsHead = NULL, *vowelsTail = NULL;
    Node *consonantsHead = NULL, *consonantsTail = NULL;
    splitList(head, &vowelsHead, &vowelsTail, &consonantsHead, &consonantsTail);

    printf("Список слов, начинающихся с гласных:\n");
    printList(vowelsHead);

    printf("Список слов, начинающихся с согласных:\n");
    printList(consonantsHead);


    return 0;
}
