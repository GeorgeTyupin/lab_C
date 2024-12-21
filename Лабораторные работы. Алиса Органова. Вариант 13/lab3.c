#include <stdio.h>
#include <math.h>

// Функция для вычисления \sqrt{1 + x} с заданной точностью
double sqrt_with_precision(double x, double epsilon) {
    double sum = 1; // Первый член ряда
    double term = x / 2; // Второй член ряда
    int n = 1;

    sum += term; // Добавляем первый ненулевой член

    while (fabs(term) > epsilon) {
        n++;
        term *= (-1) * (2 * n - 3) * x / (2 * n); // Рекуррентное вычисление n-го члена
        sum += term;
    }

    return sum;
}

// Функция для вычисления \sqrt{1 + x} для заданного количества членов
double sqrt_with_terms(double x, int terms) {
    double sum = 1; // Первый член ряда
    double term = x / 2; // Второй член ряда

    sum += term; // Добавляем первый ненулевой член

    for (int n = 2; n <= terms; ++n) {
        term *= (-1) * (2 * n - 3) * x / (2 * n); // Рекуррентное вычисление n-го члена
        sum += term;
    }

    return sum;
}

int main() {
    int choice;
    double x;

    printf("Введите значение x (от -1 до 1): ");
    scanf("%lf", &x);

    if (x <= -1 || x >= 1) {
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
                printf("Ошибка: точность должна быть больше нуля\n");
                return 1;
            }

            double result = sqrt_with_precision(x, epsilon);
            printf("\u221A(1 + %lf) = \u221A(%lf) с точностью %f = %.10lf\n", x, x+1, epsilon, result);
            break;
        }
        case 2: {
            double terms;
            printf("Введите количество членов ряда (натуральное число): ");
            scanf("%lf", &terms);
            if (terms <= 0 || terms != (int)terms) {
                printf("*Ошибка:* Число должно быть натуральным.\n");
                break;
            }

            if (terms <= 0) {
                printf("Ошибка: число членов ряда должно быть натуральным\n");
                return 1;
            }

            double result = sqrt_with_terms(x, (int)terms);
            printf("\u221A(1 + %lf) = \u221A(%lf) с %d членами ряда = %.10lf\n", x, x+1, (int)terms, result);
            break;
        }
        default:
            printf("Ошибка: некорректный выбор\n");
            return 1;
    }

    return 0;
}
