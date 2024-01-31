#ifndef BINARYTREE_H
#define BINARYTREE_H

/// The element in the tree
/// 
/// # Fields
///
/// - `val` an `int` representing the val contained
/// - `left` a pointer to the left child
/// - `right` a pointer to the right child
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} typedef TreeNode;

/// A `Binary Search Tree` data structure
///
/// # Fields
///
/// - `root` a pointer to the root node
/// - `len` an `int` representing the length of the tree
///
/// NOTE: every `O(log n)` operation
/// can become an `O(n)` operation in
/// the case of an higly unbalanced tree
struct BinaryTree {
    TreeNode* root;
    int len;
} typedef BinaryTree;

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
