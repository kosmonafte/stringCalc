// countCalc.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;
char* countCalc(char* str);
char* multDivideCalc(char* str);
char& normalize(char* str);
char* floatToString(double number);
char* plusMinusCalcV2(char* str);
char* brackets(char* str);
int main()
{
    while (true) {
        char* stroka = new char[100];
        cin >> stroka;
        char* nStroka = new char[strlen(stroka) + 1];
        for (int i = 0; i < strlen(stroka); i++) {
            nStroka[i] = stroka[i];
        }
        nStroka[strlen(stroka)] = '\0';
        delete[]stroka;

        //cout << plusMinusCalcV2(multDivideCalc(countCalc(nStroka))) << endl;

        cout << plusMinusCalcV2(multDivideCalc(brackets(nStroka))) << endl;
        cout << endl;
    }
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
    if (str[strlen(str) - 1] == '=') {
        if (str[0] != '+' && str[0] != '-') {
            nStr = new char[strlen(str) + 3];
            for (int i = 0; i < strlen(str) + 3; i++) {
                if (i == 0) {
                    nStr[i] = '+';
                }
                else if (i == strlen(str) + 2) {
                    nStr[i] = '\0';
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
                else {
                    nStr[i] = str[i];
                }
            }
        }
    }
    else {
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
    }
    int dCount = 0;
    for (int i = 0; i < strlen(nStr); i++) {
        if (nStr[i] == '+' && nStr[i + 1] == '-' || nStr[i] == '-' && nStr[i + 1] == '-') {
            dCount++;
        }
    }
    
    for (int n = 0; n < dCount; n++) {
        for (int i = 0; i < strlen(nStr); i++) {
            if (nStr[i] == '+' && nStr[i + 1] == '-') {
                char* nnStr = new char[strlen(nStr)];
                for (int j = 0; j < i; j++) {
                    nnStr[j] = nStr[j];
                }
                for (int j = i + 1; j < strlen(nStr); j++) {
                    nnStr[j - 1] = nStr[j];
                }
                delete[]nStr;
                nStr = nnStr;
                break;
            }
            else if (nStr[i] == '-' && nStr[i + 1] == '-') {
                char* nnStr = new char[strlen(nStr)];
                for (int j = 0; j < i; j++) {
                    nnStr[j] = nStr[j];
                }
                for (int j = i + 1; j < strlen(nStr); j++) {
                    if (j == i + 1) {
                        nnStr[j - 1] = '+';
                    }
                    else {
                        nnStr[j - 1] = nStr[j];
                    }
                }
                delete[]nStr;
                nStr = nnStr;
                break;
            }
        }  
    }
    return *nStr;
}

char* floatToString(double number) {
    char larr[10], rarr[10];
    float rightTemp;
    int leftPart, rightPart;
    char* nnStr;
    if (number < 0) {
        leftPart = number;
        rightPart = (-1) * (number - (float)leftPart) * 10;
    }
    else {
        leftPart = number;
        rightTemp = (number - leftPart) * 10;
        rightPart = rightTemp;
    }
    _itoa_s(leftPart, larr, 10);
    _itoa_s(rightPart, rarr, 10);
    nnStr = new char[strlen(larr) + strlen(rarr) + 2];
    for (int o = 0; o < strlen(larr); o++) {
        nnStr[o] = larr[o];
    }
    nnStr[strlen(larr)] = '.';
    for (int o = strlen(larr) + 1; o < strlen(larr) + strlen(rarr) + 1; o++) {
        nnStr[o] = rarr[o - strlen(larr) - 1];
    }
    nnStr[strlen(larr) + strlen(rarr) + 1] = '\0';
    return nnStr;
}

char* plusMinusCalcV2(char* str) {
    char* nStr = &normalize(str);
    // Считаем сколько у нас знаков, а значит и элементов
    int signCount = 0;
    for (int i = 0; i < strlen(nStr); i++) {
        if (nStr[i] == '+' || nStr[i] == '-') {
            signCount++;
        }
    }
    // Проходим по строке и парсим данные уже в числовой массив
    double* strToNumber = new double[signCount];
    int k = 0;
    char* number = nullptr;
    for (int i = 0; i < strlen(nStr); i++) {
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
    for (int i = 0; i < signCount; i++) {
        summ += strToNumber[i];
    }
    delete[]nStr;
    delete[]number;
    delete[]strToNumber;

    return floatToString(summ);
}

char* multDivideCalc(char* str) {
    char* nStr = &normalize(str);  //приводим строку к удобному виду
    int k = 0;
    for (int i = 0; i < strlen(nStr); i++) {            //считаем сколько в строке знаков "*" и "/"
        if (nStr[i] == '*' || nStr[i] == '/') {         //столько раз будем проходить циклом
            k++;
        }
    }
    char larr[10], rarr[10];
    char* leftNumber, * rightNumber, *nnStr, *nnnStr;
    double lN, rN, result;
    long long leftPart, rightPart;
    int countStartDel, countEndDel;
    //идем по строке пока не встретим знак "*" и "/",
    //если встретили то идем от знака обратно пока не встретим хоть какой другой знак,
    //потом от знака идем вперед пока не встретим хоть какой знак
    //парсим эти числа и пишем их во флот
    for (int n = 0; n < k; n++) {
        int sizeToDel = 1;
        for (int i = 0; i < strlen(nStr); i++) {
            if (nStr[i] == '*' || nStr[i] == '/') {
                for (int j = i - 1; j >= 0; j--) {
                    if (nStr[j] == '+' || nStr[j] == '*' || nStr[j] == '/' || nStr[j] == '-' || nStr[j] == '=') {
                        leftNumber = new char[i - j];
                        countStartDel = j + 1;
                        for (int l = j + 1, m = 0; l < i; l++, m++) {
                            leftNumber[m] = nStr[l];
                        }
                        leftNumber[i - j - 1] = '\0';
                        sizeToDel += strlen(leftNumber);
                        lN = atof(leftNumber);
                        delete[]leftNumber;
                        break;
                    }
                }
                for (int j = i + 1; j < strlen(nStr); j++) {
                   
                    if (nStr[j] == '+' || nStr[j] == '*' || nStr[j] == '/' || nStr[j] == '-' && j != i + 1 || nStr[j] == '=') {
                        rightNumber = new char[j - i];
                        countEndDel = j - 1;
                        for (int l = i + 1, m = 0; l < j; l++, m++) {
                            rightNumber[m] = nStr[l];
                        }
                        rightNumber[j - i - 1] = '\0';
                        sizeToDel += strlen(rightNumber);
                        rN = atof(rightNumber);
                        delete[]rightNumber;
                        break;
                    }
                }
                //считаем умножение или деление
                if (nStr[i] == '*') {
                    result = lN * rN;
                }
                if (nStr[i] == '/') {
                    result = lN / rN;
                }
                //переносим флот обратно в чар
                nnStr = floatToString(result);
                //вписываем новую строку в старый массив при этом сразу меняя длину
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
                nnnStr[strlen(nStr) - sizeToDel + strlen(nnStr)] = '\0';
                delete[]nStr;
                delete[]nnStr;
                nStr = nnnStr;
                break;
            }
        }
    }
    return nStr;
}

char* countCalc(char* str) { // Функция убирания скобок, в нее нужно передать функцию рассчета строки
    // Это счетчик чтобы понять сколько раз проходить по строке
    int k = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '(') {
            k++;
        }
    }
    if (k == 0) {
        return str;
    }
    // идем по строке и ищем открывающую скобу, если находим, то начинаем искать
    // закрывающую скобку, если находим то покачто просто печатаем то что между скобок,
    // если по пути попадается снова открывающая скобка то перекидываем индекс на нее
    // и снова идем дальше снова ищем закрывающуюу скобку.
    // Так проходиться нужно будет столько раз сколько у нас пар скобок
    for (int n = 0; n < k; n++) { 
        int z = 0;
        for (int i = 0; i < strlen(str); i++) {
            if (str[i] == '(') {
                for (int j = i + 1; j < strlen(str); j++) {
                    if (str[j] == ')') {
                        char* nStr = new char[j - i];
                        for (int l = i + 1, m = 0; l < j; l++, m++) {
                            nStr[m] = str[l];
                        }
                        nStr[j - i - 1] = '\0';  
                        char* nnStr = plusMinusCalcV2(multDivideCalc(nStr));                 
                        delete[]nStr;                      
                        char* nnnStr = new char[strlen(str) - (j - i + 1) + strlen(nnStr)];
                        for (int p = 0; p < i; p++) {
                            nnnStr[p] = str[p];
                        }                      
                        for (int p = i, r = 0; p < i + strlen(nnStr); p++, r++) {
                            nnnStr[p] = nnStr[r];
                        }                      
                        for (int p = i + strlen(nnStr), r = j + 1; p < strlen(nnnStr); p++, r++) {
                            nnnStr[p] = str[r];
                        }
                        nnnStr[strlen(str) - (j - i + 1) + strlen(nnStr)] = '\0';
                        delete[]nnStr;
                        //delete[]str;
                        str = nnnStr;
                        z = 1;
                        break;
                    }
                    if (str[j] == '(') {
                        i = j - 1;
                        break;
                    }
                }
            }
            if (z == 1) {
                break;
            }
        }
    }
    return str;
}

char* brackets(char* str) {
    int bracketsCount = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '(') {
            bracketsCount++;
        }
    }
    if (bracketsCount == 0) {
        return str;
    }
    int left, right;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '(') {
            left = i;
        }
        if (str[i] == ')') {
            right = i;
            break;
        }
    }
    char* nStr = new char[right - left];
    for (int j = left + 1, m = 0; j < right; j++, m++) {
        nStr[m] = str[j];
    }
    nStr[right - left - 1] = '\0';
    char* nnStr = plusMinusCalcV2(multDivideCalc(nStr));
    delete[]nStr;
    char* nnnStr = new char[strlen(str) - (right - left) + strlen(nnStr)];
    for (int i = 0; i < left; i++) {
        nnnStr[i] = str[i];
    }
    for (int i = 0; i < strlen(nnStr); i++) {
        nnnStr[left + i] = nnStr[i];
    }
    for (int i = right + 1, j = 0; i < strlen(str); i++, j++) {
        nnnStr[left + strlen(nnStr) + j] = str[i];
    }
    nnnStr[strlen(str) - (right - left) + strlen(nnStr) - 1] = '\0';
    return brackets(nnnStr);
}

