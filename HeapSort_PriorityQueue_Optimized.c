#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX_HEAP_SIZE 1000

// Priority Queue element structure
typedef struct {
    int data;
    int priority;
} PQElement;

// Heap structure for both max heap and min heap
typedef struct {
    PQElement* elements;
    int size;
    int capacity;
    bool is_max_heap; // true for max heap, false for min heap
} Heap;

// Function prototypes for Heap operations
Heap* create_heap(int capacity, bool is_max_heap);
void free_heap(Heap* heap);
bool is_heap_empty(Heap* heap);
bool is_heap_full(Heap* heap);
void swap_elements(PQElement* a, PQElement* b);
int parent(int index);
int left_child(int index);
int right_child(int index);
void heapify_up(Heap* heap, int index);
void heapify_down(Heap* heap, int index);
bool insert_heap(Heap* heap, int data, int priority);
PQElement extract_heap(Heap* heap);
PQElement peek_heap(Heap* heap);
void print_heap(Heap* heap);
void build_heap(Heap* heap, PQElement elements[], int n);

// Heap Sort functions
void heap_sort_ascending(int arr[], int n);
void heap_sort_descending(int arr[], int n);
void heapify_array(int arr[], int n, int root);
void print_array(int arr[], int n);

// Priority Queue operations
void priority_queue_demo();
void heap_sort_demo();

// Utility functions
void generate_random_array(int arr[], int n, int max_value);
bool is_sorted_ascending(int arr[], int n);
bool is_sorted_descending(int arr[], int n);

int main() {
    int choice;
    
    printf("=== Optimized Heap Sort & Priority Queue ===\n");
    
    while (1) {
        printf("\n=== MAIN MENU ===\n");
        printf("1. Heap Sort Demonstration\n");
        printf("2. Priority Queue Operations\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1:
                heap_sort_demo();
                break;
            case 2:
                priority_queue_demo();
                break;
            case 3:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}

void heap_sort_demo() {
    int choice, n;
    int* arr = NULL;
    clock_t start, end;
    double cpu_time_used;
    
    while (1) {
        printf("\n=== HEAP SORT MENU ===\n");
        printf("1. Sort user input array (ascending)\n");
        printf("2. Sort user input array (descending)\n");
        printf("3. Sort random array (ascending)\n");
        printf("4. Sort random array (descending)\n");
        printf("5. Performance comparison\n");
        printf("6. Back to main menu\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1:
            case 2:
                printf("Enter array size: ");
                if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_HEAP_SIZE) {
                    printf("Invalid size!\n");
                    break;
                }
                
                arr = (int*)malloc(n * sizeof(int));
                if (!arr) {
                    printf("Memory allocation failed!\n");
                    break;
                }
                
                printf("Enter %d elements: ", n);
                for (int i = 0; i < n; i++) {
                    if (scanf("%d", &arr[i]) != 1) {
                        printf("Invalid input!\n");
                        free(arr);
                        arr = NULL;
                        goto heap_menu_continue;
                    }
                }
                
                printf("Original array: ");
                print_array(arr, n);
                
                start = clock();
                if (choice == 1) {
                    heap_sort_ascending(arr, n);
                } else {
                    heap_sort_descending(arr, n);
                }
                end = clock();
                cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                
                printf("Sorted array (%s): ", 
                       choice == 1 ? "ascending" : "descending");
                print_array(arr, n);
                printf("Time taken: %f seconds\n", cpu_time_used);
                printf("Correctly sorted: %s\n", 
                       (choice == 1 ? is_sorted_ascending(arr, n) : 
                        is_sorted_descending(arr, n)) ? "Yes" : "No");
                
                free(arr);
                arr = NULL;
                break;
                
            case 3:
            case 4:
                printf("Enter array size: ");
                if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_HEAP_SIZE) {
                    printf("Invalid size!\n");
                    break;
                }
                
                arr = (int*)malloc(n * sizeof(int));
                if (!arr) {
                    printf("Memory allocation failed!\n");
                    break;
                }
                
                generate_random_array(arr, n, 1000);
                
                printf("Generated random array (first 20 elements): ");
                print_array(arr, n < 20 ? n : 20);
                if (n > 20) printf("... (%d more elements)\n", n - 20);
                
                start = clock();
                if (choice == 3) {
                    heap_sort_ascending(arr, n);
                } else {
                    heap_sort_descending(arr, n);
                }
                end = clock();
                cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                
                printf("Sorted array (%s, first 20 elements): ", 
                       choice == 3 ? "ascending" : "descending");
                print_array(arr, n < 20 ? n : 20);
                if (n > 20) printf("... (%d more elements)\n", n - 20);
                
                printf("Time taken: %f seconds\n", cpu_time_used);
                printf("Correctly sorted: %s\n", 
                       (choice == 3 ? is_sorted_ascending(arr, n) : 
                        is_sorted_descending(arr, n)) ? "Yes" : "No");
                
                free(arr);
                arr = NULL;
                break;
                
            case 5: {
                int sizes[] = {100, 500, 1000, 5000};
                int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
                
                printf("\n=== Performance Comparison ===\n");
                printf("%-10s %-15s %-15s\n", "Size", "Ascending (s)", "Descending (s)");
                printf("%-10s %-15s %-15s\n", "----", "-----------", "------------");
                
                for (int i = 0; i < num_sizes; i++) {
                    int size = sizes[i];
                    int* test_arr1 = (int*)malloc(size * sizeof(int));
                    int* test_arr2 = (int*)malloc(size * sizeof(int));
                    
                    if (!test_arr1 || !test_arr2) {
                        printf("Memory allocation failed for size %d\n", size);
                        free(test_arr1);
                        free(test_arr2);
                        continue;
                    }
                    
                    generate_random_array(test_arr1, size, 10000);
                    memcpy(test_arr2, test_arr1, size * sizeof(int));
                    
                    // Test ascending sort
                    start = clock();
                    heap_sort_ascending(test_arr1, size);
                    end = clock();
                    double time_asc = ((double)(end - start)) / CLOCKS_PER_SEC;
                    
                    // Test descending sort
                    start = clock();
                    heap_sort_descending(test_arr2, size);
                    end = clock();
                    double time_desc = ((double)(end - start)) / CLOCKS_PER_SEC;
                    
                    printf("%-10d %-15.6f %-15.6f\n", size, time_asc, time_desc);
                    
                    free(test_arr1);
                    free(test_arr2);
                }
                break;
            }
                
            case 6:
                return;
                
            default:
                printf("Invalid choice!\n");
        }
        
        heap_menu_continue:;
    }
}

