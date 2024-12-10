#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>

long long factorial(int n) {
    long long fact = 1;
    for (int i = 1; i <= n; ++i) {
        fact *= i;
    }
    return fact;
}

//Функция вычистения арккосинуса с заданной точностью
double arccos_with_precision(double x, double epsilon) {
    double sum = M_PI / 2;
    double term;
    int n = 0;

    do {
        term = (factorial(2 * n) / (pow(2, 2 * n) * pow(factorial(n), 2) * (2 * n + 1))) * pow(x, 2 * n + 1);
        sum -= term;
        n++;
    } while (fabs(term) > epsilon);

    return sum;
}

//Функция вычистения арккосинуса для заданного количества членов
double arccos_with_terms(double x, int terms) {
    double result = M_PI / 2;

    for (int n = 0; n < terms; ++n) {
        double term = (factorial(2 * n) / (pow(4, n) * pow(factorial(n), 2) * (2 * n + 1))) * pow(x, 2 * n + 1);
        result -= term;
    }
    return result;
}

int main() {
    int choice;
    double x;
    int terms;

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

            printf("Введите значение точности: ");
            scanf("%lf", &epsilon);

            double result = arccos_with_precision(x, epsilon);

            if (!isnan(result)) {
                printf("arccos(%lf) с точностью %f = %.10lf\n", x, epsilon, result);
            }

            return 0;
            break;
        }
        case 2: {
            printf("Введите количество членов ряда: ");
            scanf("%d", &terms);

            // Вычисление арккосинуса
            double result = arccos_with_terms(x, terms);

            if (result != -1) {
                printf("Приближенное значение arccos(%lf) = %.10lf\n", x, result);
            }
            break;
        }
        default: {
            printf("Ошибка: Некорректный выбор\n");
            break;
        }
    }


    return 0;
}