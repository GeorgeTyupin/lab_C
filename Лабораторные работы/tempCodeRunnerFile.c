
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