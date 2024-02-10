#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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
void insertNode(Node* current, Node* node);

bool contains(Node* current, int val);
Node* get(Node* current, int val);
Node* getParent(Node* current, int val);
bool compare(Node* self, Node* other);

bool delete(Tree* tree, int val); // a stack (in this case a deque implementation) is needed for this

void printInorder(Node* node);
void freeAll(Node* node);

// `O(1)`
void left_rotation(Node** root) {
    // there is used a pointer to a pointer so after the rotation
    // what points to the root of the rotation is updated simply
    if(*root == NULL || (*root)->right == NULL)  return;

    // perform the rotation
    Node* right_node = (*root)->right;
    (*root)->right = right_node->left;
    right_node->left = *root;
    // update the root of the rotation by deferencing the pointer
    *root = right_node;
}

// `O(1)`
void right_rotation(Node** root) {
    if(*root == NULL || (*root)->left == NULL)  return;

    // perform the rotation
    Node* left_node = (*root)->left;
    (*root)->left = left_node->right;
    left_node->right = *root;
    // update the root of the rotation by deferencing the pointer
    *root = left_node;
}

void check_balance(Node** current) {
    if (*current == NULL) return;

    int left_height = ((*current)->left != NULL) ? (*current)->left->height : -1;
    int right_height = ((*current)->right != NULL) ? (*current)->right->height : -1;

    (*current)->height = MAX(left_height, right_height) + 1;

    if (left_height - right_height > 1) {
        if (((*current)->left->left != NULL ? (*current)->left->left->height : -1) - 
            ((*current)->left->right != NULL ? (*current)->left->right->height : -1) > 0) {
            right_rotation(current);
        } else {
            left_rotation(current);
            right_rotation(current);
        }
    } else if (right_height - left_height > 1) {
        if (((*current)->right->left != NULL ? (*current)->right->left->height : -1) - 
            ((*current)->right->right != NULL ? (*current)->right->right->height : -1) < 0) {
            left_rotation(current);
        } else {
            right_rotation(current);
            left_rotation(current);
        }
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
    node->height = 0;
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
    check_balance(&current);
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

// compares two trees
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
        Node* parent = NULL;

        // Deque to store the path from root to the node to be removed
        Deque *path = (Deque *)malloc(sizeof(Deque));
        path->head = NULL;
        path->tail = NULL;
        // push all the elements before the one to remove into
        // a stack like structure
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
        // if we are here it means that a node was found
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
        // check the balance aftere the deletion
        while(path->head != NULL) {
            Node* to_check = get(tree->root, dequeue_front(path));
            check_balance(&to_check);
        }
        tree->len--;
        return true;
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

// some random test main done by chatGPT
int main() {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->root = NULL;
    tree->len = 0;

    // Insert some elements into the tree
    insert(tree, 5);
    insert(tree, 3);
    insert(tree, 7);
    insert(tree, 2);
    insert(tree, 4);
    insert(tree, 6);
    insert(tree, 8);

    printf("Inorder traversal before deletion: ");
    printInorder(tree->root);
    printf("\n");

    // Test deletion
    printf("Deleting node with value 2...\n");
    delete(tree, 2); // Deleting a leaf node
    printf("Inorder traversal after deletion of 2: ");
    printInorder(tree->root);
    printf("\n");

    printf("Deleting node with value 7...\n");
    delete(tree, 7); // Deleting a node with both subtrees
    printf("Inorder traversal after deletion of 7: ");
    printInorder(tree->root);
    printf("\n");

    // Test contains function
    int value_to_find = 5;
    if (contains(tree->root, value_to_find)) {
        printf("The tree contains the value %d\n", value_to_find);
    } else {
        printf("The tree does not contain the value %d\n", value_to_find);
    }

    // Test get function
    int value_to_get = 6;
    Node* node_found = get(tree->root, value_to_get);
    if (node_found != NULL) {
        printf("Found node with value %d\n", value_to_get);
    } else {
        printf("Node with value %d not found\n", value_to_get);
    }

    // Test getParent function
    int child_value = 4;
    Node* parent_node = getParent(tree->root, child_value);
    if (parent_node != NULL) {
        printf("Parent of node with value %d is %d\n", child_value, parent_node->val);
    } else {
        printf("Node with value %d is root or not found\n", child_value);
    }

    // Test compare function
    Tree* tree_copy = (Tree*)malloc(sizeof(Tree));
    tree_copy->root = NULL;
    tree_copy->len = 0;
    printf("Inserting 5\n");
    insert(tree_copy, 5);
    printf("traversal after 5: ");
    printInorder(tree_copy->root);
    printf("\n");
    printf("Inserting 3\n");
    insert(tree_copy, 3);
    printf("traversal after 3: ");
    printInorder(tree_copy->root);
    printf("\n");
    printf("Inserting 4\n");
    insert(tree_copy, 4);
    printf("traversal after 4: ");
    printInorder(tree_copy->root);
    printf("\n");
    printf("Inserting 6\n");
    insert(tree_copy, 6);
    printf("traversal after 6: ");
    printInorder(tree_copy->root);
    printf("\n");
    printf("Inserting 8\n");
    insert(tree_copy, 8);
    printf("traversal after 8: ");
    printInorder(tree_copy->root);
    printf("\n");
    // insert(tree_copy, 7);
    // insert(tree_copy, 2);

    printf("Inorder traversal of the copy: ");
    printInorder(tree_copy->root);
    printf("\n");

    if (compare(tree->root, tree_copy->root)) {
        printf("The trees are identical\n");
    } else {
        printf("The trees are different\n");
    }

    // Free all allocated memory
    freeAll(tree->root);
    free(tree);
    freeAll(tree_copy->root);
    free(tree_copy);

    return 0;
}
