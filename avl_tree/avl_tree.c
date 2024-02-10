#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../headers/Deque.h"

#define MAX(a,b) ((a) > (b) ? (a) : (b))

struct Node {
    int val;
    struct Node* left;
    struct Node* right;
    int height;
} typedef Node;

struct Tree {
    Node* root;
    int len;
} typedef Tree;

int get_height(Node* node);
int get_balance(Node* node);
Node* get(Node* current, int val);
Node* getParent(Node* current, int val);

void left_rotation(Node** root);
void right_rotation(Node** root);
void check_balance(Node** current);

/* 
 * Most of those implementation are the same as
 * for a normal binary tree, apart for something
 * on the insert logic but mostly the delete
 * changes a bit, the others i think remain the same
 */
void insert(Tree* tree, int val);
void insertNode(Node** current, Node* node);

bool contains(Node* current, int val);
bool compare(Node* self, Node* other);

bool delete(Tree* tree, int val);
// a stack (in this case a deque implementation) is needed for this

void printInorder(Node* node);
void freeAll(Node* node);

int get_height(Node* node) {
    if(node == NULL) {
        return 0;
    }
    return node->height;
}

int get_balance(Node* node) {
    if (node == NULL) {
        return 0;
    }
    // calculate balance factor
    return get_height(node->left) - get_height(node->right);
}

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

void left_rotation(Node** root) {
    if(*root == NULL || (*root)->right == NULL)  return;

    Node* right_node = (*root)->right;
    (*root)->right = right_node->left;
    right_node->left = *root;
    *root = right_node;

    // update the new heights
    right_node->left->height = MAX(get_height(right_node->left->left), get_height(right_node->left->right)) + 1;
    right_node->height = MAX(get_height(right_node->left), get_height(right_node->right)) + 1;
}

void right_rotation(Node** root) {
    if(*root == NULL || (*root)->left == NULL)  return;

    Node* left_node = (*root)->left;
    (*root)->left = left_node->right;
    left_node->right = *root;
    *root = left_node;

    // update the new heights
    left_node->right->height = MAX(get_height(left_node->right->left), get_height(left_node->right->right)) + 1;
    left_node->height = MAX(get_height(left_node->left), get_height(left_node->right)) + 1;
}

void check_balance(Node** current) {
    int balance = get_balance(*current);
    printf("current: %d, balance, %d\n", (*current)->val, balance);
    // Perform rotations if necessary
    if (balance > 1) {
        if (get_balance((*current)->left) >= 0) {
            printf("right rotation\n");
            right_rotation(current);
        } else {
            printf("left and right rotation\n");
            left_rotation(&((*current)->left));
            right_rotation(current);
        }
    } else if (balance < -1) {
        if (get_balance((*current)->right) <= 0) {
            printf("left rotation\n");
            left_rotation(current);
        } else {
            printf("right and left rotation\n");
            right_rotation(&((*current)->right));
            left_rotation(current);
        }
    }
    // Update heights after rotations
    (*current)->height = MAX(get_height((*current)->left), get_height((*current)->right)) + 1;
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

    // initialize new node
    Node* node = malloc(sizeof(Node));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    if (tree->root == NULL) {
        tree->root = node;
    } else {
        insertNode(&(tree->root), node);
    }
}

