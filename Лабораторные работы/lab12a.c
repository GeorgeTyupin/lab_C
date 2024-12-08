#include <stdio.h>
#include <stdlib.h>

// Структура для узла списка
typedef struct Node {
    int coefficient; // Коэффициент
    int power;       // Степень
    struct Node* next; // Указатель на следующий элемент
} Node;

// Функция для создания нового узла
Node* createNode(int coefficient, int power) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coefficient = coefficient;
    newNode->power = power;
    newNode->next = NULL;
    return newNode;
}

// Функция для вывода списка
void printPolynomial(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->coefficient > 0 && temp != head) {
            printf("+");
        }
        printf("%dx^%d ", temp->coefficient, temp->power);
        temp = temp->next;
    }
    printf("\n");
}

// Функция для удаления элементов с чётными степенями
Node* removeEvenPowers(Node* head) {
    Node* temp = head;
    Node* prev = NULL;

    while (temp != NULL) {
        if (temp->power % 2 == 0) {
            if (prev == NULL) {
                head = temp->next;
                free(temp);
                temp = head;
            } else {
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
            }
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
    return head;
}

int main() {
    // Создание списка вручную
    Node* polynomial = createNode(2, 1);
    polynomial->next = createNode(-5, 2);
    polynomial->next->next = createNode(1, 4);
    polynomial->next->next->next = createNode(-3, 5);

    printf("Исходный многочлен: ");
    printPolynomial(polynomial);

    // Удаление слагаемых с чётными степенями
    polynomial = removeEvenPowers(polynomial);

    printf("Многочлен после удаления чётных степеней: ");
    printPolynomial(polynomial);

    return 0;
}
