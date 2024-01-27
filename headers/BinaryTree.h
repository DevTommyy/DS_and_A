#ifndef BINARYTREE_H
#define BINARYTREE_H

// Define the Node structure
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} typedef TreeNode;

// Define the BinaryTree structure
struct BinaryTree {
    TreeNode* root;
    int len;
} typedef BinaryTree;

// Function prototypes
TreeNode* tree_get(TreeNode* current, int val);
TreeNode* tree_getParent(TreeNode* current, int val);

void tree_insert(BinaryTree* tree, int val);
void tree_insertTreeNode(TreeNode* current, TreeNode* node);

bool tree_delete(BinaryTree* tree, int val);

bool tree_contains(TreeNode* current, int val);
bool tree_compare(TreeNode* self, TreeNode* other);

int tree_min(TreeNode* current);
int tree_max(TreeNode* current);

void tree_printInorder(TreeNode* node);
void tree_freeAll(TreeNode* node);

#endif /* BINARYTREE_H */
