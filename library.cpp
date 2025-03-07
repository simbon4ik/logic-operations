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
        std::cout << " -> " << str << std::endl;    //Выводим результат для данных переменных
        return;
    }
    string l_var = l_vars[index];   //Строка (аргумент) для замены
    int size_l_var = l_var.size();  //Размер строки
    //Подставляем 0
    string str_with_0 = str; //Строка для заполнения 0 (чтобы потом можно было еще на 1 заменить и не испортить исходную str)
    int pos = 0;           //С какой позиции искать (для find)
    size_t start = str_with_0.find(l_var, pos);
    while (start != std::string::npos){
        pos += start;
        str_with_0.replace(start, size_l_var, "0");
        start = str_with_0.find(l_var, pos);
    }

    replace_args(str_with_0, l_vars, index + 1);    //Вызываем рекурсивно для след.аргумента
    
    //Подставляем 1
    pos = 0;           //С какой позиции искать (для find)
    start = str.find(l_var, pos);
    while (start != std::string::npos){
        pos += start;
        str.replace(start, size_l_var, "1");
        start = str.find(l_var, pos);
    }
    replace_args(str, l_vars, index + 1);   //Аналогично для 1 
     
    return;
}

void foo(string& str){  //need to add proccesing ()
    int index = 0;
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
