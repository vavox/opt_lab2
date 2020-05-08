#include "lexer.h"
#include "main.h"


int show(ofstream &fout1, ofstream &fout2)
{
    
    
     for (Lexem lex : lexem_tab) 
     {
        fout1 << "|" << left << setw(12) << lex.value << "| " << left << setw(4) << lex.code << " | " << left << setw(4) << lex.row << " | " << left << setw(4) << lex.column << " |" << endl;
        cout << "|" << left << setw(12) << lex.value << "| " << left << setw(4) << lex.code << " | " << left << setw(4) << lex.row << " | " << left << setw(4) << lex.column << " |" << endl;
        
        fout2 << "|" << left << setw(12) << lex.value << "| " << left << setw(4) << lex.code << " | " << left << setw(4) << lex.row << " | " << left << setw(4) << lex.column << " |" << endl;
    }

    for(Lexer_error lex_error : error_tab)
    {
        if (lex_error.type != 0)
        {
            cout << "Lexer Error: ";
            fout1 << "Lexer Error: ";
            fout2 << "Lexer Error: ";
            if (lex_error.type == 50)
            {
                cout << "unclosed comment, " << "row " << lex_error.row << ", column " << lex_error.column << endl;
                fout1 << "unclosed comment, " << "row " << lex_error.row << ", column " << lex_error.column << endl; 
                fout2 << "unclosed comment, " << "row " << lex_error.row << ", column " << lex_error.column << endl; 
         
            }
            else 
            {
                if (lex_error.type == 60)
                {
                    cout << "Illegal symbol: " << lex_error.sym << ", " << "row " << lex_error.row << ", column " << lex_error.column <<  endl;
                    fout1 << "Illegal symbol: " << lex_error.sym << ", " << "row " << lex_error.row << ", column " << lex_error.column <<  endl;
                    fout2 << "Illegal symbol: " << lex_error.sym << ", " << "row " << lex_error.row << ", column " << lex_error.column <<  endl;
                }
            }
        }
    }
    

    cout << endl << "Constant table:" << endl;
    fout1 << endl << "Constant table:" << endl;
    fout2 << endl << "Constant table:" << endl;
    for(Constant cons : cons_tab)
    {
        cout << cons.value << " --- " << cons.code << endl;
        fout1 << cons.value << " --- " << cons.code << endl;
        fout2 << cons.value << " --- " << cons.code << endl;
    }
    
    cout << endl << "Identifier table:" << endl;
    fout1 << endl << "Identifier table:" << endl;
    fout2 << endl << "Identifier table:" << endl;
    for(Identifier ident : ident_tab)
    {
        cout << ident.value << " --- " << ident.code << endl;
        fout1 << ident.value << " --- " << ident.code << endl;
        fout2 << ident.value << " --- " << ident.code << endl;
    }
    
    return 0;
}