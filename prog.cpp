#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

void foo(string& str);
bool l_not(string str);
void replace_args(string str, vector<string> l_vars, int index);

int main(){
   // printf("%d\n",l_not("NOT 0"));
   // string str1 = "0 OR 0";
    string str2 = "var1 OR var2 AND NOT var3";
    str2 += ' ';    //Чтобы считать последнюю переменную
    vector<string> l_vars;
    string l_var;
    for (char symbol : str2) {
        if (symbol == '(' || symbol == ')')
            continue;
        if (symbol == ' '){
            if ( (l_var != "OR") && (l_var != "AND") && (l_var != "NOT") && (std::count(l_vars.begin(), l_vars.end(), l_var) == 0 ))
                l_vars.push_back(l_var);
            l_var.clear();
            continue;
        }
        l_var += symbol;
    }
    std::cout << "l_vars.size " << l_vars.size() << std::endl;
    replace_args(str2, l_vars, 0);
    
    //foo(str2);
    return 0;
}

bool l_or(string str){
    return str[0] == '1' || str[5] == '1';
}

bool l_and(string str){
    return str[0] == '1' && str[6] == '1';
}

bool l_not(string str){
    return not(str[4] - '0');
}

void replace_args(string str, vector<string> l_vars, int index){
    if (index == l_vars.size()){
        //foo()
        std::cout << str << std::endl;
        return;
    }
    string l_var = l_vars[index];
    int size_l_var = l_var.size();
    //Подставляем 0
    string str_with_0 = str; //Строка для заполнения 0
    int pos = 0;           //С какой позиции искать (для find)
    size_t start = str_with_0.find(l_var, pos);
    while (start != std::string::npos){
        pos += start;
        str_with_0.replace(start, size_l_var, "0");
        start = str_with_0.find(l_var, pos);
    }
    replace_args(str_with_0, l_vars, index + 1);
       
    //Подставляем 1
    pos = 0;           //С какой позиции искать (для find)
    start = str.find(l_var, pos);
    while (start != std::string::npos){
        pos += start;
        str.replace(start, size_l_var, "1");
        start = str.find(l_var, pos);
    }
    replace_args(str, l_vars, index + 1);
     
    return;
}

void foo(string& str){
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
