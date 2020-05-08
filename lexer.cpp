#include "lexer.h"
#include "main.h"

int _const = 501; // const begin value
int _identif = 1001; // identifier begin value
int attributes[256];

map<int, int> const_tab;
map<string, int> identif_tab;
map<string, int> keyword_tab = {{"PROGRAM", 401}, {"PROCEDURE", 402}, {"BEGIN", 403}, {"END", 404}, {"LABEL", 405}};

deque<Lexem> lexem_tab;
vector<Lexer_error> error_tab;
vector<Constant> cons_tab;
vector<Identifier> ident_tab;

Symbol get_symbol(ifstream &fin) 
{
    Symbol temp_sym;
    fin.get(temp_sym.value);
    temp_sym.attr = attributes[int(temp_sym.value)];
    return temp_sym;
}

int lexer(ifstream &fin)//, vector<Lexem> &lexem_tab, vector<Lexer_error> &error_tab, vector<Constant> &cons_tab, vector<Identifier> &ident_tab)
{
    Symbol symbol;
    Lexem lex;
    Lexer_error lex_error;
    Constant cons;
    Identifier ident;
    int constant, _constant, keyword, identif;
    int column_num = 1, row_num = 1;
    int i;
    int l = 0, k = 0;
    string temp_symb = "";
    lex_error.type = 0;
    string temp;
  
    

    for (i = 0; i <= 255; ++i) { attributes[i] = 6; }


    attributes[32] = 0; // space symbol
    for (i = 8; i <= 13; i++) { attributes[i] = 0; }
    // digits
    for (i = 48; i <= 57; i++) { attributes[i] = 1; }
    // letters
    for (i = 65; i <= 90; i++) { attributes[i] = 2; }


    attributes[44] = 3;  // ,
    attributes[46] = 3;  // .
    attributes[58] = 3;  // :
    attributes[59] = 3;  // ;


    attributes[40] = 5;  // (
    attributes[41] = 3;  // )

    

    

    symbol = get_symbol(fin);
    while (!fin.eof())
    {
        temp = "";
        k = 0;
        lex.code = 0;
        switch (symbol.attr) 
        {

            case 0:  // space symbols
                while ((!fin.eof()) && (symbol.attr == 0)) 
                {
                    if (symbol.value == int('\n')) 
                    {
                        row_num++;
                        column_num = 0;
                    }
                    symbol = get_symbol(fin);
                    column_num++;
                    
                }
                lex.code = 0;
                break;

            case 1:  // digits
                lex.row = row_num;
                lex.column = column_num;
                
                while ((!fin.eof()) && (symbol.attr == 1)) 
                {
                    temp += symbol.value;
                    symbol = get_symbol(fin);
                    column_num++;
                }
                constant = stoi(temp);
                _constant = constant_search(constant);
                if (_constant != -1) 
                {
                    lex.value = temp;
                    lex.code = _constant;
                   
                    cons.code = lex.code;
                    cons.value = lex.value;
                    k = 1;
                } 
                else 
                {
                    lex.value = temp;
                    lex.code = constant_tab(constant);
                    
                    cons.code = lex.code;
                    cons.value = lex.value;
                    k = 1;
                }
                break;

            case 2:  // letters
                lex.row = row_num;
                lex.column = column_num;
                while ((!fin.eof()) && ((symbol.attr == 2) || (symbol.attr == 1))) 
                {
                    temp += symbol.value;
                    symbol = get_symbol(fin);
                    column_num++;
                }
                keyword = keyword_search(temp);
                lex.value = temp;
                
                if (keyword != -1)
                {
                    lex.code = keyword;
                    
                } 
                else 
                {
                    identif = identifier_search(temp);
                    if (identif != -1) 
                    {
                        lex.code = identif;
                        
                    }
                    else 
                    {
                        lex.code = identifier_tab(temp);
                        
                        ident.code = lex.code;
                        ident.value = temp;
                        l = 1;
                    }
                }
                break;

            case 3:  // single char delimiters
                lex.value = symbol.value;
                lex.row = row_num;
                lex.column = column_num;
                lex.code = int(symbol.value);
                //lex.code = attributes[symbol.value];
               
                symbol = get_symbol(fin);
                column_num++;
                break;
                

            case 4:
                cout << "Case 4" << endl;
                break;

            case 5:
                if (fin.eof()) 
                {
                    lex.row = row_num;
                    lex.column = column_num;
                    lex.code = symbol.attr;
                } 
                else 
                {
                    if(symbol.value == int('('))
                    {
                        temp_symb = symbol.value;
                        symbol = get_symbol(fin);
                        lex_error.column = column_num;
                        lex_error.row = row_num;
                        column_num++;

                        if (symbol.value == int('*')) 
                        {
                            if (fin.eof()) 
                            {
                                lex_error.type = 50;
                                lex_error.row = row_num;
                            } 
                            else 
                            {
                                symbol = get_symbol(fin);
                                column_num++;
                                if (symbol.value == int('\n')) 
                                    {
                                        row_num++;
                                        column_num = 0;
                                    }
                                while (symbol.value != int(')')) 
                                {
                                    while ((!fin.eof()) && (symbol.value != int('*'))) 
                                    {
                                        temp += symbol.value;
                                        symbol = get_symbol(fin);
                                        column_num++;
                                        if (symbol.value == int('\n')) 
                                        {
                                            row_num++;
                                            column_num = 0;
                                        }
                                    }
                                    if (fin.eof()) 
                                    {
                                        lex_error.type = 50;
                                        symbol.value = int('+');
                                        break;
                                    } 
                                    else 
                                    {
                                        symbol = get_symbol(fin);
                                        column_num++;
                                    }
                                    
                                }

                                if (!fin.eof()) 
                                {
                                    symbol = get_symbol(fin);
                                    column_num++;
                                }
                            }
                        }
                        else
                        {
                            lex.value = temp_symb;
                            lex.row = row_num;
                            lex.column = column_num;
                            //lex.code = attributes[int('(')];
                            lex.code = int('(');
                           
                            column_num++;
                        }
                        break;
                    }
                }
                break;

            case 6:
                cout << "case6" << endl;
                lex_error.row = row_num;
                lex_error.column = column_num;
                lex_error.sym = symbol.value;
                lex_error.type = 60;
                break;
        }
        
        if(lex.code != 0)
        {
            lexem_tab.push_back(lex);
            if(k == 1)
            {
                cons_tab.push_back(cons);
                k = 0;
            }
            if(l == 1)
            {
                ident_tab.push_back(ident);
                l = 0;
            }
        }

        if(lex_error.type != 0)
        {
            error_tab.push_back(lex_error);
            break;
        }
        
       
    }



    return 0;
}


