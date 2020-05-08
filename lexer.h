#pragma once

#include "struct_lexer.h"



#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

extern int _const;
extern int _identif;

int keyword_search(string tmp);
int constant_search(int constant);
int constant_tab(int constant);
int identifier_search(string tmp);
int identifier_tab(string tmp);
int lexer(ifstream &fin);



Symbol get_symbol(ifstream &fin);



int constcode_search(int code, map<int, int> &const_table);
string identifcode_search(int code, map<string, int> &identif_table);
