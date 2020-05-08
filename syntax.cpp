#include "syntax.h"
#include "main.h"
#include "lexer.h"



Parser_error error;

Node* tree = new struct Node;

vector<Parser_error> pars_err;



bool Parser() 
{
    if (!signal_program(tree)) 
    {
        pars_err.push_back(error);
        return false;
    }
    return true;
}

bool signal_program(Node* root) 
{
    root->data = "<signal program>";
    return program(root);
}

bool program(Node* root) 
{
    bool proc = false;
    Node* leaf = root->add_leaf("<program>");
    if (lexem_tab.empty()) 
    {
        error.type = 0;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = "";
        return false;
    }
    if (lexem_tab.front().code == keyword_search("PROGRAM")) 
    {
        string token_code = to_string(lexem_tab.front().code);
        lexem_tab.pop_front();
        leaf->add_leaf(token_code + " PROGRAM");
    }
    else if(lexem_tab.front().code == keyword_search("PROCEDURE"))
    {
        string token_code = to_string(lexem_tab.front().code);
        lexem_tab.pop_front();
        leaf->add_leaf(token_code + " PROCEDURE");
        proc = true;
    } 
    else 
    {
        error.type = 4;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = "PROGRAM or PROCEDURE";
        return false;
    }
    if (!procedure_identifier(leaf)) { return false; }
    if (proc)
    {
        if(!procedure_list(leaf)) { return false; }
    }
    if (lexem_tab.empty()) 
    {
        error.type = 0;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = "";
        return false;
    }
    if (lexem_tab.front().code == 59) // ;
    {  
        lexem_tab.pop_front();
        leaf->add_leaf("59 ;");
    } 
    else 
    {
        error.type = 3;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = ";";
        return false;
    }
    if (!block(leaf)) { return false; }
    if (lexem_tab.empty()) 
    {
        return false;
    }
    if(proc)
    {
        if (lexem_tab.front().code == 59) // ;
        {  
            lexem_tab.pop_front();
            leaf->add_leaf("59 ;");
        } 
        else 
        {
            error.type = 3;
            error.row = lexem_tab.front().row;
            error.column = lexem_tab.front().column;
            error.str = ";";
            return false;
        }
    }
    else
    {
        if (lexem_tab.front().code == 46) // .
        {  
            lexem_tab.pop_front();
            leaf->add_leaf("46 .");
        } 
        else 
        {
            error.type = 3;
            error.row = lexem_tab.front().row;
            error.column = lexem_tab.front().column;
            error.str = ".";
            return false;
        }
    }
    
   
    if (!lexem_tab.empty()) 
    {
        error.type = 2;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = "";
        return false;
    }
    return true;
}

bool procedure_list(Node* root)
{
    Node* leaf = root->add_leaf("<procedure-list>");
    if(lexem_tab.front().code == 40)
    {
        lexem_tab.pop_front();
        leaf->add_leaf("40 (");
    }
    else 
    {
        error.type = 3;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = "(";
        return false;
    }
    if(!declarations_list(leaf)) { return false; }
    if(lexem_tab.front().code == 41)
    {
        lexem_tab.pop_front();
        leaf->add_leaf("41 )");
    }
    else 
    {
        error.type = 3;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = ")";
        return false;
    }
    return true;
}

bool procedure_identifier(Node* root) 
{
    Node* leaf = root->add_leaf("<procedure-identifier>");
    return identifier(leaf);
}

bool identifier(Node* root) 
{
    Node* leaf = root->add_leaf("<identifier>");
    
    if (lexem_tab.front().code / _identif == 1) 
    {
        string identif_name = identifcode_search(lexem_tab.front().code, identif_tab);
        string token_code = to_string(lexem_tab.front().code);
        lexem_tab.pop_front();
        leaf->add_leaf(token_code + " " + identif_name);
        return true;
    } 
    else 
    {
        error.type = 1;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = "";
        return false;
    }
}

