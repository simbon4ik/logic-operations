#ifndef LIBRARY
#define LIBRARY

#include <string>
#include <vector>

using std::string;
using std::vector;

void foo(string& str);
bool l_not(string str);
bool l_or(string str);
bool l_and(string str);
void replace_args(string str, vector<string> l_vars, int index);

#endif
