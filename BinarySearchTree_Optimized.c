#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// BST Node structure
typedef struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
    int height;  // For potential AVL balancing
} BSTNode;

// Stack for iterative operations
typedef struct StackNode {
    BSTNode* node;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
} Stack;

// Queue for level-order traversal
typedef struct QueueNode {
    BSTNode* node;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Function prototypes
BSTNode* create_node(int data);
BSTNode* insert_recursive(BSTNode* root, int data);
BSTNode* insert_iterative(BSTNode* root, int data);
BSTNode* delete_node(BSTNode* root, int data);
BSTNode* find_min(BSTNode* root);
BSTNode* find_max(BSTNode* root);
BSTNode* search_recursive(BSTNode* root, int data);
BSTNode* search_iterative(BSTNode* root, int data);

// Traversal functions
void inorder_recursive(BSTNode* root);
void preorder_recursive(BSTNode* root);
void postorder_recursive(BSTNode* root);
void inorder_iterative(BSTNode* root);
void preorder_iterative(BSTNode* root);
void postorder_iterative(BSTNode* root);
void level_order_traversal(BSTNode* root);

// Tree analysis functions
int tree_height(BSTNode* root);
int tree_size(BSTNode* root);
bool is_valid_bst(BSTNode* root);
bool is_valid_bst_helper(BSTNode* root, int min_val, int max_val);
int count_leaves(BSTNode* root);
void print_tree_structure(BSTNode* root, int level);

// Utility functions
void free_tree(BSTNode* root);
BSTNode* copy_tree(BSTNode* root);
void print_tree_info(BSTNode* root);

// Stack operations
Stack* create_stack();
void push(Stack* stack, BSTNode* node);
BSTNode* pop(Stack* stack);
bool is_stack_empty(Stack* stack);
void free_stack(Stack* stack);

// Queue operations
Queue* create_queue();
void enqueue(Queue* queue, BSTNode* node);
BSTNode* dequeue(Queue* queue);
bool is_queue_empty(Queue* queue);
void free_queue(Queue* queue);

int main() {
    BSTNode* root = NULL;
    int choice, value;
    BSTNode* result;
    
    printf("=== Optimized Binary Search Tree ===\n");
    
    while (1) {
        printf("\n=== BST OPERATIONS MENU ===\n");
        printf("1.  Insert (Recursive)\n");
        printf("2.  Insert (Iterative)\n");
        printf("3.  Delete\n");
        printf("4.  Search (Recursive)\n");
        printf("5.  Search (Iterative)\n");
        printf("6.  Inorder Traversal (Recursive)\n");
        printf("7.  Inorder Traversal (Iterative)\n");
        printf("8.  Preorder Traversal (Recursive)\n");
        printf("9.  Preorder Traversal (Iterative)\n");
        printf("10. Postorder Traversal (Recursive)\n");
        printf("11. Postorder Traversal (Iterative)\n");
        printf("12. Level Order Traversal\n");
        printf("13. Display Tree Structure\n");
        printf("14. Tree Statistics\n");
        printf("15. Validate BST\n");
        printf("16. Clear Tree\n");
        printf("17. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                if (scanf("%d", &value) == 1) {
                    root = insert_recursive(root, value);
                    printf("Value %d inserted successfully (recursive).\n", value);
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 2:
                printf("Enter value to insert: ");
                if (scanf("%d", &value) == 1) {
                    root = insert_iterative(root, value);
                    printf("Value %d inserted successfully (iterative).\n", value);
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 3:
                if (!root) {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("Enter value to delete: ");
                if (scanf("%d", &value) == 1) {
                    root = delete_node(root, value);
                    printf("Value %d deleted successfully.\n", value);
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 4:
                if (!root) {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("Enter value to search: ");
                if (scanf("%d", &value) == 1) {
                    result = search_recursive(root, value);
                    printf("Value %d %s in the tree (recursive search).\n", 
                           value, result ? "found" : "not found");
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 5:
                if (!root) {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("Enter value to search: ");
                if (scanf("%d", &value) == 1) {
                    result = search_iterative(root, value);
                    printf("Value %d %s in the tree (iterative search).\n", 
                           value, result ? "found" : "not found");
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 6:
                if (!root) {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("Inorder Traversal (Recursive): ");
                inorder_recursive(root);
                printf("\n");
                break;
                
            case 7:
                if (!root) {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("Inorder Traversal (Iterative): ");
                inorder_iterative(root);
                printf("\n");
                break;
                
            case 8:
                if (!root) {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("Preorder Traversal (Recursive): ");
                preorder_recursive(root);
                printf("\n");
                break;
                
            case 9:
                if (!root) {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("Preorder Traversal (Iterative): ");
                preorder_iterative(root);
                printf("\n");
                break;
                
            case 10:
                if (!root) {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("Postorder Traversal (Recursive): ");
                postorder_recursive(root);
                printf("\n");
                break;
                
            case 11:
                if (!root) {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("Postorder Traversal (Iterative): ");
                postorder_iterative(root);
                printf("\n");
                break;
                
            case 12:
                if (!root) {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("Level Order Traversal: ");
                level_order_traversal(root);
                printf("\n");
                break;
                
            case 13:
                if (!root) {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("Tree Structure:\n");
                print_tree_structure(root, 0);
                break;
                
            case 14:
                if (!root) {
                    printf("Tree is empty!\n");
                    break;
                }
                print_tree_info(root);
                break;
                
            case 15:
                if (!root) {
                    printf("Tree is empty (valid BST)!\n");
                    break;
                }
                printf("Tree is %s valid BST.\n", 
                       is_valid_bst(root) ? "a" : "not a");
                break;
                
            case 16:
                if (root) {
                    free_tree(root);
                    root = NULL;
                    printf("Tree cleared successfully.\n");
                } else {
                    printf("Tree is already empty.\n");
                }
                break;
                
            case 17:
                if (root) {
                    free_tree(root);
                }
                printf("Exiting program...\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

BSTNode* create_node(int data) {
    BSTNode* new_node = (BSTNode*)malloc(sizeof(BSTNode));
    if (!new_node) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    
    return new_node;
}

BSTNode* insert_recursive(BSTNode* root, int data) {
    if (root == NULL) {
        return create_node(data);
    }
    
    if (data < root->data) {
        root->left = insert_recursive(root->left, data);
    } else if (data > root->data) {
        root->right = insert_recursive(root->right, data);
    }
    // If data equals root->data, we don't insert (no duplicates)
    
    return root;
}

BSTNode* insert_iterative(BSTNode* root, int data) {
    BSTNode* new_node = create_node(data);
    if (!new_node) return root;
    
    if (root == NULL) {
        return new_node;
    }
    
    BSTNode* current = root;
    BSTNode* parent = NULL;
    
    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            // Duplicate found, don't insert
            free(new_node);
            return root;
        }
    }
    
    if (data < parent->data) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    
    return root;
}

BSTNode* delete_node(BSTNode* root, int data) {
    if (root == NULL) {
        return root;
    }
    
    if (data < root->data) {
        root->left = delete_node(root->left, data);
    } else if (data > root->data) {
        root->right = delete_node(root->right, data);
    } else {
        // Node to be deleted found
        
        // Case 1: Node with no children (leaf)
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        
        // Case 2: Node with one child
        if (root->left == NULL) {
            BSTNode* temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            BSTNode* temp = root->left;
            free(root);
            return temp;
        }
        
        // Case 3: Node with two children
        BSTNode* temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data);
    }
    
    return root;
}

BSTNode* find_min(BSTNode* root) {
    if (root == NULL) return NULL;
    
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

BSTNode* find_max(BSTNode* root) {
    if (root == NULL) return NULL;
    
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

BSTNode* search_recursive(BSTNode* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    
    if (data < root->data) {
        return search_recursive(root->left, data);
    }
    
    return search_recursive(root->right, data);
}

BSTNode* search_iterative(BSTNode* root, int data) {
    while (root != NULL) {
        if (data == root->data) {
            return root;
        } else if (data < root->data) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return NULL;
}

void inorder_recursive(BSTNode* root) {
    if (root != NULL) {
        inorder_recursive(root->left);
        printf("%d ", root->data);
        inorder_recursive(root->right);
    }
}

void preorder_recursive(BSTNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder_recursive(root->left);
        preorder_recursive(root->right);
    }
}

void postorder_recursive(BSTNode* root) {
    if (root != NULL) {
        postorder_recursive(root->left);
        postorder_recursive(root->right);
        printf("%d ", root->data);
    }
}

void inorder_iterative(BSTNode* root) {
    Stack* stack = create_stack();
    BSTNode* current = root;
    
    while (current != NULL || !is_stack_empty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }
        
        current = pop(stack);
        printf("%d ", current->data);
        current = current->right;
    }
    
    free_stack(stack);
}

void preorder_iterative(BSTNode* root) {
    if (root == NULL) return;
    
    Stack* stack = create_stack();
    push(stack, root);
    
    while (!is_stack_empty(stack)) {
        BSTNode* current = pop(stack);
        printf("%d ", current->data);
        
        if (current->right) {
            push(stack, current->right);
        }
        if (current->left) {
            push(stack, current->left);
        }
    }
    
    free_stack(stack);
}

void postorder_iterative(BSTNode* root) {
    if (root == NULL) return;
    
    Stack* stack1 = create_stack();
    Stack* stack2 = create_stack();
    
    push(stack1, root);
    
    while (!is_stack_empty(stack1)) {
        BSTNode* current = pop(stack1);
        push(stack2, current);
        
        if (current->left) {
            push(stack1, current->left);
        }
        if (current->right) {
            push(stack1, current->right);
        }
    }
    
    while (!is_stack_empty(stack2)) {
        BSTNode* current = pop(stack2);
        printf("%d ", current->data);
    }
    
    free_stack(stack1);
    free_stack(stack2);
}

void level_order_traversal(BSTNode* root) {
    if (root == NULL) return;
    
    Queue* queue = create_queue();
    enqueue(queue, root);
    
    while (!is_queue_empty(queue)) {
        BSTNode* current = dequeue(queue);
        printf("%d ", current->data);
        
        if (current->left) {
            enqueue(queue, current->left);
        }
        if (current->right) {
            enqueue(queue, current->right);
        }
    }
    
    free_queue(queue);
}

int tree_height(BSTNode* root) {
    if (root == NULL) return 0;
    
    int left_height = tree_height(root->left);
    int right_height = tree_height(root->right);
    
    return 1 + (left_height > right_height ? left_height : right_height);
}

int tree_size(BSTNode* root) {
    if (root == NULL) return 0;
    
    return 1 + tree_size(root->left) + tree_size(root->right);
}

bool is_valid_bst(BSTNode* root) {
    return is_valid_bst_helper(root, INT_MIN, INT_MAX);
}

bool is_valid_bst_helper(BSTNode* root, int min_val, int max_val) {
    if (root == NULL) return true;
    
    if (root->data <= min_val || root->data >= max_val) {
        return false;
    }
    
    return is_valid_bst_helper(root->left, min_val, root->data) &&
           is_valid_bst_helper(root->right, root->data, max_val);
}

int count_leaves(BSTNode* root) {
    if (root == NULL) return 0;
    
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    
    return count_leaves(root->left) + count_leaves(root->right);
}

void print_tree_structure(BSTNode* root, int level) {
    if (root == NULL) return;
    
    print_tree_structure(root->right, level + 1);
    
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("%d\n", root->data);
    
    print_tree_structure(root->left, level + 1);
}

void print_tree_info(BSTNode* root) {
    printf("\n=== Tree Statistics ===\n");
    printf("Tree Height: %d\n", tree_height(root));
    printf("Tree Size: %d\n", tree_size(root));
    printf("Number of Leaves: %d\n", count_leaves(root));
    printf("Is Valid BST: %s\n", is_valid_bst(root) ? "Yes" : "No");
    
    BSTNode* min_node = find_min(root);
    BSTNode* max_node = find_max(root);
    printf("Minimum Value: %d\n", min_node ? min_node->data : 0);
    printf("Maximum Value: %d\n", max_node ? max_node->data : 0);
}

void free_tree(BSTNode* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

// Stack implementation
Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack) {
        stack->top = NULL;
    }
    return stack;
}

void push(Stack* stack, BSTNode* node) {
    StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
    if (new_node) {
        new_node->node = node;
        new_node->next = stack->top;
        stack->top = new_node;
    }
}

BSTNode* pop(Stack* stack) {
    if (is_stack_empty(stack)) return NULL;
    
    StackNode* temp = stack->top;
    BSTNode* node = temp->node;
    stack->top = temp->next;
    free(temp);
    
    return node;
}

bool is_stack_empty(Stack* stack) {
    return stack->top == NULL;
}

void free_stack(Stack* stack) {
    while (!is_stack_empty(stack)) {
        pop(stack);
    }
    free(stack);
}

// Queue implementation
Queue* create_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue) {
        queue->front = NULL;
        queue->rear = NULL;
    }
    return queue;
}

void enqueue(Queue* queue, BSTNode* node) {
    QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
    if (new_node) {
        new_node->node = node;
        new_node->next = NULL;
        
        if (queue->rear == NULL) {
            queue->front = queue->rear = new_node;
        } else {
            queue->rear->next = new_node;
            queue->rear = new_node;
        }
    }
}

BSTNode* dequeue(Queue* queue) {
    if (is_queue_empty(queue)) return NULL;
    
    QueueNode* temp = queue->front;
    BSTNode* node = temp->node;
    queue->front = temp->next;
    
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    
    free(temp);
    return node;
}

bool is_queue_empty(Queue* queue) {
    return queue->front == NULL;
}

void free_queue(Queue* queue) {
    while (!is_queue_empty(queue)) {
        dequeue(queue);
    }
    free(queue);
}