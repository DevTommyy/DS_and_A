#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

struct Node {
    int val;
    struct Node* left;
    struct Node* right;
    int height;
} typedef Node;

struct Tree {
    Node* root;
} typedef Tree;

void left_rotation(Node* root);
void right_rotation(Node* root);
void check_balance(Node* current);

/* 
 * Most of those implementation are the same as
 * for a normal binary tree, apart for something
 * on the insert logic but mostly the delete
 * changes a bit, the others i think remain the same
 */
void insert(Tree* tree, int val);
void insertNode(Node* current, Node* node);

bool contains(Node* current, int val);
Node* get(Node* current, int val);
Node* getParent(Node* current, int val);

bool compare(Node* self, Node* other);

bool delete(Tree* tree, int val);
// a stack (in this case a deque implementation) is needed for this

int main() {
    return 0;
}