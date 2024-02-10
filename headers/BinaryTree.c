#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} typedef TreeNode;

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

/// Gets a node from the tree given it's value
/// in an `O(log n)` time.
///  
/// # Returns
/// - A `NULL` pointer if the node isn't found
/// - A `TreeNode` pointer if the value is found 
TreeNode* tree_get(TreeNode* current, int val) {
    if (current == NULL) {
        return NULL;
    } else {
        if (val == current->val) {
            return current;
        } else if (val < current->val) {
            return tree_get(current->left, val);
        } else {
            return tree_get(current->right, val);
        }
        return NULL;
    }
}

/// Gets the parent of a node given the child value
/// in an `O(log n)` time.
///  
/// 
/// # Returns
/// - A `NULL` pointer if the parent node isn't found
/// - A `TreeNode` pointer if the parent node is found 
TreeNode* tree_getParent(TreeNode* current, int val) {
    if (current == NULL || current->val == val) {
        // No parent or the node itself is the root
        return NULL; 
    }

    if ((current->left != NULL && current->left->val == val) ||
        (current->right != NULL && current->right->val == val)) {
        // Found the parent of the node
        return current; 
    }

    // Recursively search in left and right subtrees
    if (val < current->val) {
        return tree_getParent(current->left, val);
    } else {
        return tree_getParent(current->right, val);
    }
}

/// Inserts a node into the tree if its the root
/// or calls an helper function to insert it.
/// 
/// # Params
///
/// - `tree` the `BinaryTree` in which to insert
/// - `val` an int representing the value to insert
void tree_insert(BinaryTree* tree, int val) {
    tree->len++;

    TreeNode* node = malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    if (tree->root == NULL) {
        tree->root = node;
    } else {
        TreeNode* current = tree->root;
        tree_insertTreeNode(current, node);
    }
}

/// Inserts a node into the tree in an `O(log n)` time.
/// 
/// # Params
///
/// - `current` the root of the `BinaryTree`
/// - `val` an int representing the value to insert
void tree_insertTreeNode(TreeNode* current, TreeNode* node) {
    if (node->val < current->val) {
        // inserting in the left
        if (current->left == NULL) {
            current->left = node;
        } else {
            tree_insertTreeNode(current->left, node);
        }
    } else {
        // inserting in the right
        if (current->right == NULL) {
            current->right = node;
        } else {
            tree_insertTreeNode(current->right, node);
        }
    }
}

/// # Cases
/// - the tree is empty 
/// - the val is not in the tree
/// - the node is the root
/// - the node is a leaf
/// - the node has a right subtrree
/// - the node has a left subtree
/// - the node has both subtrees

/// Deletes the node with the value provided in an `O(log n)` time.
/// 
/// # Params
/// 
/// `tree` a `BinaryTree` pointer of the tree to check
/// `val` an `int` representing the value to delete
bool tree_delete(BinaryTree* tree, int val) {
    TreeNode* to_remove = tree_get(tree->root, val);
    // if the tree is NULL or no node with the value to remove exists return false
    // case 1 and 2
    if (tree->len == 0 || to_remove == NULL) {
        return false;
    } else {
        // if we are here it means that a node was found
        TreeNode* parent = tree_getParent(tree->root, val);
        // case 3, removing the root
        if (tree->len == 1) {
            tree->root = NULL;
        } else if (to_remove->left == NULL && to_remove->right == NULL) {
            // case 4 the node is a leaf
            if (to_remove->val < parent->val) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        } else if (to_remove->left == NULL && to_remove->right != NULL) {
            // case 5 the node has a right subtree
            if (to_remove->val < parent->val) {
                parent->left = to_remove->right;
            } else {
                parent->right = to_remove->right;
            }
        } else if (to_remove->left != NULL && to_remove->right == NULL) {
            // case 6 the node has a left subtree
            if (to_remove->val < parent->val) {
                parent->left = to_remove->left;
            } else {
                parent->right = to_remove->left;
            }
        } else {
            // case 7 the node has both subtrees
            TreeNode* largest_parent = to_remove;
            TreeNode* largest = to_remove->left;
            while (largest->right != NULL) {
                largest_parent = largest;
                largest = largest->right;
            }

            if (largest_parent == to_remove) {
                // If the largest node is directly the left child of to_remove
                to_remove->left = largest->left;
            } else {
                // If the largest node is deeper in the left subtree
                largest_parent->right = largest->left;
            }

            to_remove->val = largest->val;
            // Adjust parent pointers to maintain binary search tree properties
            if (largest->left != NULL) {
                tree_getParent(tree->root, largest->val)->right = largest->left;
            }
            free(largest);
        }
        tree->len--;
        return true;
    }
}

/// Checks if a node is in the tree in an `O(log n)` time.
/// 
/// # Params
/// `current` the root of the `BinaryTree`
/// `val` an int representing the value to check for
///
/// # Returns
/// A `true` if the value is found 
/// A `false` if the value isn't found
bool tree_contains(TreeNode* current, int val) {
    if (current == NULL) {
        return false;
    } else {
        if (current->val == val) {
            return true;
        } else if (val < current->val) {
            return tree_contains(current->left, val);
        } else {
            return tree_contains(current->right, val);
        }
    }
}

/// compares two trees
///
/// # Parameters 
///
/// `self` a `Node*` to the first tree
/// `other` a `Node*` to the second tree
///
/// # Returns 
/// 
/// `true` if they are equal, `false` if they arent
bool tree_compare(TreeNode* self, TreeNode* other) {
    // If both nodes are NULL, they are equal
    if (self == NULL && other == NULL) {
        return true;
    }
    // If one node is NULL while the other isn't, they are not equal
    if (self == NULL || other == NULL) {
        return false;
    }

    // Compare values and recursively check left and right subtrees
    return (self->val == other->val) &&
           compare(self->left, other->left) &&
           compare(self->right, other->right);
}

/// finds the smallest value in a tree in an `O(log n)` time.
int tree_min(TreeNode* current) {
    if (current->left == NULL) {
        return current->val;
    } else {
        return tree_min(current->left);
    }
}

/// finds the biggest value in a tree in an `O(log n)` time.
int tree_max(TreeNode* current) {
    if (current->right == NULL) {
        return current->val;
    } else {
        return tree_max(current->right);
    }
}

/// prints the tree in orders based on where you put the print
/// this operation takes `O(n)` time
void tree_printInorder(TreeNode* node) {
    if (node != NULL) {
        printf("%d ", node->val); // if print is there, from start to end (preorder)
        tree_printInorder(node->left); // if print is there root is in the centre (inorder)
        tree_printInorder(node->right); // if print is there from end to start (postorder)
        // as the comments say the order should be what is in the parentheses but inorder
        // is actually like this
    }
}

/// frees all the memory allocated by the list
/// this operation takes `O(n)` time
void tree_freeAll(TreeNode* node) {
    if (node != NULL) {
        tree_freeAll(node->left);
        tree_freeAll(node->right);
        free(node);
    }
}