void priority_queue_demo() {
    Heap* max_pq = create_heap(MAX_HEAP_SIZE, true);  // Max priority queue
    Heap* min_pq = create_heap(MAX_HEAP_SIZE, false); // Min priority queue
    int choice, data, priority;
    PQElement element;
    
    if (!max_pq || !min_pq) {
        printf("Failed to create priority queues!\n");
        return;
    }
    
    while (1) {
        printf("\n=== PRIORITY QUEUE MENU ===\n");
        printf("1.  Insert into Max Priority Queue\n");
        printf("2.  Insert into Min Priority Queue\n");
        printf("3.  Extract from Max Priority Queue\n");
        printf("4.  Extract from Min Priority Queue\n");
        printf("5.  Peek Max Priority Queue\n");
        printf("6.  Peek Min Priority Queue\n");
        printf("7.  Display Max Priority Queue\n");
        printf("8.  Display Min Priority Queue\n");
        printf("9.  Clear Max Priority Queue\n");
        printf("10. Clear Min Priority Queue\n");
        printf("11. Back to main menu\n");
        printf("Enter your choice: ");
        
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
                if (scanf("%d", &priority) != 1) {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                    break;
                }
                
                if (insert_heap(max_pq, data, priority)) {
                    printf("Inserted (%d, %d) into Max Priority Queue.\n", data, priority);
                } else {
                    printf("Failed to insert! Queue might be full.\n");
                }
                break;
                
            case 2:
                printf("Enter data: ");
                if (scanf("%d", &data) != 1) {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                    break;
                }
                printf("Enter priority: ");
                if (scanf("%d", &priority) != 1) {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                    break;
                }
                
                if (insert_heap(min_pq, data, priority)) {
                    printf("Inserted (%d, %d) into Min Priority Queue.\n", data, priority);
                } else {
                    printf("Failed to insert! Queue might be full.\n");
                }
                break;
                
            case 3:
                if (is_heap_empty(max_pq)) {
                    printf("Max Priority Queue is empty!\n");
                } else {
                    element = extract_heap(max_pq);
                    printf("Extracted from Max PQ: Data=%d, Priority=%d\n", 
                           element.data, element.priority);
                }
                break;
                
            case 4:
                if (is_heap_empty(min_pq)) {
                    printf("Min Priority Queue is empty!\n");
                } else {
                    element = extract_heap(min_pq);
                    printf("Extracted from Min PQ: Data=%d, Priority=%d\n", 
                           element.data, element.priority);
                }
                break;
                
            case 5:
                if (is_heap_empty(max_pq)) {
                    printf("Max Priority Queue is empty!\n");
                } else {
                    element = peek_heap(max_pq);
                    printf("Top of Max PQ: Data=%d, Priority=%d\n", 
                           element.data, element.priority);
                }
                break;
                
            case 6:
                if (is_heap_empty(min_pq)) {
                    printf("Min Priority Queue is empty!\n");
                } else {
                    element = peek_heap(min_pq);
                    printf("Top of Min PQ: Data=%d, Priority=%d\n", 
                           element.data, element.priority);
                }
                break;
                
            case 7:
                printf("Max Priority Queue contents:\n");
                print_heap(max_pq);
                break;
                
            case 8:
                printf("Min Priority Queue contents:\n");
                print_heap(min_pq);
                break;
                
            case 9:
                max_pq->size = 0;
                printf("Max Priority Queue cleared.\n");
                break;
                
            case 10:
                min_pq->size = 0;
                printf("Min Priority Queue cleared.\n");
                break;
                
            case 11:
                free_heap(max_pq);
                free_heap(min_pq);
                return;
                
            default:
                printf("Invalid choice!\n");
        }
    }
}

