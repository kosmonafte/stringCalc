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

    

    cout << countCalc(nStroka) << endl;
    cout << multDivideCalc(countCalc(nStroka)) << endl;
    cout << plusMinusCalcV2(multDivideCalc(countCalc(nStroka))) << endl;

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
    return *nStr;
}

char* floatToString(double number) {
    char larr[10], rarr[10];
    int leftPart, rightPart;
    char* nnStr;
    if (number < 0) {
        leftPart = number;
        rightPart = (-1) * (number - (float)leftPart) * 100.0;
    }
    else {
        leftPart = number;
        rightPart = (number - (float)leftPart) * 100.0;
    }
    cout << endl << leftPart << endl << rightPart << endl;
    _itoa_s(leftPart, larr, 10);
    _itoa_s(rightPart, rarr, 10);
    cout << endl << larr << endl << rarr << endl;
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
    cout << nStr << endl << signCount << endl;
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
                    cout << endl << number << endl;
                    cout << endl << atof(number) << endl;
                    strToNumber[k] = atof(number);
                    k++;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < signCount; i++) {
        cout << strToNumber[i] << " ";
    }
    cout << endl;
    // Считаем сумму числового массива
    double summ = 0;
    for (int i = 0; i < signCount; i++) {
        summ += strToNumber[i];
    }
    cout << endl << summ << endl;
    delete[]nStr;
    delete[]number;
    delete[]strToNumber;

    return floatToString(summ);
}

char* multDivideCalc(char* str) {
    char* nStr = &normalize(str);  //приводим строку к удобному виду
    /*for (int i = 0; i < strlen(nStr); i++) {
        cout << nStr[i];
    }*/

    int k = 0;
    for (int i = 0; i < strlen(nStr); i++) {            //считаем сколько в строке знаков "*" и "/"
        if (nStr[i] == '*' || nStr[i] == '/') {         //столько раз будем проходить циклом
            k++;
        }
    }
    char larr[10], rarr[10];
    char* leftNumber, * rightNumber, *nnStr, *nnnStr;
    double lN, rN, result;
    int leftPart, rightPart, countStartDel, countEndDel;
    //идем по строке пока не встретим знак "*" и "/",
    //если встретили то идем от знака обратно пока не встретим хоть какой другой знак,
    //потом от знака идем вперед пока не встретим хоть какой знак
    //парсим эти числа и пишем их во флот
    cout << endl << nStr << endl;
    for (int n = 0; n < k; n++) {
        int sizeToDel = 1;
        cout << endl << strlen(nStr) << endl;
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
                        cout << endl << leftNumber << endl;
                        lN = atof(leftNumber);
                        cout << endl << lN << endl;
                        delete[]leftNumber;
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
                        cout << endl << rightNumber << endl;
                        rN = atof(rightNumber);
                        cout << endl << rN << endl;
                        delete[]rightNumber;
                        break;
                    }
                }
                //считаем умножение или деление
                if (nStr[i] == '*') {
                    result = lN * rN;
                    cout << endl << result << endl;
                }
                if (nStr[i] == '/') {
                    result = lN / rN;
                    cout << endl << result << endl;
                }
                
                //переносим флот обратно в чар

                nnStr = floatToString(result);

                cout << endl << nnStr << " - ftos" << endl;
                //вписываем новую строку в старый массив при этом сразу меняя длину
                nnnStr = new char[strlen(nStr) - sizeToDel + strlen(nnStr) + 1];
                for (int j = 0; j < countStartDel; j++) {
                    nnnStr[j] = nStr[j];
                }
                cout << endl << nnnStr << endl;
                for (int j = countStartDel; j < strlen(nnStr) + countStartDel; j++) {
                    nnnStr[j] = nnStr[j - countStartDel];
                }
                cout << endl << nnnStr << endl;
                for (int j = countStartDel + strlen(nnStr); j < strlen(nnnStr); j++) {
                    nnnStr[j] = nStr[j + countEndDel - countStartDel - strlen(nnStr) + 1];
                }
                cout << endl << nnnStr << endl;
                nnnStr[strlen(nStr) - sizeToDel + strlen(nnStr)] = '\0'; //добавил проверить
                cout << endl << nnnStr << endl;
                delete[]nStr;
                delete[]nnStr;
                nStr = nnnStr;
                cout << endl << nStr << endl;
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
    char* strn = str;
    for (int n = 0; n < k; n++) {
        
        int z = 0;
        for (int i = 0; i < strlen(strn); i++) {
            if (strn[i] == '(') {
                for (int j = i + 1; j < strlen(strn); j++) {
                    if (strn[j] == ')') {
                        char* nStr = new char[j - i];
                        for (int l = i + 1, m = 0; l < j; l++, m++) {
                            nStr[m] = strn[l];
                        }
                        nStr[j - i - 1] = '\0';  
                        cout << endl << nStr << endl;
                        char* nnStr = plusMinusCalcV2(multDivideCalc(nStr));                 
                        delete[]nStr;                      
                        char* nnnStr = new char[strlen(strn) - (j - i + 1) + strlen(nnStr)];
                        for (int p = 0; p < i; p++) {
                            nnnStr[p] = strn[p];
                        }                      
                        for (int p = i, r = 0; p < i + strlen(nnStr); p++, r++) {
                            nnnStr[p] = nnStr[r];
                        }                      
                        for (int p = i + strlen(nnStr), r = j + 1; p < strlen(nnnStr); p++, r++) {
                            nnnStr[p] = strn[r];  
                        }
                        nnnStr[strlen(strn) - (j - i + 1) + strlen(nnStr)] = '\0';
                        strn = nnnStr;
                        z = 1;
                        break;
                    }
                    if (strn[j] == '(') {
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
    return strn;
}


