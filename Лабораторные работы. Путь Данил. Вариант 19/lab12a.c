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
    // Выделяем память для нового узла
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) { // Проверяем успешность выделения памяти
        printf("Ошибка выделения памяти\n");
        exit(1); // Завершаем программу в случае ошибки
    }
    newNode->coefficient = coefficient; // Устанавливаем коэффициент
    newNode->power = power; // Устанавливаем степень
    newNode->next = NULL; // Изначально следующий узел отсутствует
    return newNode; // Возвращаем указатель на созданный узел
}

// Функция для вывода многочлена
void printPolynomial(Node* head) {
    Node* temp = head; // Указатель для перемещения по списку
    while (temp != NULL) { // Проходим по всем узлам списка
        if (temp->coefficient != 0) { // Если коэффициент ненулевой, выводим член
            if (temp->coefficient > 0 && temp != head) {
                printf("+"); // Добавляем знак "+" перед положительным членом (кроме первого)
            }
            // Упрощаем вывод в зависимости от коэффициента и степени
            if (temp->coefficient == 1 && temp->power != 0) {
                printf("x^%d ", temp->power); // Коэффициент 1 и ненулевая степень
            } else if (temp->coefficient == -1 && temp->power != 0) {
                printf("-x^%d ", temp->power); // Коэффициент -1 и ненулевая степень
            } else {
                printf("%dx^%d ", temp->coefficient, temp->power); // Общий случай
            }
        }
        temp = temp->next; // Переходим к следующему узлу
    }
    printf("\n"); // Завершаем строку
}

// Функция для удаления членов с меньшей степенью
Node* removeLowerPowers(Node* head, int k) {
    Node* temp = head; // Указатель для текущего узла
    Node* prev = NULL; // Указатель на предыдущий узел

    while (temp != NULL) {
        if (temp->power < k) { // Если степень меньше заданного значения
            if (prev == NULL) { // Если текущий узел — первый
                head = temp->next; // Сдвигаем голову списка
                free(temp); // Освобождаем память текущего узла
                temp = head; // Перемещаемся к следующему узлу
            } else { // Если текущий узел не первый
                prev->next = temp->next; // Удаляем текущий узел из списка
                free(temp); // Освобождаем память
                temp = prev->next; // Переходим к следующему узлу
            }
        } else { // Если степень >= k, просто перемещаем указатели
            prev = temp; 
            temp = temp->next;
        }
    }
    return head; // Возвращаем обновленный список
}

// Проверяет, является ли число натуральным
int is_natural(double n) {
    return (n <= 0 || (int)n != n) ? 1 : 0; // Возвращает 1, если число не натуральное
}

// Проверяет, существует ли член с заданной степенью
int doesPowerExist(Node* head, int power) {
    Node* temp = head; // Указатель для перемещения по списку
    while (temp != NULL) {
        if (temp->power == power) { // Если степень найдена, возвращаем 1
            return 1;
        }
        temp = temp->next; // Переход к следующему узлу
    }
    return 0; // Возвращаем 0, если степень не найдена
}

// Функция для ввода многочлена с клавиатуры
Node* inputPolynomial() {
    Node* top = NULL; // Указатель на начало списка
    Node* tail = NULL; // Указатель на конец списка
    float n; // Количество членов многочлена

    printf("Введите количество членов многочлена: ");
    scanf("%f", &n); // Читаем количество членов
    if (is_natural(n)) { // Проверяем, что введено натуральное число
        printf("Ошибка ввода.\n");
        return NULL; // Возвращаем NULL в случае ошибки
    }

    for (int i = 0; i < n; i++) {
        double coefficient, power;
        printf("Введите коэффициент и степень для члена %d (через пробел): ", i + 1);
        scanf("%lf %lf", &coefficient, &power); // Читаем коэффициент и степень

        if (doesPowerExist(top, power)) { // Проверяем, нет ли уже члена с такой степенью
            printf("\nОшибка: член с такой степенью уже существует или вы ввели не число. Попробуйте снова.\n");
            exit(EXIT_FAILURE); // Завершаем программу в случае ошибки
        }

        Node* newNode = createNode(coefficient, power); // Создаем новый узел

        if (top == NULL) { // Если список пуст
            top = newNode; // Устанавливаем первый узел
            tail = newNode;
        } else { // Если список не пуст
            tail->next = newNode; // Добавляем узел в конец
            tail = newNode;
        }
    }

    return top; // Возвращаем указатель на голову списка
}

// Функция для освобождения памяти
void freePolynomial(Node* head) {
    Node* temp;
    while (head != NULL) { // Проходим по всем узлам
        temp = head; 
        head = head->next; // Переходим к следующему узлу
        free(temp); // Освобождаем память текущего узла
    }
}

int main() {
    double N;
    // Ввод многочлена с консоли
    printf("Ввод многочлена.\n");
    Node* polynomial = inputPolynomial(); // Ввод многочлена
    if (polynomial == NULL) { // Проверяем на ошибки ввода
        return 0; // Завершаем программу
    }
    
    printf("Исходный многочлен: ");
    printPolynomial(polynomial); // Вывод исходного многочлена

    puts("Введите число, члены со степениями меньше чем это число будут удалены:");
    //Проверка на ввод именно числа
    if ( scanf("%lf", &N) == 0 ){
        printf("Ошибка: введено не число.\n");
        freePolynomial(polynomial); // Освобождаем память
      return 0; // Успешное завершение программы
    }
    // Удаление членов со степенями меньше N
    polynomial = removeLowerPowers(polynomial, (int)N);

    printf("Многочлен после удаления слагаемых с степенями меньше %d: ", (int)N);
    printPolynomial(polynomial); // Вывод результата

    freePolynomial(polynomial); // Освобождаем память
    return 0; // Успешное завершение программы
}
