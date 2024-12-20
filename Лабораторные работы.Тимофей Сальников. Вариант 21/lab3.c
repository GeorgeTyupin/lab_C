#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>

// Функция для вычисления факториала
long long factorial(int n) {
    long long fact = 1;
    for (int i = 1; i <= n; ++i) {
        fact *= i;
    }
    return fact;
}

// Функция для вычисления cos^2(x) с точностью epsilon
double cos2_with_precision(double x, double epsilon) {
    double result = 1; // Первое значение ряда
    double term;
    int n = 1;

    do {
        // Член ряда разложения
        term = pow(-1, n + 1) * pow(2, 2 * n - 1) * pow(x, 2 * n) / factorial(2 * n);
        result -= term;
        n++;
    } while (fabs(term) > epsilon);

    return result;
}

// Функция для вычисления cos^2(x) для заданного количества членов
double cos2_with_terms(double x, int terms) {
    double result = 1; // Первое значение ряда

    for (int n = 1; n <= terms; ++n) {
        // Член ряда разложения
        double term = pow(-1, n + 1) * pow(2, 2 * n - 1) * pow(x, 2 * n) / factorial(2 * n);
        result -= term;
    }
    return result;
}

int main() {
    int choice;
    double x;
    double terms;

    printf("Введите значение x (|x| < 1): ");
    scanf("%lf", &x);

    if (fabs(x) >= 1) {
        printf("Ошибка: x должно быть в диапазоне (-1, 1)\n");
        return 1;
    }

    printf("Выберите способ вычисления:\n");
    printf("1 - С заданной точностью\n");
    printf("2 - Для заданного количества членов\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            double epsilon;

            printf("Введите значение точности (больше нуля): ");
            scanf("%lf", &epsilon);

            if (epsilon <= 0) {
                printf("Ошибка: Точность должна быть больше нуля\n");
                return 1;
            }

            double result = cos2_with_precision(x, epsilon);
            printf("cos^2(%lf) с точностью %f = %.10lf\n", x, epsilon, result);
            break;
        }
        case 2: {
            printf("Введите количество членов ряда (Натуральное): ");
            scanf("%lf", &terms);
            if (terms <= 0 || terms != (int)terms) {
                printf("*Ошибка:* Число должно быть натуральным.\n");
                break;
            }
    

            double result = cos2_with_terms(x, terms);
            printf("cos^2(%lf) с %d членами ряда = %.10lf\n", x, (int)terms, result);
            break;
        }
        default:
            printf("Ошибка: Некорректный выбор\n");
            break;
    }

    return 0;
}
