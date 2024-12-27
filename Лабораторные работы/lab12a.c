#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Структура для узла списка
typedef struct Node {
    int coefficient; // Коэффициент
    int power;       // Степень
    struct Node* next; // Указатель на следующий элемент
} Node;

// Функция для создания нового узла
Node* createNode(int coefficient, int power) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) {
        printf("Ошибка выделения памяти.\n");
        exit(1);
    }
    newNode->coefficient = coefficient;
    newNode->power = power;
    newNode->next = NULL;
    return newNode;
}

// Функция для вывода списка
void printPolynomial(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->coefficient != 0) {
            if (temp->coefficient > 0 && temp != head) {
                printf("+");
            }
            if (temp->coefficient == 1 && temp->power != 0) {
                printf("x^%d ", temp->power);
            } else if (temp->coefficient == -1 && temp->power != 0) {
                printf("-x^%d ", temp->power);
            } else {
                printf("%dx^%d ", temp->coefficient, temp->power);
            }
        }
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

// Функция для проверки, существует ли степень в списке
int doesPowerExist(Node* head, int power) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->power == power) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int is_natural(double n) {
    return (n <= 0 || (int)n != n) ? 1 : 0;
}

// Функция для ввода многочлена
Node* inputPolynomial() {
    Node* top = NULL;
    Node* tail = NULL;
    float n;
    char input[100];

    printf("Введите количество членов многочлена: ");
    scanf("%f", &n);
    if ( is_natural(n) ) {
        printf("Ошибка ввода.");
        return NULL;
    }
    

    for (int i = 0; i < n; i++) {
        double coefficient, power;
        printf("Введите коэффициент и степень для члена %d (через пробел): ", i + 1);
        scanf("%lf %lf", &coefficient, &power);

        if (doesPowerExist(top, power)) {
            printf("Ошибка: член с такой степенью уже существует. Попробуйте снова.\n");
            exit(EXIT_FAILURE);
        }

        Node* newNode = createNode(coefficient, power);

        if (top == NULL) {
            top = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return top;
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
    // Ввод многочлена с консоли
    printf("Ввод многчлена.\n");
    Node* polynomial = inputPolynomial();
    if ( polynomial == NULL ) {
        return 0;
    }

    printf("Исходный многочлен: ");
    printPolynomial(polynomial);

    // Удаление слагаемых с чётными степенями
    polynomial = removeEvenPowers(polynomial);

    printf("Многочлен после удаления чётных степеней: ");
    printPolynomial(polynomial);

    // Освобождение памяти
    freePolynomial(polynomial);

    return 0;
}
