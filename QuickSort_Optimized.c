#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE 10000
#define INSERTION_SORT_THRESHOLD 10

// Pivot selection strategies
typedef enum {
    FIRST_ELEMENT,
    LAST_ELEMENT,
    MIDDLE_ELEMENT,
    MEDIAN_OF_THREE,
    RANDOM_ELEMENT
} PivotStrategy;

// Stack for iterative quicksort
typedef struct {
    int low;
    int high;
} StackFrame;

typedef struct {
    StackFrame frames[MAX_SIZE];
    int top;
} Stack;

// Function prototypes
void quicksort_recursive(int arr[], int low, int high, PivotStrategy strategy);
void quicksort_iterative(int arr[], int low, int high, PivotStrategy strategy);
void quicksort_hybrid(int arr[], int low, int high, PivotStrategy strategy);
int partition(int arr[], int low, int high, PivotStrategy strategy);
int select_pivot(int arr[], int low, int high, PivotStrategy strategy);
void insertion_sort(int arr[], int low, int high);
void swap(int* a, int* b);
int median_of_three(int arr[], int low, int high);
void print_array(int arr[], int size);
bool is_sorted(int arr[], int size);
void generate_test_data(int arr[], int size, const char* type);
void benchmark_sorts(int size);

// Stack operations
void init_stack(Stack* stack);
void push(Stack* stack, int low, int high);
bool pop(Stack* stack, int* low, int* high);
bool is_empty(Stack* stack);

int main() {
    int choice, size, pivot_choice;
    int* arr = NULL;
    clock_t start, end;
    double cpu_time_used;
    
    printf("=== Optimized QuickSort Implementation ===\n");
    
    while (1) {
        printf("\n=== MENU ===\n");
        printf("1. Sort user input array\n");
        printf("2. Sort random array\n");
        printf("3. Performance benchmark\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1: {
                printf("Enter array size (max %d): ", MAX_SIZE);
                if (scanf("%d", &size) != 1 || size <= 0 || size > MAX_SIZE) {
                    printf("Invalid size!\n");
                    break;
                }
                
                arr = (int*)malloc(size * sizeof(int));
                if (!arr) {
                    printf("Memory allocation failed!\n");
                    break;
                }
                
                printf("Enter %d elements: ", size);
                for (int i = 0; i < size; i++) {
                    if (scanf("%d", &arr[i]) != 1) {
                        printf("Invalid input!\n");
                        free(arr);
                        arr = NULL;
                        goto menu_continue;
                    }
                }
                
                printf("\nOriginal array: ");
                print_array(arr, size);
                
                printf("\nSelect pivot strategy:\n");
                printf("1. First element\n2. Last element\n3. Middle element\n");
                printf("4. Median of three\n5. Random element\n");
                printf("Enter choice: ");
                
                if (scanf("%d", &pivot_choice) != 1 || 
                    pivot_choice < 1 || pivot_choice > 5) {
                    printf("Invalid pivot strategy!\n");
                    free(arr);
                    arr = NULL;
                    break;
                }
                
                // Create copies for different sorting methods
                int* arr_recursive = (int*)malloc(size * sizeof(int));
                int* arr_iterative = (int*)malloc(size * sizeof(int));
                int* arr_hybrid = (int*)malloc(size * sizeof(int));
                
                if (!arr_recursive || !arr_iterative || !arr_hybrid) {
                    printf("Memory allocation failed!\n");
                    free(arr);
                    free(arr_recursive);
                    free(arr_iterative);
                    free(arr_hybrid);
                    break;
                }
                
                memcpy(arr_recursive, arr, size * sizeof(int));
                memcpy(arr_iterative, arr, size * sizeof(int));
                memcpy(arr_hybrid, arr, size * sizeof(int));
                
                PivotStrategy strategy = (PivotStrategy)(pivot_choice - 1);
                
                // Recursive QuickSort
                start = clock();
                quicksort_recursive(arr_recursive, 0, size - 1, strategy);
                end = clock();
                cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                
                printf("\nRecursive QuickSort result: ");
                print_array(arr_recursive, size);
                printf("Time taken: %f seconds\n", cpu_time_used);
                printf("Sorted correctly: %s\n", is_sorted(arr_recursive, size) ? "Yes" : "No");
                
                // Iterative QuickSort
                start = clock();
                quicksort_iterative(arr_iterative, 0, size - 1, strategy);
                end = clock();
                cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                
                printf("\nIterative QuickSort result: ");
                print_array(arr_iterative, size);
                printf("Time taken: %f seconds\n", cpu_time_used);
                printf("Sorted correctly: %s\n", is_sorted(arr_iterative, size) ? "Yes" : "No");
                
                // Hybrid QuickSort
                start = clock();
                quicksort_hybrid(arr_hybrid, 0, size - 1, strategy);
                end = clock();
                cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                
                printf("\nHybrid QuickSort result: ");
                print_array(arr_hybrid, size);
                printf("Time taken: %f seconds\n", cpu_time_used);
                printf("Sorted correctly: %s\n", is_sorted(arr_hybrid, size) ? "Yes" : "No");
                
                free(arr);
                free(arr_recursive);
                free(arr_iterative);
                free(arr_hybrid);
                arr = NULL;
                break;
            }
            
            case 2: {
                printf("Enter array size (max %d): ", MAX_SIZE);
                if (scanf("%d", &size) != 1 || size <= 0 || size > MAX_SIZE) {
                    printf("Invalid size!\n");
                    break;
                }
                
                arr = (int*)malloc(size * sizeof(int));
                if (!arr) {
                    printf("Memory allocation failed!\n");
                    break;
                }
                
                generate_test_data(arr, size, "random");
                
                printf("Generated random array (first 20 elements): ");
                print_array(arr, size < 20 ? size : 20);
                if (size > 20) printf("... (%d more elements)\n", size - 20);
                
                start = clock();
                quicksort_hybrid(arr, 0, size - 1, MEDIAN_OF_THREE);
                end = clock();
                cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                
                printf("\nSorted array (first 20 elements): ");
                print_array(arr, size < 20 ? size : 20);
                if (size > 20) printf("... (%d more elements)\n", size - 20);
                
                printf("Time taken: %f seconds\n", cpu_time_used);
                printf("Sorted correctly: %s\n", is_sorted(arr, size) ? "Yes" : "No");
                
                free(arr);
                arr = NULL;
                break;
            }
            
            case 3:
                benchmark_sorts(1000);
                break;
                
            case 4:
                printf("Exiting program...\n");
                if (arr) free(arr);
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
        
        menu_continue:;
    }
    
    return 0;
}

