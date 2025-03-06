#include <iostream>
#include <string>
#include <vector>
#include <set>


using std::string;
using std::vector;
using std::set;
using std::string_view;

void foo(string& str);
bool l_not(string str);
int main(){
    
    printf("%d\n",l_not("NOT 0"));
    string str1 = "0 OR 0";
    string str2 = "var1 OR var2 AND NOT var3";
    str2 += ' ';    //Чтобы считать последнюю переменную
    set<string> l_vars;
    string l_var;
    for (char symbol : str2) {
        if (symbol == '(' || symbol == ')')
            continue;
        if (symbol == ' '){
            if ( (l_var != "OR") && (l_var != "AND") && (l_var != "NOT") )
                l_vars.insert(l_var);
            l_var.clear();
            continue;
        }
        l_var += symbol;
    }
    std::cout << "Len is " << l_vars.size() << std::endl;
    foo(str1);
    std::cout << str1 << std::endl;
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
