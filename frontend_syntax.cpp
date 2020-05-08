#include "syntax.h"
#include "main.h"

void show_error() 
{
    for(Parser_error error: pars_err)
    {
        cout << endl << "Parser Error: ";

        switch (error.type)
        {
        case 0:
            cout << "Unexpected end of the file at row: " << error.row << " column: " << error.column << endl;
            break;
        case 1:
            cout << "There`s no expected identifier at row: " << error.row << " column: " << error.column << endl;
            break;
        case 2:
            cout << "Unexpected tokens (after the end of the program) at row: " << error.row << " column: " << error.column << endl;
            break;    
        case 3:
            cout << "There`s no expected symbol '" << error.str << "' at row: " << error.row << " column: " << error.column << endl;
            break;
        case 4:
            cout << "There`s no expected keyword '" << error.str << "' at row: " << error.row << " column: " << error.column << endl;
            break;
        case 5:
            cout << "There`s no expected constant at row: " << error.row << " column: " << error.column << endl;
            break;
        }
    }
    
}

void print_tree(const string prefix, struct Node *node, bool last, ofstream &fout) 
{
    
    if (node == nullptr) return;
    int leaf_size = node->leafs.size();
    cout << prefix;
    fout << prefix;

    cout << (last ? "|__" : "|__");
    fout << (last ? "|__" : "|__");

    cout << node->data << endl;
    fout << node->data << endl;
    
    for (int i = 0; i < leaf_size; i++)
    {
        if (i == leaf_size - 1)
        {
            print_tree(prefix + (last ? "|   " : "    "), node->leafs[i], false, fout);
        } 
        else 
        {
            print_tree(prefix + (last ? "|   " : "    "), node->leafs[i], true, fout);
        }
    }
}


