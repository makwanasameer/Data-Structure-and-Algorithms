#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_VERTICES 100
#define QUEUE_SIZE 100

// Graph structure using adjacency list for better memory efficiency
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int num_vertices;
    Node** adj_list;
    bool* visited;
} Graph;

// Queue for BFS
typedef struct Queue {
    int items[QUEUE_SIZE];
    int front;
    int rear;
} Queue;

// Stack for DFS
typedef struct Stack {
    int items[QUEUE_SIZE];
    int top;
} Stack;

// Function prototypes
Graph* create_graph(int vertices);
void add_edge(Graph* graph, int src, int dest);
void print_graph(Graph* graph);
void bfs(Graph* graph, int start_vertex);
void dfs(Graph* graph, int start_vertex);
void dfs_recursive(Graph* graph, int vertex);
void reset_visited(Graph* graph);
void free_graph(Graph* graph);

// Queue operations
Queue* create_queue();
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
bool is_queue_empty(Queue* q);

// Stack operations
Stack* create_stack();
void push(Stack* s, int value);
int pop(Stack* s);
bool is_stack_empty(Stack* s);

int main() {
    int num_vertices, choice, src, dest, start_vertex;
    char continue_choice;
    
    printf("=== Optimized Graph Traversal (BFS & DFS) ===\n");
    printf("Enter number of vertices: ");
    
    if (scanf("%d", &num_vertices) != 1 || num_vertices <= 0 || num_vertices > MAX_VERTICES) {
        printf("Error: Invalid number of vertices!\n");
        return 1;
    }
    
    Graph* graph = create_graph(num_vertices);
    if (!graph) {
        printf("Error: Memory allocation failed!\n");
        return 1;
    }
    
    printf("\nEnter edges (format: source destination, -1 -1 to stop):\n");
    while (1) {
        printf("Edge: ");
        if (scanf("%d %d", &src, &dest) != 2) {
            printf("Invalid input format!\n");
            continue;
        }
        
        if (src == -1 && dest == -1) break;
        
        if (src < 0 || src >= num_vertices || dest < 0 || dest >= num_vertices) {
            printf("Error: Vertex out of range! Valid range: 0-%d\n", num_vertices - 1);
            continue;
        }
        
        add_edge(graph, src, dest);
    }
    
    printf("\nGraph adjacency list:\n");
    print_graph(graph);
    
    do {
        printf("\n=== MENU ===\n");
        printf("1. Breadth-First Search (BFS)\n");
        printf("2. Depth-First Search (DFS) - Iterative\n");
        printf("3. Depth-First Search (DFS) - Recursive\n");
        printf("4. Display Graph\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        
        if (choice >= 1 && choice <= 3) {
            printf("Enter starting vertex (0-%d): ", num_vertices - 1);
            if (scanf("%d", &start_vertex) != 1 || 
                start_vertex < 0 || start_vertex >= num_vertices) {
                printf("Error: Invalid starting vertex!\n");
                continue;
            }
        }
        
        switch (choice) {
            case 1:
                printf("\nBFS traversal starting from vertex %d:\n", start_vertex);
                bfs(graph, start_vertex);
                break;
            case 2:
                printf("\nDFS (Iterative) traversal starting from vertex %d:\n", start_vertex);
                dfs(graph, start_vertex);
                break;
            case 3:
                printf("\nDFS (Recursive) traversal starting from vertex %d:\n", start_vertex);
                reset_visited(graph);
                dfs_recursive(graph, start_vertex);
                printf("\n");
                break;
            case 4:
                printf("\nGraph adjacency list:\n");
                print_graph(graph);
                break;
            default:
                printf("Invalid choice!\n");
                continue;
        }
        
        printf("\nDo you want to continue? (y/n): ");
        scanf(" %c", &continue_choice);
        
    } while (continue_choice == 'y' || continue_choice == 'Y');
    
    free_graph(graph);
    printf("Program terminated successfully.\n");
    return 0;
}

Graph* create_graph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) return NULL;
    
    graph->num_vertices = vertices;
    graph->adj_list = (Node**)calloc(vertices, sizeof(Node*));
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
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return;
    
    new_node->vertex = dest;
    new_node->next = graph->adj_list[src];
    graph->adj_list[src] = new_node;
    
    // For undirected graph, add edge from dest to src
    new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return;
    
    new_node->vertex = src;
    new_node->next = graph->adj_list[dest];
    graph->adj_list[dest] = new_node;
}

