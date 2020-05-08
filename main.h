#pragma once

#include "struct_lexer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <iomanip> 

using namespace std;

extern deque<Lexem> lexem_tab;
extern vector<Lexer_error> error_tab;
extern vector<Constant> cons_tab;
extern vector<Identifier> ident_tab;


extern map<int, int> const_tab;
extern map<string, int> identif_tab;
extern map<string, int> keyword_tab;

;

int show(ofstream &fout1, ofstream &fout2);
int lexer(ifstream &fin);
