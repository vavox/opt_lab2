#pragma once

#include "tree.h"


struct Parser_error 
{
    int type;
    int row;
    int column;
    string str;
};


bool Parser();
bool signal_program(Node* tree);
bool program(Node* root);
bool procedure_identifier(Node* root);
bool identifier(Node* root);
bool block(Node* root);
bool declarations(Node* root);
bool statements_list(Node* root);
bool label_declarations(Node* root);
bool unsigned_integer(Node* root);
bool labels_list(Node* root);
bool declarations_list(Node* root);
bool procedure_list(Node* root);

extern Node* tree;

void show_error();
void print_tree(const string prefix, struct Node *node, bool last, ofstream &fout);

extern vector<Parser_error> pars_err;