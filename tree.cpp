#include "tree.h"

Node *new_leaf(string data)
 {
    Node *leaf = new struct Node;
    leaf->data = data;
    return leaf;
}

