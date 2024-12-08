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

//Функция вычистения sin^2(x) с заданной точностью
double sin2_with_precision(double x, double epsilon) {
    double sum = 0.0;
    double term;
    int n = 1;
    do {

        term = pow(-1, n + 1) * pow(2, 2 * n - 1) * pow(x, 2 * n) / factorial(2 * n);
        sum += term;
        n++;
    } while (fabs(term) > epsilon);
    return sum;
}

//Функция вычистения sin^2(x) для заданного количества членов
double sin2x_with_terms(double x, int terms) {
    double result = 0.0;
    for (int n = 1; n <= terms; n++) {
        double term = pow(-1, n + 1) * pow(2, 2 * n - 1) * pow(x, 2 * n) / factorial(2 * n);
        result += term;
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
        printf("Ошибка: x должно быть в диапазоне (-1, 1)\\n");
        return 1;
    }

    printf("Выберите способ вычисления:\n");
    printf("1 - С заданной точностью\n");
    printf("2 - Для заданного количества членов\n");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1: {
            double epsilon;

            printf("Введите значение точности epsilon: ");
            scanf("%lf", &epsilon);

            double result = sin2_with_precision(x, epsilon);

            if (!isnan(result)) {
                printf("sin^2(%lf) с точностью %f = %.10lf\n", x, epsilon, result);
            }

            return 0;
            break;
        }
        case 2: {
            printf("Введите количество членов ряда: ");
            scanf("%d", &terms);

            // Вычисление арккосинуса
            double result = sin2x_with_terms(x, terms);

            if (result != -1) {
                printf("Приближенное значение sin^2(%lf) = %.10lf\n", x, result);
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