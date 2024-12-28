#include <stdio.h>
#include <stdlib.h>

// Структура для узла списка
typedef struct Node {
    int coefficient; // Коэффициент члена многочлена
    int power;       // Степень члена многочлена
    struct Node* next; // Указатель на следующий элемент списка
} Node;

// Функция для создания нового узла списка
Node* createNode(int coefficient, int power) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    newNode->coefficient = coefficient;
    newNode->power = power;
    newNode->next = NULL;
    return newNode;
}

// Функция для вывода многочлена
void printPolynomial(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->coefficient != 0) {
            if (temp->coefficient > 0 && temp != head) {
                printf("+");
            }
            if (temp->power == 0) {
                printf("%d", temp->coefficient);
            } else if (temp->power == 1) {
                printf("%dx", temp->coefficient);
            } else {
                printf("%dx^%d", temp->coefficient, temp->power);
            }
        }
        temp = temp->next;
    }
    printf("\n");
}

// Функция для удаления членов с степенями больше заданной
Node* removeHigherPowers(Node* head, int k) {
    Node* temp = head;
    Node* prev = NULL;

    while (temp != NULL) {
        if (temp->power > k) {
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

// Функция для ввода многочлена с клавиатуры
Node* inputPolynomial() {
    Node* head = NULL;
    Node* tail = NULL;
    float n;

    printf("Введите количество членов многочлена: ");
    scanf("%f", &n);
    if (n <= 0 || (int)n != n) {
        printf("Ошибка ввода.\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        int coefficient, power;
        printf("Введите коэффициент и степень для члена %d (через пробел): ", i + 1);
        scanf("%d %d", &coefficient, &power);

        Node* newNode = createNode(coefficient, power);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}

// Функция для освобождения памяти
void freePolynomial(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    double k;
    printf("Ввод многочлена.\n");
    Node* polynomial = inputPolynomial();
    if (polynomial == NULL) { // Проверяем на ошибки ввода
        return 0;
    }

    printf("Исходный многочлен: ");
    printPolynomial(polynomial);



    printf("Введите максимальную степень: ");
    scanf("%lf", &k);

    if (k <= 0 || k != (int)k) {
        printf("Ошибка: Число должно быть натуральным.\n");
        freePolynomial(polynomial);
        return 1;
    }

    polynomial = removeHigherPowers(polynomial, k);

    printf("Многочлен после удаления членов со степенями больше %d: ", (int)k);
    printPolynomial(polynomial);

    freePolynomial(polynomial);
    return 0;
}