void quicksort_recursive(int arr[], int low, int high, PivotStrategy strategy) {
    if (low < high) {
        int pivot_index = partition(arr, low, high, strategy);
        quicksort_recursive(arr, low, pivot_index - 1, strategy);
        quicksort_recursive(arr, pivot_index + 1, high, strategy);
    }
}

void quicksort_iterative(int arr[], int low, int high, PivotStrategy strategy) {
    Stack stack;
    init_stack(&stack);
    push(&stack, low, high);
    
    while (!is_empty(&stack)) {
        int current_low, current_high;
        pop(&stack, &current_low, &current_high);
        
        if (current_low < current_high) {
            int pivot_index = partition(arr, current_low, current_high, strategy);
            
            // Push larger subarray first to optimize stack usage
            if (pivot_index - current_low > current_high - pivot_index) {
                push(&stack, current_low, pivot_index - 1);
                push(&stack, pivot_index + 1, current_high);
            } else {
                push(&stack, pivot_index + 1, current_high);
                push(&stack, current_low, pivot_index - 1);
            }
        }
    }
}

void quicksort_hybrid(int arr[], int low, int high, PivotStrategy strategy) {
    if (low < high) {
        // Use insertion sort for small subarrays
        if (high - low + 1 <= INSERTION_SORT_THRESHOLD) {
            insertion_sort(arr, low, high);
            return;
        }
        
        int pivot_index = partition(arr, low, high, strategy);
        quicksort_hybrid(arr, low, pivot_index - 1, strategy);
        quicksort_hybrid(arr, pivot_index + 1, high, strategy);
    }
}

int partition(int arr[], int low, int high, PivotStrategy strategy) {
    int pivot_index = select_pivot(arr, low, high, strategy);
    
    // Move pivot to end
    swap(&arr[pivot_index], &arr[high]);
    int pivot = arr[high];
    
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

int select_pivot(int arr[], int low, int high, PivotStrategy strategy) {
    switch (strategy) {
        case FIRST_ELEMENT:
            return low;
        case LAST_ELEMENT:
            return high;
        case MIDDLE_ELEMENT:
            return low + (high - low) / 2;
        case MEDIAN_OF_THREE:
            return median_of_three(arr, low, high);
        case RANDOM_ELEMENT:
            return low + rand() % (high - low + 1);
        default:
            return high;
    }
}

int median_of_three(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    
    if (arr[low] > arr[mid]) swap(&arr[low], &arr[mid]);
    if (arr[mid] > arr[high]) swap(&arr[mid], &arr[high]);
    if (arr[low] > arr[mid]) swap(&arr[low], &arr[mid]);
    
    return mid;
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

void swap(int* a, int* b) {
    if (a != b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

bool is_sorted(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

void generate_test_data(int arr[], int size, const char* type) {
    srand(time(NULL));
    
    if (strcmp(type, "random") == 0) {
        for (int i = 0; i < size; i++) {
            arr[i] = rand() % 1000;
        }
    } else if (strcmp(type, "ascending") == 0) {
        for (int i = 0; i < size; i++) {
            arr[i] = i;
        }
    } else if (strcmp(type, "descending") == 0) {
        for (int i = 0; i < size; i++) {
            arr[i] = size - i;
        }
    }
}

void benchmark_sorts(int size) {
    printf("\n=== Performance Benchmark (Size: %d) ===\n", size);
    
    int* test_data = (int*)malloc(size * sizeof(int));
    if (!test_data) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    const char* test_types[] = {"random", "ascending", "descending"};
    const char* strategy_names[] = {"First", "Last", "Middle", "Median-of-3", "Random"};
    
    for (int test_type = 0; test_type < 3; test_type++) {
        printf("\n--- %s data ---\n", test_types[test_type]);
        
        for (int strat = 0; strat < 5; strat++) {
            generate_test_data(test_data, size, test_types[test_type]);
            
            clock_t start = clock();
            quicksort_hybrid(test_data, 0, size - 1, (PivotStrategy)strat);
            clock_t end = clock();
            
            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("%s pivot: %f seconds - %s\n", 
                   strategy_names[strat], time_taken,
                   is_sorted(test_data, size) ? "✓" : "✗");
        }
    }
    
    free(test_data);
}

// Stack implementation
void init_stack(Stack* stack) {
    stack->top = -1;
}

void push(Stack* stack, int low, int high) {
    if (stack->top < MAX_SIZE - 1) {
        stack->top++;
        stack->frames[stack->top].low = low;
        stack->frames[stack->top].high = high;
    }
}

bool pop(Stack* stack, int* low, int* high) {
    if (stack->top >= 0) {
        *low = stack->frames[stack->top].low;
        *high = stack->frames[stack->top].high;
        stack->top--;
        return true;
    }
    return false;
}

bool is_empty(Stack* stack) {
    return stack->top == -1;
}