bool block(Node* root) 
{
    Node* leaf = root->add_leaf("<block>");
    if (lexem_tab.empty()) 
    {
        error.type = 0;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = "";
        return false;
    }
    if (!declarations(leaf)) return false;
    if (lexem_tab.empty()) 
    {
        error.type = 0;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = "";
        return false;
    }
    if (lexem_tab.front().code == keyword_search("BEGIN")) 
    {
        
        string token_code = to_string(lexem_tab.front().code);
       
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column + 5;

        lexem_tab.pop_front();
        leaf->add_leaf(token_code + " BEGIN");
        
    } 
    else 
    {
        error.type = 4;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = "BEGIN";

        
        return false;
    }
    if (!statements_list(leaf)) return false;
    if (lexem_tab.empty()) 
    {
        error.type = 0;
        //error.row = lexem_tab.front().row;
        //error.column = lexem_tab.front().column;
        error.str = "";
        return false;
    }
    if (lexem_tab.front().code == keyword_search("END")) 
    {
        string token_code = to_string(lexem_tab.front().code);
       
        lexem_tab.pop_front();
        leaf->add_leaf(token_code + " END");
       
    } 
    else
    {
       
        error.type = 4;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = "END";
        return false;
    }
    return true;
}

bool declarations(Node* root) 
{
    Node* leaf = root->add_leaf("<declarations>");
    return label_declarations(leaf);
}

bool label_declarations(Node* root) 
{
    Node* leaf = root->add_leaf("<label-declarations>");
    if (lexem_tab.empty()) 
    {
        error.type = 0;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = "";
        return false;
    }
    if (lexem_tab.front().code == keyword_search("LABEL")) 
    {
        string token_code = to_string(lexem_tab.front().code);
        lexem_tab.pop_front();
        leaf->add_leaf(token_code + " LABEL");
    } 
    else 
    {
        leaf->add_leaf("<empty>");
        return true;
    }
    if (!unsigned_integer(leaf)) { return false; }
    if (lexem_tab.empty()) 
    {
        error.type = 0;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = "";
        return false;
    }
    if (!labels_list(leaf)) { return false; }
    if (lexem_tab.empty()) 
    {
        error.type = 0;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = "";
        return false;
    }
    if (lexem_tab.front().code == 59) //;
    {  
        lexem_tab.pop_front();
        leaf->add_leaf("59 ;");
    } 
    else 
    {
        error.type = 3;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = ";";
        return false;
    }
    return true;
}

bool unsigned_integer(Node* root) 
{
    Node* leaf = root->add_leaf("<unsigned-integer>");
    if (lexem_tab.empty()) 
    {
        error.type = 0;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = "";
        return false;
    }
    if (lexem_tab.front().code / _const == 1) 
    {
        int const_val = constcode_search(lexem_tab.front().code, const_tab);
        string token_code = to_string(lexem_tab.front().code);
        lexem_tab.pop_front();
        leaf->add_leaf(token_code + " '" + to_string(const_val) + "'");
        return true;

    } else 
    {
        error.type = 5;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = "";
        return false;
        return false;
    }
    return true;
}

bool labels_list(Node* root) 
{
    Node* leaf = root->add_leaf("<labels-list>");
    if (lexem_tab.empty()) 
    {
       error.type = 0;
        error.row = lexem_tab.front().row;
        error.column = lexem_tab.front().column;
        error.str = "";
        return false;
;
    }
    if (lexem_tab.front().code != 44) 
    {
        leaf->add_leaf("<empty>");
        return true;
    }
    if (lexem_tab.front().code == 44) // ,
    {  
        lexem_tab.pop_front();
        leaf->add_leaf("44 ,");
        if (!unsigned_integer(leaf)) return false;
        if (lexem_tab.empty()) 
        {
            error.type = 0;
            error.row = lexem_tab.front().row;
            error.column = lexem_tab.front().column;
            error.str = "";
            return false;
        }
        if (!labels_list(leaf)) return false;
    }
    return true;
}

bool statements_list(Node* root) 
{
    Node* leaf = root->add_leaf("<statements-list>");
    
    leaf->add_leaf("<empty>");
    
    return true;
}

bool declarations_list(Node* root) 
{
    Node* leaf = root->add_leaf("<declaration-list>");
    
    leaf->add_leaf("<empty>");

    return true;
}

