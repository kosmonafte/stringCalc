// countCalc.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;
int countCalc(char* str);
int parseCalc(char* str);
char& normalize(char* str);
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



    //cout << plusMinusCalcV2(nStroka);

    parseCalc(nStroka);

}

char& normalize(char* str) {
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
    return *nStr;
}

double plusMinusCalcV2(char* str) {
    char* nStr = &normalize(str);
    // Считаем сколько у нас знаков, а значит и элементов
    int signCount = 0;
    for (int i = 0; i < strlen(nStr); i++) {
        if (nStr[i] == '+' || nStr[i] == '-') {
            signCount++;
        }
    }
    //cout << nStr << endl << signCount << endl;
    // Проходим по строке и парсим данные уже в числовой массив
    double* strToNumber = new double[signCount];
    int k = 0;
    char* number = nullptr;
    for (int i = 0; i < strlen(nStr) ; i++) {
        if (nStr[i] == '+' || nStr[i] == '-') {
            for (int j = i + 1; j < strlen(nStr); j++) {
                if (nStr[j] == '+' || nStr[j] == '-' || nStr[j] == '=') {
                    number = new char[j - i + 1];
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
    // Считаем сумму числового массива
    double summ = 0;
    for (int i = 0; i < k; i++) {
        summ += strToNumber[i];
    }
    delete[]nStr;
    delete[]number;
    delete[]strToNumber;
    return summ;
}

int parseCalc(char* str) {
    char* nStr = &normalize(str);
    for (int i = 0; i < strlen(nStr); i++) {
        cout << nStr[i];
    }
    cout << endl;
    int k = 0;
    for (int i = 0; i < strlen(nStr); i++) {
        if (nStr[i] == '*' || nStr[i] == '/') {
            k++;
        }
    }
    cout << k << endl;
    char larr[10], rarr[10];
    char* leftNumber, * rightNumber, *nnStr, *nnnStr;
    double lN, rN, result;
    int leftPart, rightPart, countStartDel, countEndDel;
    for (int n = 0; n < k; n++) {
        int sizeToDel = 1;
        for (int i = 0; i < strlen(nStr); i++) {
            if (nStr[i] == '*') {
                for (int j = i - 1; j >= 0; j--) {
                    if (nStr[j] == '+' || nStr[j] == '*' || nStr[j] == '/' || nStr[j] == '-' || nStr[j] == '=') {
                        leftNumber = new char[i - j];
                        countStartDel = j + 1;
                        for (int l = j + 1, m = 0; l < i; l++, m++) {
                            leftNumber[m] = nStr[l];
                        }
                        leftNumber[i - j - 1] = '\0';
                        cout << endl << leftNumber << "-----------" << endl;
                        sizeToDel += strlen(leftNumber);
                        cout << endl << sizeToDel << "-----------" << endl;
                        lN = atof(leftNumber);
                        
                        delete[]leftNumber;
                        cout << endl << lN << "left" << endl;
                        break;
                    }
                }
                for (int j = i + 1; j < strlen(nStr); j++) {
                    if (nStr[j] == '+' || nStr[j] == '*' || nStr[j] == '/' || nStr[j] == '-' || nStr[j] == '=') {
                        rightNumber = new char[j - i];
                        countEndDel = j - 1;
                        for (int l = i + 1, m = 0; l < j; l++, m++) {
                            rightNumber[m] = nStr[l];
                        }
                        rightNumber[j - i - 1] = '\0';
                        sizeToDel += strlen(rightNumber);
                        cout << endl << sizeToDel << "-----------" << endl;
                        rN = atof(rightNumber);
                        
                        delete[]rightNumber;
                        cout << endl << rN << "right " << endl;
                        break;
                    }
                }
                result = lN * rN;
                //cout << result << endl;
                //result += 0.345;
                leftPart = result;
                rightPart = (result - leftPart) * 1000;
                cout << leftPart << "." << rightPart << endl;
                _itoa_s(leftPart, larr, 10);
                _itoa_s(rightPart, rarr, 10);
                cout << strlen(larr) << endl << strlen(rarr) << endl;
                nnStr = new char[strlen(larr) + strlen(rarr) + 2];
                for (int o = 0; o < strlen(larr); o++) {
                    nnStr[o] = larr[o];
                }
                nnStr[strlen(larr)] = '.';
                for (int o = strlen(larr) + 1; o < strlen(larr) + strlen(rarr) + 1; o++) {
                    nnStr[o] = rarr[o - strlen(larr) - 1];
                }
                nnStr[strlen(larr) + strlen(rarr) + 1] = '\0';
                cout << nnStr;
                cout << endl << sizeToDel << "sadasdasdadasdsda";
                nnnStr = new char[strlen(nStr) - sizeToDel + strlen(nnStr) + 1];
                for (int j = 0; j < countStartDel; j++) {
                    nnnStr[j] = nStr[j];
                }
                for (int j = countStartDel; j < strlen(nnStr) + countStartDel; j++) {
                    nnnStr[j] = nnStr[j - countStartDel];
                }
                for (int j = countStartDel + strlen(nnStr); j < strlen(nnnStr); j++) {
                    nnnStr[j] = nStr[j + countEndDel - countStartDel - strlen(nnStr) + 1];
                }

                cout << endl << nnnStr;
                delete[]nStr;
                nStr = nnnStr;
                break;
            }
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


