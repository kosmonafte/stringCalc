// countCalc.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>
using namespace std;
int countCalc(char* str);
int parseCalc(char* str);
int plusMinusCalc(char* str);
double plusMinusCalcV2(char* str);
int main()
{
    char* stroka = new char[100];
    cin >> stroka;
    char* nStroka = new char[strlen(stroka) + 1];
    for (int i = 0; i < strlen(stroka); i++) {
        nStroka[i] = stroka[i];
    }
    nStroka[strlen(stroka)] = '\0';
    delete[]stroka;
    cout << nStroka << endl;
    //cout << countCalc(nStroka) << endl;
    //plusMinusCalc(nStroka);
    
    cout << endl << plusMinusCalcV2(nStroka);

    
}

double plusMinusCalcV2(char* str) {
    //
    // создаем указатель с нулевым значением, далее приводим строку к универсальному
    // формату и записываем ее в созданый указатель, т.е. расставляем знаки арифметики,
    // если первое число не отрицательное,
    // то добавляем к нему знак "+", а в конец добавляем знак "=", если в начале число
    // отрицательное то просто в конец добавляем знак "=".
    // 
    char* nStr = nullptr;
    if (str[0] != '+' && str[0] != '-') {
        nStr = new char[strlen(str) + 3];
        for (int i = 0; i < strlen(str) + 3; i++) {
            if (i == 0) {
                nStr[i] = '+';
            }
            else if (i == strlen(str) + 2) {
                nStr[i] = '\0';
            }
            else if (i == strlen(str) + 1) {
                nStr[i] = '=';
            }
            else {
                nStr[i] = str[i - 1];
            }
        }
    }
    else {
        nStr = new char[strlen(str) + 2];
        for (int i = 0; i < strlen(str) + 2; i++) {
            if (i == strlen(str) + 1) {
                nStr[i] = '\0';
            }
            else if (i == strlen(str)) {
                nStr[i] = '=';
            }
            else {
                nStr[i] = str[i];
            }
        }
    }
    //
    // Считаем сколько у нас знаков, а значит и элементов
    // 
    int signCount = 0;
    for (int i = 0; i < strlen(nStr); i++) {
        if (nStr[i] == '+' || nStr[i] == '-') {
            signCount++;
        }
    }
    cout << nStr << endl << signCount << endl;
    //
    // Проходим по строке и парсим данные уже в числовой массив
    //
    double* strToNumber = new double[signCount];
    int k = 0;
    for (int i = 0; i < strlen(nStr) ; i++) {
        if (nStr[i] == '+' || nStr[i] == '-') {
            for (int j = i + 1; j < strlen(nStr); j++) {
                if (nStr[j] == '+' || nStr[j] == '-' || nStr[j] == '=') {
                    char* number = new char[j - i + 1];
                    int m = 0;
                    for (int l = i; l < j; l++) {
                        number[m++] = nStr[l];
                    }
                    number[j - i] = '\0';
                    strToNumber[k] = atof(number);
                    k++;
                    break;
                }
            }
        }
    }
    //
    // Считаем сумму числового массива
    //
    double summ = 0;
    for (int i = 0; i < k; i++) {
        cout << strToNumber[i] << " ";
        summ += strToNumber[i];
    }

    return summ;
}

int plusMinusCalc(char* str) {


    double leftNumber, rightNumber;                          //переменые под 2 числа
    for (int i = 0; i < strlen(str); i++) {                  //идум по строке слева на право ищем знаки арифметики
        if (str[i] == '+' || str[i] == '-') {                //если встречаем + или -
            if (str[i] == '+') {                             //если это плюс
                for (int j = i - 1; j > 0; j--) {            //идем в обратную сторону и ищем предыдущий плюс и минус
                    if (str[j] == '+' || str[j] == '-') {    //если вустречаем знак то парсим число
                        char* number = new char[i - j];      //создаем новый масив чаров
                        int k = 0;                           
                        for (int l = j + 1; k < i; l++) {    //переписываем часть строки в новый массив
                            number[k++] = str[l];            // 
                        }
                        number[i - j - 1] = '\0';
                        leftNumber = atof(number);           //переводим строку в число
                        cout << leftNumber;
                        break;
                    }
                }
            }
            else {
                //natknulis na minus

            }
        }
    }
    return 0;
}

int parseCalc(char* str) {
    int k = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '*' || str[i] == '/') {
            k++;
        }
    }
    for (int i = 0; i < k; i++) { 
    }
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '*') {

        }
    }
    return 0;
}

int countCalc(char* str) { // Функция убирания скобок, в нее нужно передать функцию рассчета строки
    // Это счетчик чтобы понять сколько раз проходить по строке
    int k = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '(') {
            k++;
        }
    }
    // идем по строке и ищем открывающую скобу, если находим, то начинаем искать
    // закрывающую скобку, если находим то покачто просто печатаем то что между скобок,
    // если по пути попадается снова открывающая скобка то перекидываем индекс на нее
    // и снова идем дальше снова ищем закрывающуюу скобку.
    // Так проходиться нужно будет столько раз сколько у нас пар скобок
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '(') {
            for (int j = i + 1; j < strlen(str); j++) {
                if (str[j] == ')') {
                    for (int l = i + 1; l < j; l++) {
                        cout << str[l] << " ";
                    }
                    cout << endl;
                    break;
                }
                if (str[j] == '(') {
                    i = j - 1;
                    break;
                }
            }          
        }
    }

    return k;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