// Heap implementation
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

void free_heap(Heap* heap) {
    if (heap) {
        free(heap->elements);
        free(heap);
    }
}

bool is_heap_empty(Heap* heap) {
    return heap->size == 0;
}

bool is_heap_full(Heap* heap) {
    return heap->size == heap->capacity;
}

void swap_elements(PQElement* a, PQElement* b) {
    PQElement temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int index) {
    return (index - 1) / 2;
}

int left_child(int index) {
    return 2 * index + 1;
}

int right_child(int index) {
    return 2 * index + 2;
}

void heapify_up(Heap* heap, int index) {
    if (index == 0) return;
    
    int parent_idx = parent(index);
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
    int left = left_child(index);
    int right = right_child(index);
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
    if (is_heap_full(heap)) {
        return false;
    }
    
    heap->elements[heap->size].data = data;
    heap->elements[heap->size].priority = priority;
    heapify_up(heap, heap->size);
    heap->size++;
    
    return true;
}

PQElement extract_heap(Heap* heap) {
    PQElement result = {0, 0};
    
    if (is_heap_empty(heap)) {
        return result;
    }
    
    result = heap->elements[0];
    heap->elements[0] = heap->elements[heap->size - 1];
    heap->size--;
    
    if (heap->size > 0) {
        heapify_down(heap, 0);
    }
    
    return result;
}

PQElement peek_heap(Heap* heap) {
    PQElement result = {0, 0};
    
    if (!is_heap_empty(heap)) {
        result = heap->elements[0];
    }
    
    return result;
}

void print_heap(Heap* heap) {
    if (is_heap_empty(heap)) {
        printf("Heap is empty.\n");
        return;
    }
    
    printf("Heap (%s): ", heap->is_max_heap ? "Max" : "Min");
    for (int i = 0; i < heap->size; i++) {
        printf("(%d,%d) ", heap->elements[i].data, heap->elements[i].priority);
    }
    printf("\n");
}

// Heap Sort implementation
void heap_sort_ascending(int arr[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify_array(arr, n, i);
    }
    
    // Extract elements one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        
        // Call heapify on the reduced heap
        heapify_array(arr, i, 0);
    }
}

void heap_sort_descending(int arr[], int n) {
    // Build min heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        // Use modified heapify for min heap
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && arr[left] < arr[smallest]) {
            smallest = left;
        }
        
        if (right < n && arr[right] < arr[smallest]) {
            smallest = right;
        }
        
        if (smallest != i) {
            int temp = arr[i];
            arr[i] = arr[smallest];
            arr[smallest] = temp;
            
            // Recursively heapify the affected subtree
            for (int j = smallest; j < n; ) {
                int min_idx = j;
                int l = 2 * j + 1;
                int r = 2 * j + 2;
                
                if (l < n && arr[l] < arr[min_idx]) {
                    min_idx = l;
                }
                
                if (r < n && arr[r] < arr[min_idx]) {
                    min_idx = r;
                }
                
                if (min_idx != j) {
                    int tmp = arr[j];
                    arr[j] = arr[min_idx];
                    arr[min_idx] = tmp;
                    j = min_idx;
                } else {
                    break;
                }
            }
        }
    }
    
    // Extract elements one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        
        // Call min heapify on the reduced heap
        for (int j = 0; j < i; ) {
            int smallest = j;
            int left = 2 * j + 1;
            int right = 2 * j + 2;
            
            if (left < i && arr[left] < arr[smallest]) {
                smallest = left;
            }
            
            if (right < i && arr[right] < arr[smallest]) {
                smallest = right;
            }
            
            if (smallest != j) {
                int tmp = arr[j];
                arr[j] = arr[smallest];
                arr[smallest] = tmp;
                j = smallest;
            } else {
                break;
            }
        }
    }
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
        int temp = arr[root];
        arr[root] = arr[largest];
        arr[largest] = temp;
        
        heapify_array(arr, n, largest);
    }
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void generate_random_array(int arr[], int n, int max_value) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % max_value;
    }
}

bool is_sorted_ascending(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

bool is_sorted_descending(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[i - 1]) {
            return false;
        }
    }
    return true;
}