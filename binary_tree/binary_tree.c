#include<stdio.h>
#include<stdlib.h>

struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} typedef Node;

struct Tree {
    Node* root;
    int len;
} typedef Tree;

typedef enum {true = 1, false = 0} bool;

void insert(Tree* tree, int val);
void insertNode(Node* current, Node* node);
bool contains(Node* current, int val);
Node* get(Node* current, int val);
Node* getParent(Node* current, int val);
bool delete(Tree* tree, int val);
int min(Node* current);
int max(Node* current);
void printInorder(Node* node);
void freeAll(Node* node);

/// gets a node from the tree given it's value
///  
/// # Returns
/// A `NULL` pointer if the node isn't found
/// A `Node` pointer if the value is found 
Node* get(Node* current, int val) {
    if (current == NULL) {
        return NULL;
    } else {
        if (val == current->val) {
            return current;
        } else if (val < current->val) {
            return get(current->left, val);
        } else {
            return get(current->right, val);
        }
        return NULL;
    }
}

/// gets the parent of a node given the child value
/// 
/// # Returns
/// A `NULL` pointer if the parent node isn't found
/// A `Node` pointer if the parent node is found 
Node* getParent(Node* current, int val) {
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
        return getParent(current->left, val);
    } else {
        return getParent(current->right, val);
    }
}

/// inserts a node into the tree if its the root
/// or calls an helper function to insert it
/// 
/// # Params
///
/// `tree` the `Tree` in which to insert
/// `val` an int representing the value to insert
void insert(Tree* tree, int val) {
    tree->len++;

    Node* node = malloc(sizeof(Node));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    if (tree->root == NULL) {
        tree->root = node;
    } else {
        Node* current = tree->root;
        insertNode(current, node);
    }
}

/// inserts a node into the tree
/// 
/// # Params
///
/// `current` the root of the `Tree`
/// `val` an int representing the value to insert
void insertNode(Node* current, Node* node) {
    if (node->val < current->val) {
        // inserting in the left
        if (current->left == NULL) {
            current->left = node;
        } else {
            insertNode(current->left, node);
        }
    } else {
        // inserting in the right
        if (current->right == NULL) {
            current->right = node;
        } else {
            insertNode(current->right, node);
        }
    }
}

/// checks if a node is in the tree
/// 
/// # Params
/// `current` the root of the `Tree`
/// `val` an int representing the value to check for
///
/// # Returns
/// A `true` if the value is found 
/// A `false` if the value isn't found
bool contains(Node* current, int val) {
    if (current == NULL) {
        return false;
    } else {
        if (current->val == val) {
        return true;
        } else if (current->val < val) {
            contains(current->left, val);
        } else {
            contains(current->right, val);
        }
        return false;
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

/// deletes the node with the value provided
/// 
/// # Params
/// 
/// `tree` a `Tree` pointer of the tree to check
/// `val` an `int` representing the value to delete
bool delete(Tree* tree, int val) {
    Node* to_remove = get(tree->root, val);
    // if the tree is NULL or no node with the value to remove exists return false
    // case 1 and 2
    if (tree->len == 0 || to_remove == NULL) {
        return false;
    } else {
        // if we are here it means that a node was found
        Node* parent = getParent(tree->root, val);
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
            Node* largest_parent = to_remove;
            Node* largest = to_remove->left;
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
                getParent(tree->root, largest->val)->right = largest->left;
            }
            free(largest);
        }
        tree->len--;
        return true;
    }
}

/// finds the smallest value in a tree
int min(Node* current) {
    if (current->left == NULL) {
        return current->val;
    } else {
        return min(current->left);
    }
}

/// finds the biggest value in a tree
int max(Node* current) {
    if (current->right == NULL) {
        return current->val;
    } else {
        return min(current->right);
    }
}

/// prints the tree in orders based on where you put the print
void printInorder(Node* node) {
    if (node != NULL) {
        printf("%d ", node->val); // if print is there, from start to end (preorder)
        printInorder(node->left); // if print is there root is in the centre (inorder)
        printInorder(node->right); // if print is there from end to start (postorder)
        // as the comments say the order should be what is in the parentheses but inorder
        // is actually like this
    }
}

/// frees all the memory allocated by the list
void freeAll(Node* node) {
    if (node != NULL) {
        freeAll(node->left);
        freeAll(node->right);
        free(node);
    }
}

// some random testing generated by chatGPT
int main() {
    // Create an empty tree
    Tree* tree = malloc(sizeof(Tree));
    tree->root = NULL;
    tree->len = 0;

    // Test insert function
    insert(tree, 10);
    insert(tree, 5);
    insert(tree, 15);
    insert(tree, 3);
    insert(tree, 7);
    insert(tree, 12);
    insert(tree, 17);

    // Test printInorder function
    printf("Inorder traversal: ");
    printInorder(tree->root);
    printf("\n");

    // Test contains function
    printf("Tree contains 10: %s\n", contains(tree->root, 10) ? "true" : "false");
    printf("Tree contains 8: %s\n", contains(tree->root, 8) ? "true" : "false");

    // Test get function
    printf("Node with value 5: %p (represented as memory location, 0x0 means NULL)\n", get(tree->root, 5));
    printf("Node with value 20: %p (represented as memory location, 0x0 means NULL)\n", get(tree->root, 20));

    // Test delete function
    printf("Deleting node with value 5: %s\n", delete(tree, 5) ? "true" : "false");
    printf("Inorder traversal after deletion: ");
    printInorder(tree->root);
    printf("\n");

    // Test min and max functions
    printf("Minimum value in the tree: %d\n", min(tree->root));
    printf("Maximum value in the tree: %d\n", max(tree->root));

    // Free allocated memory
    freeAll(tree->root);
    free(tree);

    return 0;
}