#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>

#define MAX_SIZE 1000
#define MAX_VERTICES 100
#define QUEUE_SIZE 100
#define INSERTION_SORT_THRESHOLD 10

// =============================================================================
// COMMON DATA STRUCTURES AND UTILITIES
// =============================================================================

// Generic swap function
void swap_ints(int* a, int* b) {
    if (a != b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
}

// Print array utility
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Check if array is sorted
bool is_sorted_ascending(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) return false;
    }
    return true;
}

bool is_sorted_descending(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[i - 1]) return false;
    }
    return true;
}

// Generate random array
void generate_random_array(int arr[], int n, int max_value) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % max_value;
    }
}

// =============================================================================
// 1. GRAPH TRAVERSAL (BFS/DFS) IMPLEMENTATION
// =============================================================================

// Graph node for adjacency list
typedef struct GraphNode {
    int vertex;
    struct GraphNode* next;
} GraphNode;

// Graph structure
typedef struct Graph {
    int num_vertices;
    GraphNode** adj_list;
    bool* visited;
} Graph;

// Queue for BFS
typedef struct Queue {
    int items[QUEUE_SIZE];
    int front, rear;
} Queue;

// Stack for DFS
typedef struct Stack {
    int items[QUEUE_SIZE];
    int top;
} Stack;

// Graph functions
Graph* create_graph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) return NULL;
    
    graph->num_vertices = vertices;
    graph->adj_list = (GraphNode**)calloc(vertices, sizeof(GraphNode*));
    graph->visited = (bool*)calloc(vertices, sizeof(bool));
    
    if (!graph->adj_list || !graph->visited) {
        free(graph->adj_list);
        free(graph->visited);
        free(graph);
        return NULL;
    }
    
    return graph;
}

void add_edge(Graph* graph, int src, int dest) {
    // Add edge from src to dest
    GraphNode* new_node = (GraphNode*)malloc(sizeof(GraphNode));
    if (!new_node) return;
    
    new_node->vertex = dest;
    new_node->next = graph->adj_list[src];
    graph->adj_list[src] = new_node;
    
    // For undirected graph, add edge from dest to src
    new_node = (GraphNode*)malloc(sizeof(GraphNode));
    if (!new_node) return;
    
    new_node->vertex = src;
    new_node->next = graph->adj_list[dest];
    graph->adj_list[dest] = new_node;
}

void reset_visited(Graph* graph) {
    memset(graph->visited, false, graph->num_vertices * sizeof(bool));
}

// Queue operations
Queue* create_queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q) {
        q->front = -1;
        q->rear = -1;
    }
    return q;
}

