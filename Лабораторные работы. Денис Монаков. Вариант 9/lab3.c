#include <stdio.h>
#include <math.h>

// Функция вычисления факториала
long long factorial(int n) {
    long long fact = 1;
    for (int i = 1; i <= n; ++i) {
        fact *= i;
    }
    return fact;
}

// Нормализация x в диапазон [-2*pi, 2*pi]
double normalize_x(double x) {
    const double PI = 3.141592653589793;
    return fmod(x, 2 * PI);
}

// Функция вычисления cos(x) с заданной точностью
double cos_with_precision(double x, double epsilon) {
    x = normalize_x(x); // Нормализация x

    double sum = 0.0;
    double term = 1.0; // Первый член ряда
    int n = 0;

    while (fabs(term) > epsilon) {
        term = pow(-1, n) * pow(x, 2 * n) / factorial(2 * n);
        sum += term;
        n++;
    }

    return sum;
}

// Функция вычисления cos(x) для заданного количества членов
double cos_with_terms(double x, int terms) {
    x = normalize_x(x); // Нормализация x

    double result = 0.0;
    for (int n = 0; n < terms; n++) {
        double term = pow(-1, n) * pow(x, 2 * n) / factorial(2 * n);
        result += term;
    }
    return result;
}

int main() {
    int choice;
    double x;

    printf("Введите значение x: ");
    scanf("%lf", &x);

    printf("Выберите способ вычисления:\n");
    printf("1 - С заданной точностью\n");
    printf("2 - Для заданного количества членов\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            double epsilon;

            printf("Введите значение точности epsilon: ");
            scanf("%lf", &epsilon);

            if (epsilon <= 0) {
                printf("Ошибка: точность должна быть положительным числом\n");
                return 1;
            }

            double result = cos_with_precision(x, epsilon);

            printf("cos(%lf) с точностью %f = %.10lf\n", x, epsilon, result);
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

            double result = cos_with_terms(x, (int)terms);
            printf("Приближенное значение cos(%lf) = %.10lf\n", x, result);
            break;
        }
        default: {
            printf("Ошибка: некорректный выбор или число\n");
            return 1;
        }
    }

    return 0;
}