int keyword_search(string tmp) 
{
    map<string, int>::iterator it;
    it = keyword_tab.find(tmp);
    if (it != keyword_tab.end()) 
    {
        return it->second;
    }
    else
    {
        return -1;
    }
}

int identifier_tab(string tmp) 
{
    int value = identif_tab.size() + _identif;
    identif_tab.insert(make_pair(tmp, value));
    return value;
}

int identifier_search(string tmp) 
{
    map<string, int>::iterator it;
    it = identif_tab.find(tmp);
    if (it != identif_tab.end()) 
    {
        return it->second;
    }
    else
    {
        return -1;
    }
}

int constant_tab(int constant) 
{
    int value = const_tab.size() + _const;
    const_tab.insert(make_pair(constant, value));
    return value;
}

int constant_search(int constant) 
{
    map<int, int>::iterator it;
    it = const_tab.find(constant);
    if (it != const_tab.end()) 
    {
        return it->second;
    }
    else
    {
        return -1;
    }
}

int constcode_search(int code, map<int, int> &const_table) 
{
    map<int, int>::iterator it;
    for (it = const_table.begin(); it != const_table.end(); ++it)
    {
        if (it->second == code) return it->first;
    }
    return -1;
}

string identifcode_search(int code, map<string, int> &identif_table) 
{
    map<string, int>::iterator it;
    for (it = identif_table.begin(); it != identif_table.end(); ++it)
    {
        if (it->second == code) 
        {
            return it->first;
        }
    }
    return "empty";
}