/// inserts a node into the tree
/// 
/// # Params
///
/// `current` the root of the `Tree`
/// `val` an int representing the value to insert
void insertNode(Node** current, Node* node) {
    if (node->val < (*current)->val) {
        // inserting in the left
        if ((*current)->left == NULL) {
            (*current)->left = node;
        } else {
            insertNode(&((*current)->left), node);
        }
    } else {
        // inserting in the right
        if ((*current)->right == NULL) {
            (*current)->right = node;
        } else {
            insertNode(&((*current)->right), node);
        }
    }

    // Update heights before checking balance
    (*current)->height = MAX(get_height((*current)->left), get_height((*current)->right)) + 1;
    check_balance(current);
    printf("check balance returned, now the tree is: \n");
    printInorder(*current);
    printf("\n");
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
        } else if (val < current->val) {
            return contains(current->left, val);
        } else {
            return contains(current->right, val);
        }
        return false;
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
bool compare(Node* self, Node* other) {
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

bool delete(Tree* tree, int val) {
    Node* to_remove = get(tree->root, val);
    if (tree->len == 0 || to_remove == NULL) {
        return false;
    } else {
        Node* parent = NULL;
        Deque *path = (Deque *)malloc(sizeof(Deque));
        path->head = NULL;
        path->tail = NULL;
        
        Node* current = tree->root;
        while (current != NULL) {
            enqueue_front(path, current->val);
            if (val == current->val) {
                to_remove = current;
                break;
            } else if (val < current->val) {
                parent = current;
                current = current->left;
            } else {
                parent = current;
                current = current->right;
            }
        }
        if (tree->len == 1) {
            tree->root = NULL;
        } else if (to_remove->left == NULL && to_remove->right == NULL) {
            if (to_remove->val < parent->val) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        } else if (to_remove->left == NULL && to_remove->right != NULL) {
            if (to_remove->val < parent->val) {
                parent->left = to_remove->right;
            } else {
                parent->right = to_remove->right;
            }
        } else if (to_remove->left != NULL && to_remove->right == NULL) {
            if (to_remove->val < parent->val) {
                parent->left = to_remove->left;
            } else {
                parent->right = to_remove->left;
            }
        } else {
            Node* largest_parent = to_remove;
            Node* largest = to_remove->left;
            while (largest->right != NULL) {
                // find the biggest value of the left branch
                largest_parent = largest;
                largest = largest->right;
            }
            // Copy the value from largest to to_remove
            to_remove->val = largest->val;
            // Delete largest
            if (largest_parent->right == largest) {
                largest_parent->right = largest->left;
            } else {
                largest_parent->left = largest->left;
            }
            free(largest);
            largest = NULL;
        }
        while(path->head != NULL) {
            int val = dequeue_front(path);
            Node* to_check = get(tree->root, val);
            if (to_check == NULL) {
                continue;
            }
            check_balance(&to_check);
            // Update parent pointers after rotations
            Node* parent = getParent(tree->root, val);
            if (parent != NULL) {
                if (parent->left != NULL && parent->left->val == val) {
                    parent->left = to_check;
                } else if (parent->right != NULL && parent->right->val == val) {
                    parent->right = to_check;
                }
            }
        }
        tree->len--;
        free(path); // Free the Deque to prevent memory leaks
        return true;
    }
}



// =============================== UTILS ======================
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

// some random main generated by chatGPT
int main() {
    // Create an empty AVL tree
    Tree* avl_tree = malloc(sizeof(Tree));
    avl_tree->root = NULL;
    avl_tree->len = 0;

    // Insert some elements into the AVL tree
    insert(avl_tree, 10);
    insert(avl_tree, 5);
    insert(avl_tree, 15);
    insert(avl_tree, 3);
    insert(avl_tree, 7);
    insert(avl_tree, 12);
    insert(avl_tree, 17);

    printf("Inorder traversal of AVL tree after insertion: ");
    printInorder(avl_tree->root);
    printf("\n");

    // Check containment
    int val_to_check = 12;
    printf("AVL tree contains %d: %s\n", val_to_check, contains(avl_tree->root, val_to_check) ? "true" : "false");

    // Compare the AVL tree with itself
    printf("AVL tree is equal to itself: %s\n", compare(avl_tree->root, avl_tree->root) ? "true" : "false");

    // Delete an element from the AVL tree
    int val_to_delete = 5;
    printf("Deleting %d from AVL tree\n", val_to_delete);
    delete(avl_tree, val_to_delete);

    printf("Inorder traversal of AVL tree after deletion: ");
    printInorder(avl_tree->root);
    printf("\n");

    // Compare the AVL tree with itself after deletion
    printf("AVL tree is equal to itself after deletion: %s\n", compare(avl_tree->root, avl_tree->root) ? "true" : "false");

    // Free the memory allocated for the AVL tree
    freeAll(avl_tree->root);
    free(avl_tree);

    return 0;
}
