#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct Symbol 
{
    int attr;
    char value;
};

struct Lexem 
{
    string value;
    int code;
    int row;
    int column;
};

struct Lexer_error
{
    int type;
    int row;
    int column;
    char sym;
};

struct Constant 
{
    string value;
    int code;
};

struct Identifier 
{
    string value;
    int code;
};