void print_graph(Graph* graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        printf("Vertex %d: ", i);
        Node* current = graph->adj_list[i];
        while (current) {
            printf("%d ", current->vertex);
            current = current->next;
        }
        printf("\n");
    }
}

void bfs(Graph* graph, int start_vertex) {
    reset_visited(graph);
    Queue* queue = create_queue();
    
    graph->visited[start_vertex] = true;
    enqueue(queue, start_vertex);
    
    printf("BFS: ");
    while (!is_queue_empty(queue)) {
        int current_vertex = dequeue(queue);
        printf("%d ", current_vertex);
        
        Node* adjacent = graph->adj_list[current_vertex];
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

void dfs(Graph* graph, int start_vertex) {
    reset_visited(graph);
    Stack* stack = create_stack();
    
    push(stack, start_vertex);
    
    printf("DFS (Iterative): ");
    while (!is_stack_empty(stack)) {
        int current_vertex = pop(stack);
        
        if (!graph->visited[current_vertex]) {
            graph->visited[current_vertex] = true;
            printf("%d ", current_vertex);
            
            // Add adjacent vertices to stack in reverse order
            // to maintain left-to-right traversal order
            Node* adjacent = graph->adj_list[current_vertex];
            int* temp_vertices = (int*)malloc(graph->num_vertices * sizeof(int));
            int count = 0;
            
            while (adjacent) {
                if (!graph->visited[adjacent->vertex]) {
                    temp_vertices[count++] = adjacent->vertex;
                }
                adjacent = adjacent->next;
            }
            
            // Push in reverse order
            for (int i = count - 1; i >= 0; i--) {
                push(stack, temp_vertices[i]);
            }
            free(temp_vertices);
        }
    }
    printf("\n");
    free(stack);
}

void dfs_recursive(Graph* graph, int vertex) {
    graph->visited[vertex] = true;
    printf("%d ", vertex);
    
    Node* adjacent = graph->adj_list[vertex];
    while (adjacent) {
        if (!graph->visited[adjacent->vertex]) {
            dfs_recursive(graph, adjacent->vertex);
        }
        adjacent = adjacent->next;
    }
}

void reset_visited(Graph* graph) {
    memset(graph->visited, false, graph->num_vertices * sizeof(bool));
}

void free_graph(Graph* graph) {
    if (!graph) return;
    
    for (int i = 0; i < graph->num_vertices; i++) {
        Node* current = graph->adj_list[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    
    free(graph->adj_list);
    free(graph->visited);
    free(graph);
}

// Queue implementation
Queue* create_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue) {
        queue->front = -1;
        queue->rear = -1;
    }
    return queue;
}

void enqueue(Queue* q, int value) {
    if (q->rear == QUEUE_SIZE - 1) {
        printf("Queue overflow!\n");
        return;
    }
    
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

int dequeue(Queue* q) {
    if (q->front == -1 || q->front > q->rear) {
        printf("Queue underflow!\n");
        return -1;
    }
    
    int item = q->items[q->front++];
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

bool is_queue_empty(Queue* q) {
    return q->front == -1 || q->front > q->rear;
}

// Stack implementation
Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack) {
        stack->top = -1;
    }
    return stack;
}

void push(Stack* s, int value) {
    if (s->top == QUEUE_SIZE - 1) {
        printf("Stack overflow!\n");
        return;
    }
    s->items[++s->top] = value;
}

int pop(Stack* s) {
    if (s->top == -1) {
        printf("Stack underflow!\n");
        return -1;
    }
    return s->items[s->top--];
}

bool is_stack_empty(Stack* s) {
    return s->top == -1;
}