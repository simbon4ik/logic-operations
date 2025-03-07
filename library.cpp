#include <iostream>
#include <algorithm>
#include "library.h"

bool l_or(string str){      //Логическое или для строки типа "0 OR 1" 
    return str[0] == '1' || str[5] == '1';
}

bool l_and(string str){    //Логическое и
    return str[0] == '1' && str[6] == '1';
}

bool l_not(string str){    //Логическое отрицание
    return not(str[4] - '0');
}

void replace_args(string str, vector<string> l_vars, int index){        //Функция замены аргументов на "0" и "1"
    if (index == l_vars.size()){            //Всё заменили
        std::cout << str;
        foo(str);                           //Считаем логические операции
        std::cout << "-> " << str << std::endl;    //Выводим результат для данных переменных
        return;
    }
    string l_var = l_vars[index];   //Строка (аргумент) для замены
    int size_l_var = l_var.size();  //Размер строки
    //Подставляем 0
    string str_with_0 = str; //Строка для заполнения 0 (чтобы потом можно было еще на 1 заменить и не испортить исходную str)
    int pos = 0;           //С какой позиции искать (для find)
    size_t start = str_with_0.find(l_var, pos);
    while (start != std::string::npos){
        pos = start + 1;
        if (start > 0 && isalpha(str_with_0[start - 1])) {        //Проверка, если переменная "A", чтобы она не была в "AND"
            start = str_with_0.find(l_var, pos);
            continue;
        }
        if (start + size_l_var < str_with_0.size() && isalpha(str_with_0[start + size_l_var])) {
            start = str_with_0.find(l_var, pos);
            continue;
        }
        str_with_0.replace(start, size_l_var, "0");
        start = str_with_0.find(l_var, pos);
    }

    replace_args(str_with_0, l_vars, index + 1);    //Вызываем рекурсивно для след.аргумента
    
    //Подставляем 1
    pos = 0;           //С какой позиции искать (для find)
    start = str.find(l_var, pos);
    while (start != std::string::npos){
        pos = start + 1;
        if (start > 0 && isalpha(str[start - 1])) {        //Проверка, если переменная "A", чтобы она не была в "AND"
            start = str.find(l_var, pos);
            continue;
        }
        if (start + size_l_var < str.size() && isalpha(str[start + size_l_var])) {
            start = str.find(l_var, pos);
            continue;
        }
        str.replace(start, size_l_var, "1");
        start = str.find(l_var, pos);
    }
    replace_args(str, l_vars, index + 1);   //Аналогично для 1 
     
    return;
}

void foo(string& str){  
    int index = 0;
    int pos = 0;
    int pos_end = str.size();

    while ((index = str.rfind("(")) != std::string::npos) {     //rfind, чтобы избежать вложенных скобок (начинаем либо с крайнего правого, либо с внутр.
        int index_out = str.find(")", index + 1);

        string str_with_staples = str.substr(index + 1, index_out - index - 1);
        foo(str_with_staples); // Рекурсивный вызов для выражения внутри скобок
        str.replace(index, index_out - index + 1, str_with_staples);
    }

    while ( (index = str.find("NOT") ) != std::string::npos){
        str.replace(index , 5, std::to_string(l_not(str.substr(index, 5))));
    }
    while ( (index = str.find("AND") ) != std::string::npos){
        str.replace(index - 2 , 7, std::to_string(l_and(str.substr(index - 2, 7))));
    }
    while ( (index = str.find("OR") ) != std::string::npos){
        str.replace(index - 2 , 6, std::to_string(l_or(str.substr(index - 2, 6))));
    }
}
