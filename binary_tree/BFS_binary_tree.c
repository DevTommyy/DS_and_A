#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include"../headers/LinkedList.h"

struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} typedef Node;

struct Tree {
    Node* root;
    int len;
} typedef Tree;

// typedef enum {true = 1, false = 0} bool; declared in linked_list

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

int min(Node* current) {
    if (current->left == NULL) {
        return current->val;
    } else {
        return min(current->left);
    }
}

int max(Node* current) {
    if (current->right == NULL) {
        return current->val;
    } else {
        return min(current->right);
    }
}

void printInorder(Node* node) {
    if (node != NULL) {
        printf("%d ", node->val); // if print is there, from start to end
        printInorder(node->left); // if print is there root is in the centre
        printInorder(node->right); // if print is there from end to start
    }
}



void freeAll(Node* node) {
    if (node != NULL) {
        freeAll(node->left);
        freeAll(node->right);
        free(node);
    }
}

int main() {
    Tree* tree = malloc(sizeof(Tree));
    tree->root = NULL;
    tree->len = 0;

    LinkedList* list = malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;

    insert(tree, 50);
    insert(tree, 30);
    insert(tree, 20);
    insert(tree, 40);
    insert(tree, 70);
    insert(tree, 60);
    insert(tree, 80);

    printf("Inorder traversal of the tree: ");
    printInorder(tree->root);
    printf("\n");

    printf("Deleting 20 from the tree...\n");
    delete(tree, 20);
    printf("Inorder traversal after deletion: ");
    printInorder(tree->root);
    printf("\n");

    printf("Deleting 30 from the tree...\n");
    delete(tree, 30);
    printf("Inorder traversal after deletion: ");
    printInorder(tree->root);
    printf("\n");

    printf("Deleting 50 (root) from the tree...\n");
    delete(tree, 50);
    printf("Inorder traversal after deletion: ");
    printInorder(tree->root);
    printf("\n");


    // Free memory
    freeAll(tree->root);

    return 0;
}
// TODO implement BreadthFirstSearch
// TODO fix this to use the linkedlist as a queue and add docs

/*
    1) algorithm BreadthFirst(root)
    2) 3) 4) 5) 6) 7) 8) 9)
    10) if root.Right ̸= ∅
    11) q.Enqueue(root.Right)
    12) end if
    Pre: root is the root node of the BST
    Post: the nodes in the BST have been visited in breadth first order q ← queue
    while root ̸= ∅
    yield root.Value if root.Left ̸= ∅
    q.Enqueue(root.Left) end if
    13) if !q.IsEmpty()
    14) root ← q.Dequeue()
    15) else
    16) root ← ∅
    17) end if
    18) end while
    19) end BreadthFirst 
 */