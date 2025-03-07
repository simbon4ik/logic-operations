#include <iostream>
#include <algorithm>
#include "library.h"

int main(){
    string str2 = "(var1 OR var2) AND NOT var3";      //Пробная строка
    str2 += ' ';    //Чтобы считать последнюю переменную
    vector<string> l_vars;  //Вектор переменных
    string l_var;           //Переменная, которую считываем
    for (char symbol : str2) {
        if (symbol == '(' || symbol == ')')
            continue;
        if (symbol == ' '){
            if ( (l_var != "OR") && (l_var != "AND") && (l_var != "NOT") && (std::count(l_vars.begin(), l_vars.end(), l_var) == 0 ))
                l_vars.push_back(l_var);    //Добавляем, если считанная строка не AND, NOT, OR и еще нет в векторе
            l_var.clear();
            continue;
        }
        l_var += symbol;
    }

    replace_args(str2, l_vars, 0);      //Заменяем аргументы на их значения (0/1)
    
    return 0;
}
