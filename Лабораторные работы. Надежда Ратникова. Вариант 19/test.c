#include <stdio.h>
#include <math.h>

// Функция для вычисления факториала
double factorial(int n) {
    if (n == 0 || n == 1) return 1.0;
    double result = 1.0;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Функция для вычисления sin^2(x) через ряд
double sin2_series(double x, double epsilon) {
    double sum = 0.0; // Сумма ряда
    double term;      // Текущий член ряда
    int n = 1;        // Начальный индекс
    do {
        // Вычисление текущего члена ряда
        term = pow(-1, n + 1) * pow(2, 2 * n - 1) * pow(x, 2 * n) / factorial(2 * n);
        sum += term; // Добавление члена ряда к сумме
        n++;         // Переход к следующему индексу
    } while (fabs(term) > epsilon); // Проверка условия точности
    return sum;
}

int main() {
    double x, epsilon;

    // Ввод значения x и точности
    printf("Введите x (-1 < x < 1): ");
    scanf("%lf", &x);
    if (fabs(x) >= 1) {
        printf("Ошибка: x должен быть в диапазоне -1 < x < 1\n");
        return 1;
    }

    printf("Введите точность (epsilon): ");
    scanf("%lf", &epsilon);
    if (epsilon <= 0) {
        printf("Ошибка: точность должна быть положительной\n");
        return 1;
    }

    // Вычисление sin^2(x) через ряд
    double result = sin2_series(x, epsilon);
    printf("sin^2(%.6f) ≈ %.10f\n", x, result);

    return 0;
}