void enqueue(Queue* q, int value) {
    if (q->rear == QUEUE_SIZE - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

int dequeue(Queue* q) {
    if (q->front == -1 || q->front > q->rear) return -1;
    int item = q->items[q->front++];
    if (q->front > q->rear) q->front = q->rear = -1;
    return item;
}

bool is_queue_empty(Queue* q) {
    return q->front == -1 || q->front > q->rear;
}

// Stack operations
Stack* create_stack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (s) s->top = -1;
    return s;
}

void push(Stack* s, int value) {
    if (s->top < QUEUE_SIZE - 1) {
        s->items[++s->top] = value;
    }
}

int pop(Stack* s) {
    return (s->top >= 0) ? s->items[s->top--] : -1;
}

bool is_stack_empty(Stack* s) {
    return s->top == -1;
}

// BFS implementation
void bfs(Graph* graph, int start_vertex) {
    reset_visited(graph);
    Queue* queue = create_queue();
    
    graph->visited[start_vertex] = true;
    enqueue(queue, start_vertex);
    
    printf("BFS traversal: ");
    while (!is_queue_empty(queue)) {
        int current_vertex = dequeue(queue);
        printf("%d ", current_vertex);
        
        GraphNode* adjacent = graph->adj_list[current_vertex];
        while (adjacent) {
            int adj_vertex = adjacent->vertex;
            if (!graph->visited[adj_vertex]) {
                graph->visited[adj_vertex] = true;
                enqueue(queue, adj_vertex);
            }
            adjacent = adjacent->next;
        }
    }
    printf("\n");
    free(queue);
}

// DFS implementation
void dfs(Graph* graph, int start_vertex) {
    reset_visited(graph);
    Stack* stack = create_stack();
    
    push(stack, start_vertex);
    printf("DFS traversal: ");
    
    while (!is_stack_empty(stack)) {
        int current_vertex = pop(stack);
        
        if (!graph->visited[current_vertex]) {
            graph->visited[current_vertex] = true;
            printf("%d ", current_vertex);
            
            GraphNode* adjacent = graph->adj_list[current_vertex];
            while (adjacent) {
                if (!graph->visited[adjacent->vertex]) {
                    push(stack, adjacent->vertex);
                }
                adjacent = adjacent->next;
            }
        }
    }
    printf("\n");
    free(stack);
}

void free_graph(Graph* graph) {
    if (!graph) return;
    
    for (int i = 0; i < graph->num_vertices; i++) {
        GraphNode* current = graph->adj_list[i];
        while (current) {
            GraphNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    
    free(graph->adj_list);
    free(graph->visited);
    free(graph);
}

// =============================================================================
// 2. QUICKSORT IMPLEMENTATION
// =============================================================================

typedef enum {
    FIRST_ELEMENT,
    LAST_ELEMENT,
    MIDDLE_ELEMENT,
    MEDIAN_OF_THREE,
    RANDOM_ELEMENT
} PivotStrategy;

typedef struct {
    int low, high;
} StackFrame;

typedef struct {
    StackFrame frames[MAX_SIZE];
    int top;
} QSStack;

void init_qs_stack(QSStack* stack) {
    stack->top = -1;
}

void qs_push(QSStack* stack, int low, int high) {
    if (stack->top < MAX_SIZE - 1) {
        stack->top++;
        stack->frames[stack->top].low = low;
        stack->frames[stack->top].high = high;
    }
}

bool qs_pop(QSStack* stack, int* low, int* high) {
    if (stack->top >= 0) {
        *low = stack->frames[stack->top].low;
        *high = stack->frames[stack->top].high;
        stack->top--;
        return true;
    }
    return false;
}

bool qs_is_empty(QSStack* stack) {
    return stack->top == -1;
}

int median_of_three(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    
    if (arr[low] > arr[mid]) swap_ints(&arr[low], &arr[mid]);
    if (arr[mid] > arr[high]) swap_ints(&arr[mid], &arr[high]);
    if (arr[low] > arr[mid]) swap_ints(&arr[low], &arr[mid]);
    
    return mid;
}

int select_pivot(int arr[], int low, int high, PivotStrategy strategy) {
    switch (strategy) {
        case FIRST_ELEMENT: return low;
        case LAST_ELEMENT: return high;
        case MIDDLE_ELEMENT: return low + (high - low) / 2;
        case MEDIAN_OF_THREE: return median_of_three(arr, low, high);
        case RANDOM_ELEMENT: return low + rand() % (high - low + 1);
        default: return high;
    }
}

int partition(int arr[], int low, int high, PivotStrategy strategy) {
    int pivot_index = select_pivot(arr, low, high, strategy);
    swap_ints(&arr[pivot_index], &arr[high]);
    int pivot = arr[high];
    
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap_ints(&arr[i], &arr[j]);
        }
    }
    
    swap_ints(&arr[i + 1], &arr[high]);
    return i + 1;
}

void insertion_sort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void quicksort_hybrid(int arr[], int low, int high, PivotStrategy strategy) {
    if (low < high) {
        if (high - low + 1 <= INSERTION_SORT_THRESHOLD) {
            insertion_sort(arr, low, high);
            return;
        }
        
        int pivot_index = partition(arr, low, high, strategy);
        quicksort_hybrid(arr, low, pivot_index - 1, strategy);
        quicksort_hybrid(arr, pivot_index + 1, high, strategy);
    }
}

void quicksort_iterative(int arr[], int low, int high, PivotStrategy strategy) {
    QSStack stack;
    init_qs_stack(&stack);
    qs_push(&stack, low, high);
    
    while (!qs_is_empty(&stack)) {
        int current_low, current_high;
        qs_pop(&stack, &current_low, &current_high);
        
        if (current_low < current_high) {
            int pivot_index = partition(arr, current_low, current_high, strategy);
            
            if (pivot_index - current_low > current_high - pivot_index) {
                qs_push(&stack, current_low, pivot_index - 1);
                qs_push(&stack, pivot_index + 1, current_high);
            } else {
                qs_push(&stack, pivot_index + 1, current_high);
                qs_push(&stack, current_low, pivot_index - 1);
            }
        }
    }
}

// =============================================================================
// 3. BINARY SEARCH TREE IMPLEMENTATION
// =============================================================================

typedef struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

typedef struct BSTStackNode {
    BSTNode* node;
    struct BSTStackNode* next;
} BSTStackNode;

typedef struct BSTStack {
    BSTStackNode* top;
} BSTStack;

BSTNode* create_bst_node(int data) {
    BSTNode* new_node = (BSTNode*)malloc(sizeof(BSTNode));
    if (new_node) {
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

BSTNode* insert_bst_recursive(BSTNode* root, int data) {
    if (root == NULL) {
        return create_bst_node(data);
    }
    
    if (data < root->data) {
        root->left = insert_bst_recursive(root->left, data);
    } else if (data > root->data) {
        root->right = insert_bst_recursive(root->right, data);
    }
    
    return root;
}

BSTNode* find_min_bst(BSTNode* root) {
    if (root == NULL) return NULL;
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

BSTNode* delete_bst_node(BSTNode* root, int data) {
    if (root == NULL) return root;
    
    if (data < root->data) {
        root->left = delete_bst_node(root->left, data);
    } else if (data > root->data) {
        root->right = delete_bst_node(root->right, data);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        
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
        
        BSTNode* temp = find_min_bst(root->right);
        root->data = temp->data;
        root->right = delete_bst_node(root->right, temp->data);
    }
    
    return root;
}

BSTNode* search_bst(BSTNode* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    
    if (data < root->data) {
        return search_bst(root->left, data);
    }
    
    return search_bst(root->right, data);
}

void inorder_traversal(BSTNode* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

void preorder_traversal(BSTNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}

void postorder_traversal(BSTNode* root) {
    if (root != NULL) {
        postorder_traversal(root->left);
        postorder_traversal(root->right);
        printf("%d ", root->data);
    }
}

int bst_height(BSTNode* root) {
    if (root == NULL) return 0;
    
    int left_height = bst_height(root->left);
    int right_height = bst_height(root->right);
    
    return 1 + (left_height > right_height ? left_height : right_height);
}

void free_bst(BSTNode* root) {
    if (root != NULL) {
        free_bst(root->left);
        free_bst(root->right);
        free(root);
    }
}

// =============================================================================
// 4. INFIX TO POSTFIX CONVERTER
// =============================================================================

typedef struct {
    char items[MAX_SIZE];
    int top;
} CharStack;

void init_char_stack(CharStack* stack) {
    stack->top = -1;
}

bool is_char_stack_empty(CharStack* stack) {
    return stack->top == -1;
}

void push_char(CharStack* stack, char item) {
    if (stack->top < MAX_SIZE - 1) {
        stack->items[++stack->top] = item;
    }
}

char pop_char(CharStack* stack) {
    return (stack->top >= 0) ? stack->items[stack->top--] : '\0';
}

char peek_char(CharStack* stack) {
    return (stack->top >= 0) ? stack->items[stack->top] : '\0';
}

bool is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
}

bool is_operand(char c) {
    return isalnum(c);
}

int get_precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

bool is_left_associative(char op) {
    return (op == '+' || op == '-' || op == '*' || op == '/' || op == '%');
}

void remove_spaces(char* str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ' ' && str[i] != '\t') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

char* infix_to_postfix(const char* infix) {
    char* input = (char*)malloc(strlen(infix) + 1);
    strcpy(input, infix);
    remove_spaces(input);
    
    char* output = (char*)malloc(2 * strlen(input) + 1);
    CharStack operator_stack;
    init_char_stack(&operator_stack);
    
    int output_index = 0;
    
    for (int i = 0; input[i]; i++) {
        char c = input[i];
        
        if (is_operand(c)) {
            output[output_index++] = c;
            output[output_index++] = ' ';
        } else if (c == '(') {
            push_char(&operator_stack, c);
        } else if (c == ')') {
            while (!is_char_stack_empty(&operator_stack) && peek_char(&operator_stack) != '(') {
                output[output_index++] = pop_char(&operator_stack);
                output[output_index++] = ' ';
            }
            if (!is_char_stack_empty(&operator_stack)) {
                pop_char(&operator_stack);
            }
        } else if (is_operator(c)) {
            while (!is_char_stack_empty(&operator_stack) && 
                   peek_char(&operator_stack) != '(' &&
                   (get_precedence(peek_char(&operator_stack)) > get_precedence(c) ||
                    (get_precedence(peek_char(&operator_stack)) == get_precedence(c) && 
                     is_left_associative(c)))) {
                output[output_index++] = pop_char(&operator_stack);
                output[output_index++] = ' ';
            }
            push_char(&operator_stack, c);
        }
    }
    
    while (!is_char_stack_empty(&operator_stack)) {
        output[output_index++] = pop_char(&operator_stack);
        output[output_index++] = ' ';
    }
    
    if (output_index > 0 && output[output_index - 1] == ' ') {
        output_index--;
    }
    output[output_index] = '\0';
    
    free(input);
    return output;
}

// =============================================================================
// 5. HEAP SORT AND PRIORITY QUEUE
// =============================================================================

typedef struct {
    int data;
    int priority;
} PQElement;

typedef struct {
    PQElement* elements;
    int size;
    int capacity;
    bool is_max_heap;
} Heap;

void swap_elements(PQElement* a, PQElement* b) {
    PQElement temp = *a;
    *a = *b;
    *b = temp;
}

int parent_index(int index) {
    return (index - 1) / 2;
}

int left_child_index(int index) {
    return 2 * index + 1;
}

int right_child_index(int index) {
    return 2 * index + 2;
}

Heap* create_heap(int capacity, bool is_max_heap) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    if (!heap) return NULL;
    
    heap->elements = (PQElement*)malloc(capacity * sizeof(PQElement));
    if (!heap->elements) {
        free(heap);
        return NULL;
    }
    
    heap->size = 0;
    heap->capacity = capacity;
    heap->is_max_heap = is_max_heap;
    
    return heap;
}

void heapify_up(Heap* heap, int index) {
    if (index == 0) return;
    
    int parent_idx = parent_index(index);
    bool should_swap;
    
    if (heap->is_max_heap) {
        should_swap = heap->elements[index].priority > heap->elements[parent_idx].priority;
    } else {
        should_swap = heap->elements[index].priority < heap->elements[parent_idx].priority;
    }
    
    if (should_swap) {
        swap_elements(&heap->elements[index], &heap->elements[parent_idx]);
        heapify_up(heap, parent_idx);
    }
}

void heapify_down(Heap* heap, int index) {
    int left = left_child_index(index);
    int right = right_child_index(index);
    int target = index;
    
    if (heap->is_max_heap) {
        if (left < heap->size && 
            heap->elements[left].priority > heap->elements[target].priority) {
            target = left;
        }
        if (right < heap->size && 
            heap->elements[right].priority > heap->elements[target].priority) {
            target = right;
        }
    } else {
        if (left < heap->size && 
            heap->elements[left].priority < heap->elements[target].priority) {
            target = left;
        }
        if (right < heap->size && 
            heap->elements[right].priority < heap->elements[target].priority) {
            target = right;
        }
    }
    
    if (target != index) {
        swap_elements(&heap->elements[index], &heap->elements[target]);
        heapify_down(heap, target);
    }
}

bool insert_heap(Heap* heap, int data, int priority) {
    if (heap->size >= heap->capacity) return false;
    
    heap->elements[heap->size].data = data;
    heap->elements[heap->size].priority = priority;
    heapify_up(heap, heap->size);
    heap->size++;
    
    return true;
}

PQElement extract_heap(Heap* heap) {
    PQElement result = {0, 0};
    
    if (heap->size == 0) return result;
    
    result = heap->elements[0];
    heap->elements[0] = heap->elements[heap->size - 1];
    heap->size--;
    
    if (heap->size > 0) {
        heapify_down(heap, 0);
    }
    
    return result;
}

void heapify_array(int arr[], int n, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    if (largest != root) {
        swap_ints(&arr[root], &arr[largest]);
        heapify_array(arr, n, largest);
    }
}

void heap_sort_ascending(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify_array(arr, n, i);
    }
    
    for (int i = n - 1; i > 0; i--) {
        swap_ints(&arr[0], &arr[i]);
        heapify_array(arr, i, 0);
    }
}

void free_heap(Heap* heap) {
    if (heap) {
        free(heap->elements);
        free(heap);
    }
}

// =============================================================================
// 6. CIRCULAR LINKED LIST
// =============================================================================

typedef struct CLLNode {
    int data;
    struct CLLNode* next;
} CLLNode;

typedef struct CircularLinkedList {
    CLLNode* last;
    int size;
} CircularLinkedList;

CLLNode* create_cll_node(int data) {
    CLLNode* new_node = (CLLNode*)malloc(sizeof(CLLNode));
    if (new_node) {
        new_node->data = data;
        new_node->next = NULL;
    }
    return new_node;
}

CircularLinkedList* create_cll() {
    CircularLinkedList* list = (CircularLinkedList*)malloc(sizeof(CircularLinkedList));
    if (list) {
        list->last = NULL;
        list->size = 0;
    }
    return list;
}

bool is_cll_empty(CircularLinkedList* list) {
    return list->last == NULL;
}

bool insert_cll_beginning(CircularLinkedList* list, int data) {
    CLLNode* new_node = create_cll_node(data);
    if (!new_node) return false;
    
    if (is_cll_empty(list)) {
        new_node->next = new_node;
        list->last = new_node;
    } else {
        new_node->next = list->last->next;
        list->last->next = new_node;
    }
    
    list->size++;
    return true;
}

bool insert_cll_end(CircularLinkedList* list, int data) {
    CLLNode* new_node = create_cll_node(data);
    if (!new_node) return false;
    
    if (is_cll_empty(list)) {
        new_node->next = new_node;
        list->last = new_node;
    } else {
        new_node->next = list->last->next;
        list->last->next = new_node;
        list->last = new_node;
    }
    
    list->size++;
    return true;
}

bool delete_cll_beginning(CircularLinkedList* list) {
    if (is_cll_empty(list)) return false;
    
    CLLNode* first = list->last->next;
    
    if (first == list->last) {
        free(first);
        list->last = NULL;
    } else {
        list->last->next = first->next;
        free(first);
    }
    
    list->size--;
    return true;
}

void display_cll(CircularLinkedList* list) {
    if (is_cll_empty(list)) {
        printf("List is empty.\n");
        return;
    }
    
    CLLNode* current = list->last->next;
    printf("Circular List: ");
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != list->last->next);
    
    printf("(circular)\n");
}

void free_cll(CircularLinkedList* list) {
    if (!list) return;
    
    while (!is_cll_empty(list)) {
        delete_cll_beginning(list);
    }
    
    free(list);
}

// =============================================================================
// MAIN MENU SYSTEM
// =============================================================================

void graph_menu() {
    Graph* graph = NULL;
    int choice, vertices, src, dest, start;
    
    printf("\n=== GRAPH TRAVERSAL MENU ===\n");
    printf("Enter number of vertices: ");
    if (scanf("%d", &vertices) != 1 || vertices <= 0 || vertices > MAX_VERTICES) {
        printf("Invalid number of vertices!\n");
        return;
    }
    
    graph = create_graph(vertices);
    if (!graph) {
        printf("Failed to create graph!\n");
        return;
    }
    
    printf("Enter edges (format: source destination, -1 -1 to stop):\n");
    while (1) {
        printf("Edge: ");
        if (scanf("%d %d", &src, &dest) != 2) {
            printf("Invalid input!\n");
            continue;
        }
        
        if (src == -1 && dest == -1) break;
        
        if (src < 0 || src >= vertices || dest < 0 || dest >= vertices) {
            printf("Invalid vertex range! Use 0-%d\n", vertices - 1);
            continue;
        }
        
        add_edge(graph, src, dest);
    }
    
    while (1) {
        printf("\n1. BFS Traversal\n");
        printf("2. DFS Traversal\n");
        printf("3. Back to main menu\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }
        
        if (choice == 3) break;
        
        if (choice == 1 || choice == 2) {
            printf("Enter starting vertex (0-%d): ", vertices - 1);
            if (scanf("%d", &start) != 1 || start < 0 || start >= vertices) {
                printf("Invalid starting vertex!\n");
                continue;
            }
            
            if (choice == 1) {
                bfs(graph, start);
            } else {
                dfs(graph, start);
            }
        } else {
            printf("Invalid choice!\n");
        }
    }
    
    free_graph(graph);
}

void sorting_menu() {
    int choice, n, pivot_choice;
    int* arr = NULL;
    clock_t start_time, end_time;
    double cpu_time_used;
    
    while (1) {
        printf("\n=== SORTING ALGORITHMS MENU ===\n");
        printf("1. QuickSort (Hybrid)\n");
        printf("2. QuickSort (Iterative)\n");
        printf("3. Heap Sort\n");
        printf("4. Back to main menu\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }
        
        if (choice == 4) break;
        
        if (choice >= 1 && choice <= 3) {
            printf("Enter array size: ");
            if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_SIZE) {
                printf("Invalid size!\n");
                continue;
            }
            
            arr = (int*)malloc(n * sizeof(int));
            if (!arr) {
                printf("Memory allocation failed!\n");
                continue;
            }
            
            printf("1. Enter manually\n2. Generate random\nChoice: ");
            int input_choice;
            if (scanf("%d", &input_choice) != 1) {
                printf("Invalid choice!\n");
                free(arr);
                continue;
            }
            
            if (input_choice == 1) {
                printf("Enter %d elements: ", n);
                for (int i = 0; i < n; i++) {
                    if (scanf("%d", &arr[i]) != 1) {
                        printf("Invalid input!\n");
                        free(arr);
                        goto sort_menu_continue;
                    }
                }
            } else {
                generate_random_array(arr, n, 1000);
                printf("Generated random array (first 20): ");
                print_array(arr, n < 20 ? n : 20);
                if (n > 20) printf("... (%d more)\n", n - 20);
            }
            
            printf("Original array: ");
            print_array(arr, n < 20 ? n : 20);
            
            start_time = clock();
            
            switch (choice) {
                case 1:
                    printf("Select pivot strategy (1-5): ");
                    if (scanf("%d", &pivot_choice) == 1 && pivot_choice >= 1 && pivot_choice <= 5) {
                        quicksort_hybrid(arr, 0, n - 1, (PivotStrategy)(pivot_choice - 1));
                    } else {
                        quicksort_hybrid(arr, 0, n - 1, MEDIAN_OF_THREE);
                    }
                    break;
                case 2:
                    quicksort_iterative(arr, 0, n - 1, MEDIAN_OF_THREE);
                    break;
                case 3:
                    heap_sort_ascending(arr, n);
                    break;
            }
            
            end_time = clock();
            cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            
            printf("Sorted array: ");
            print_array(arr, n < 20 ? n : 20);
            if (n > 20) printf("... (%d more)\n", n - 20);
            
            printf("Time taken: %f seconds\n", cpu_time_used);
            printf("Correctly sorted: %s\n", is_sorted_ascending(arr, n) ? "Yes" : "No");
            
            free(arr);
        } else {
            printf("Invalid choice!\n");
        }
        
        sort_menu_continue:;
    }
}

void bst_menu() {
    BSTNode* root = NULL;
    int choice, value;
    
    while (1) {
        printf("\n=== BINARY SEARCH TREE MENU ===\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Inorder Traversal\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Tree Height\n");
        printf("8. Back to main menu\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                if (scanf("%d", &value) == 1) {
                    root = insert_bst_recursive(root, value);
                    printf("Value %d inserted.\n", value);
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 2:
                if (root == NULL) {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("Enter value to delete: ");
                if (scanf("%d", &value) == 1) {
                    root = delete_bst_node(root, value);
                    printf("Value %d deleted.\n", value);
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 3:
                if (root == NULL) {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("Enter value to search: ");
                if (scanf("%d", &value) == 1) {
                    BSTNode* result = search_bst(root, value);
                    printf("Value %d %s in tree.\n", value, result ? "found" : "not found");
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 4:
                if (root == NULL) {
                    printf("Tree is empty!\n");
                } else {
                    printf("Inorder: ");
                    inorder_traversal(root);
                    printf("\n");
                }
                break;
                
            case 5:
                if (root == NULL) {
                    printf("Tree is empty!\n");
                } else {
                    printf("Preorder: ");
                    preorder_traversal(root);
                    printf("\n");
                }
                break;
                
            case 6:
                if (root == NULL) {
                    printf("Tree is empty!\n");
                } else {
                    printf("Postorder: ");
                    postorder_traversal(root);
                    printf("\n");
                }
                break;
                
            case 7:
                printf("Tree height: %d\n", bst_height(root));
                break;
                
            case 8:
                if (root) free_bst(root);
                return;
                
            default:
                printf("Invalid choice!\n");
        }
    }
}

void expression_menu() {
    char infix[MAX_SIZE];
    char* postfix;
    int choice;
    
    while (1) {
        printf("\n=== EXPRESSION CONVERTER MENU ===\n");
        printf("1. Convert Infix to Postfix\n");
        printf("2. Back to main menu\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1:
                printf("Enter infix expression: ");
                scanf(" %[^\n]", infix);
                
                postfix = infix_to_postfix(infix);
                if (postfix) {
                    printf("Infix:    %s\n", infix);
                    printf("Postfix:  %s\n", postfix);
                    free(postfix);
                } else {
                    printf("Error in conversion!\n");
                }
                break;
                
            case 2:
                return;
                
            default:
                printf("Invalid choice!\n");
        }
    }
}

void priority_queue_menu() {
    Heap* max_pq = create_heap(MAX_SIZE, true);
    int choice, data, priority;
    PQElement element;
    
    if (!max_pq) {
        printf("Failed to create priority queue!\n");
        return;
    }
    
    while (1) {
        printf("\n=== PRIORITY QUEUE MENU ===\n");
        printf("1. Insert\n");
        printf("2. Extract Max\n");
        printf("3. Display Queue\n");
        printf("4. Back to main menu\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1:
                printf("Enter data: ");
                if (scanf("%d", &data) != 1) {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                    break;
                }
                printf("Enter priority: ");
                if (scanf("%d", &priority) == 1) {
                    if (insert_heap(max_pq, data, priority)) {
                        printf("Inserted (%d, %d)\n", data, priority);
                    } else {
                        printf("Queue is full!\n");
                    }
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 2:
                if (max_pq->size == 0) {
                    printf("Queue is empty!\n");
                } else {
                    element = extract_heap(max_pq);
                    printf("Extracted: Data=%d, Priority=%d\n", element.data, element.priority);
                }
                break;
                
            case 3:
                if (max_pq->size == 0) {
                    printf("Queue is empty!\n");
                } else {
                    printf("Priority Queue: ");
                    for (int i = 0; i < max_pq->size; i++) {
                        printf("(%d,%d) ", max_pq->elements[i].data, max_pq->elements[i].priority);
                    }
                    printf("\n");
                }
                break;
                
            case 4:
                free_heap(max_pq);
                return;
                
            default:
                printf("Invalid choice!\n");
        }
    }
}

void circular_list_menu() {
    CircularLinkedList* list = create_cll();
    int choice, data;
    
    if (!list) {
        printf("Failed to create list!\n");
        return;
    }
    
    while (1) {
        printf("\n=== CIRCULAR LINKED LIST MENU ===\n");
        printf("1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Delete from beginning\n");
        printf("4. Display list\n");
        printf("5. List size\n");
        printf("6. Back to main menu\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1:
                printf("Enter value: ");
                if (scanf("%d", &data) == 1) {
                    if (insert_cll_beginning(list, data)) {
                        printf("Inserted %d at beginning.\n", data);
                    } else {
                        printf("Failed to insert!\n");
                    }
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 2:
                printf("Enter value: ");
                if (scanf("%d", &data) == 1) {
                    if (insert_cll_end(list, data)) {
                        printf("Inserted %d at end.\n", data);
                    } else {
                        printf("Failed to insert!\n");
                    }
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 3:
                if (delete_cll_beginning(list)) {
                    printf("Deleted from beginning.\n");
                } else {
                    printf("List is empty!\n");
                }
                break;
                
            case 4:
                display_cll(list);
                break;
                
            case 5:
                printf("List size: %d\n", list->size);
                break;
                
            case 6:
                free_cll(list);
                return;
                
            default:
                printf("Invalid choice!\n");
        }
    }
}

int main() {
    int choice;
    
    printf("=== COMPREHENSIVE DATA STRUCTURES & ALGORITHMS ===\n");
    printf("Optimized implementations with modern C standards\n");
    
    while (1) {
        printf("\n=== MAIN MENU ===\n");
        printf("1. Graph Traversal (BFS/DFS)\n");
        printf("2. Sorting Algorithms\n");
        printf("3. Binary Search Tree\n");
        printf("4. Expression Converter\n");
        printf("5. Priority Queue\n");
        printf("6. Circular Linked List\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        
        switch (choice) {
            case 1:
                graph_menu();
                break;
            case 2:
                sorting_menu();
                break;
            case 3:
                bst_menu();
                break;
            case 4:
                expression_menu();
                break;
            case 5:
                priority_queue_menu();
                break;
            case 6:
                circular_list_menu();
                break;
            case 7:
                printf("Thank you for using the program!\n");
                return 0;
            default:
                printf("Invalid choice! Please select 1-7.\n");
        }
    }
    
    return 0;
}