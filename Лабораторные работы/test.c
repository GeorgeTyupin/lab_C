 #include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

// Модуль для вывода табличного значения
int Solve(int choice) {
    double res = 0;
    double n = 1, x = 0; // Объявление переменных

    switch (choice) {
        case 1: {
            double accur;
            printf("Введите количество знаков после запятой\n");
            scanf("%lf", &accur);
            if ( accur <= 0 || accur != (int)accur ) {
                puts("Число должно быть целым и больше нуля");
                return 1;
            }
            printf("Считаем ln(1 + x)\n");
            printf("Значение x = ");
            scanf("%lf", &x);

            if (fabs(x) >= 1) {
                printf("Ошибка: x должно быть в диапазоне (-1, 1)\n");
                return 1;
            }

            // Цикл вычисления ln(1 + x), пока член ряда больше необходимой точности
            do {
                res += pow(-1, n - 1) * pow(x, n) / n;
                n += 1;
            } while (pow(x, n - 1) / (n - 1) > pow(10, -accur));

            printf("result = %.*lf\n", (int)accur, res);
            break;
        }
        case 2: {
            double pov;
            printf("Введите количество повторений\n");
            scanf("%lf", &pov);
            if ( pov <= 0 || pov != (int)pov ) {
                puts("Число должно быть целым и больше нуля");
                return 1;
            }
            printf("Считаем ln(1 + x)\n");
            scanf("%lf", &x);

            if (fabs(x) >= 1) {
                printf("Ошибка: x должно быть в диапазоне (-1, 1)\n");
                return 1;
            }                   
            
            // Цикл подсчета результата
            for (int i = 1; i <= pov; i++) {
                res += pow(-1, i - 1) * pow(x, i) / i;
            }

            printf("result = %lf\n", res);
            break;
        }
        default:
            printf("Не должно сюда заходить даже\n");
            break;
    }

    printf("Значение функции посчитано в модуле math.h = %lf\n", log(x + 1));
}

int main() {
    int choice; // Объявление переменной
    setlocale(LC_ALL, "");

    do {
        printf("Выберите способ вычисления\n1) С заданной точностью\n2) С заданным количеством\n");
        scanf("%d", &choice);
        if (choice == 1 || choice == 2) {
            break;
        }
        printf("Повторите ввод\n");
    } while (1);

    Solve(choice); // Вызов функции

    return 0;
}
