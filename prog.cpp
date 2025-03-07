#include <iostream>
#include <algorithm>
#include "library.h"

int main(){
    //string str = "var3 OR ((var1 OR var2) AND NOT var3)";      //Пробная строка, где переменные повторяются
    string str = "(A AND B) OR (C AND NOT D)";                   //Пробная строка по тз
    //string str = "var4 OR ((var1 OR var2) AND NOT var3)";      //Пробная строка на 4 переменных
    str += ' ';    //Чтобы считать последнюю переменную
    
    vector<string> l_vars = find_l_vars(str);  //Вектор переменных

    replace_args(str, l_vars, 0);      //Заменяем аргументы на их значения (0/1) и считаем результат
    
    return 0;
}
