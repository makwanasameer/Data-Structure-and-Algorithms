#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for circular linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Circular linked list structure
typedef struct CircularLinkedList {
    Node* last;  // Points to the last node (tail)
    int size;
} CircularLinkedList;

// Function prototypes
CircularLinkedList* create_list();
void free_list(CircularLinkedList* list);
bool is_empty(CircularLinkedList* list);
int get_size(CircularLinkedList* list);

// Insertion operations
bool insert_at_beginning(CircularLinkedList* list, int data);
bool insert_at_end(CircularLinkedList* list, int data);
bool insert_at_position(CircularLinkedList* list, int data, int position);
bool insert_after_value(CircularLinkedList* list, int data, int target_value);
bool insert_before_value(CircularLinkedList* list, int data, int target_value);

// Deletion operations
bool delete_from_beginning(CircularLinkedList* list);
bool delete_from_end(CircularLinkedList* list);
bool delete_at_position(CircularLinkedList* list, int position);
bool delete_by_value(CircularLinkedList* list, int value);
bool delete_all_occurrences(CircularLinkedList* list, int value);

// Search and access operations
Node* search(CircularLinkedList* list, int value);
int get_at_position(CircularLinkedList* list, int position);
int get_position_of_value(CircularLinkedList* list, int value);
bool contains(CircularLinkedList* list, int value);

// Display operations
void display_forward(CircularLinkedList* list);
void display_backward(CircularLinkedList* list);
void display_from_position(CircularLinkedList* list, int position, int count);

// Utility operations
void reverse_list(CircularLinkedList* list);
CircularLinkedList* copy_list(CircularLinkedList* list);
bool are_lists_equal(CircularLinkedList* list1, CircularLinkedList* list2);
void sort_list(CircularLinkedList* list);
void remove_duplicates(CircularLinkedList* list);
CircularLinkedList* merge_lists(CircularLinkedList* list1, CircularLinkedList* list2);

// Statistical operations
int find_max(CircularLinkedList* list);
int find_min(CircularLinkedList* list);
double calculate_average(CircularLinkedList* list);
int count_occurrences(CircularLinkedList* list, int value);

// Helper functions
Node* create_node(int data);
Node* get_node_at_position(CircularLinkedList* list, int position);
void print_list_info(CircularLinkedList* list);

int main() {
    CircularLinkedList* list = create_list();
    int choice, data, position, target_value, count;
    
    if (!list) {
        printf("Failed to create list!\n");
        return 1;
    }
    
    printf("=== Optimized Circular Linked List ===\n");
    
    while (1) {
        printf("\n=== CIRCULAR LINKED LIST MENU ===\n");
        printf("1.  Insert at beginning\n");
        printf("2.  Insert at end\n");
        printf("3.  Insert at position\n");
        printf("4.  Insert after value\n");
        printf("5.  Insert before value\n");
        printf("6.  Delete from beginning\n");
        printf("7.  Delete from end\n");
        printf("8.  Delete at position\n");
        printf("9.  Delete by value\n");
        printf("10. Delete all occurrences\n");
        printf("11. Search for value\n");
        printf("12. Get value at position\n");
        printf("13. Get position of value\n");
        printf("14. Display forward\n");
        printf("15. Display backward\n");
        printf("16. Display from position\n");
        printf("17. Reverse list\n");
        printf("18. Sort list\n");
        printf("19. Remove duplicates\n");
        printf("20. List statistics\n");
        printf("21. List information\n");
        printf("22. Clear list\n");
        printf("23. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                if (scanf("%d", &data) == 1) {
                    if (insert_at_beginning(list, data)) {
                        printf("Value %d inserted at beginning.\n", data);
                    } else {
                        printf("Failed to insert value.\n");
                    }
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 2:
                printf("Enter value to insert: ");
                if (scanf("%d", &data) == 1) {
                    if (insert_at_end(list, data)) {
                        printf("Value %d inserted at end.\n", data);
                    } else {
                        printf("Failed to insert value.\n");
                    }
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 3:
                printf("Enter value to insert: ");
                if (scanf("%d", &data) != 1) {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                    break;
                }
                printf("Enter position (0-based): ");
                if (scanf("%d", &position) == 1) {
                    if (insert_at_position(list, data, position)) {
                        printf("Value %d inserted at position %d.\n", data, position);
                    } else {
                        printf("Failed to insert value at position %d.\n", position);
                    }
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 4:
                if (is_empty(list)) {
                    printf("List is empty!\n");
                    break;
                }
                printf("Enter value to insert: ");
                if (scanf("%d", &data) != 1) {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                    break;
                }
                printf("Enter target value to insert after: ");
                if (scanf("%d", &target_value) == 1) {
                    if (insert_after_value(list, data, target_value)) {
                        printf("Value %d inserted after %d.\n", data, target_value);
                    } else {
                        printf("Target value %d not found.\n", target_value);
                    }
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 5:
                if (is_empty(list)) {
                    printf("List is empty!\n");
                    break;
                }
                printf("Enter value to insert: ");
                if (scanf("%d", &data) != 1) {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                    break;
                }
                printf("Enter target value to insert before: ");
                if (scanf("%d", &target_value) == 1) {
                    if (insert_before_value(list, data, target_value)) {
                        printf("Value %d inserted before %d.\n", data, target_value);
                    } else {
                        printf("Target value %d not found.\n", target_value);
                    }
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 6:
                if (delete_from_beginning(list)) {
                    printf("Value deleted from beginning.\n");
                } else {
                    printf("List is empty!\n");
                }
                break;
                
            case 7:
                if (delete_from_end(list)) {
                    printf("Value deleted from end.\n");
                } else {
                    printf("List is empty!\n");
                }
                break;
                
            case 8:
                if (is_empty(list)) {
                    printf("List is empty!\n");
                    break;
                }
                printf("Enter position to delete (0-based): ");
                if (scanf("%d", &position) == 1) {
                    if (delete_at_position(list, position)) {
                        printf("Value deleted from position %d.\n", position);
                    } else {
                        printf("Invalid position %d.\n", position);
                    }
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 9:
                if (is_empty(list)) {
                    printf("List is empty!\n");
                    break;
                }
                printf("Enter value to delete: ");
                if (scanf("%d", &data) == 1) {
                    if (delete_by_value(list, data)) {
                        printf("Value %d deleted.\n", data);
                    } else {
                        printf("Value %d not found.\n", data);
                    }
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 10:
                if (is_empty(list)) {
                    printf("List is empty!\n");
                    break;
                }
                printf("Enter value to delete all occurrences: ");
                if (scanf("%d", &data) == 1) {
                    if (delete_all_occurrences(list, data)) {
                        printf("All occurrences of %d deleted.\n", data);
                    } else {
                        printf("Value %d not found.\n", data);
                    }
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 11:
                if (is_empty(list)) {
                    printf("List is empty!\n");
                    break;
                }
                printf("Enter value to search: ");
                if (scanf("%d", &data) == 1) {
                    Node* found = search(list, data);
                    if (found) {
                        printf("Value %d found in the list.\n", data);
                    } else {
                        printf("Value %d not found.\n", data);
                    }
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 12:
                if (is_empty(list)) {
                    printf("List is empty!\n");
                    break;
                }
                printf("Enter position (0-based): ");
                if (scanf("%d", &position) == 1) {
                    int value = get_at_position(list, position);
                    if (value != INT_MIN) {
                        printf("Value at position %d: %d\n", position, value);
                    } else {
                        printf("Invalid position %d.\n", position);
                    }
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 13:
                if (is_empty(list)) {
                    printf("List is empty!\n");
                    break;
                }
                printf("Enter value to find position: ");
                if (scanf("%d", &data) == 1) {
                    int pos = get_position_of_value(list, data);
                    if (pos != -1) {
                        printf("First occurrence of %d is at position %d.\n", data, pos);
                    } else {
                        printf("Value %d not found.\n", data);
                    }
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 14:
                printf("List (forward): ");
                display_forward(list);
                break;
                
            case 15:
                printf("List (backward): ");
                display_backward(list);
                break;
                
            case 16:
                if (is_empty(list)) {
                    printf("List is empty!\n");
                    break;
                }
                printf("Enter starting position: ");
                if (scanf("%d", &position) != 1) {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                    break;
                }
                printf("Enter count of elements to display: ");
                if (scanf("%d", &count) == 1) {
                    printf("List from position %d (%d elements): ", position, count);
                    display_from_position(list, position, count);
                } else {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 17:
                if (is_empty(list)) {
                    printf("List is empty!\n");
                } else {
                    reverse_list(list);
                    printf("List reversed successfully.\n");
                }
                break;
                
            case 18:
                if (is_empty(list)) {
                    printf("List is empty!\n");
                } else {
                    sort_list(list);
                    printf("List sorted successfully.\n");
                }
                break;
                
            case 19:
                if (is_empty(list)) {
                    printf("List is empty!\n");
                } else {
                    remove_duplicates(list);
                    printf("Duplicates removed successfully.\n");
                }
                break;
                
            case 20:
                if (is_empty(list)) {
                    printf("List is empty!\n");
                } else {
                    printf("\n=== List Statistics ===\n");
                    printf("Size: %d\n", get_size(list));
                    printf("Maximum value: %d\n", find_max(list));
                    printf("Minimum value: %d\n", find_min(list));
                    printf("Average value: %.2f\n", calculate_average(list));
                }
                break;
                
            case 21:
                print_list_info(list);
                break;
                
            case 22:
                if (!is_empty(list)) {
                    while (!is_empty(list)) {
                        delete_from_beginning(list);
                    }
                    printf("List cleared successfully.\n");
                } else {
                    printf("List is already empty.\n");
                }
                break;
                
            case 23:
                free_list(list);
                printf("Exiting program...\n");
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}

// List management functions
CircularLinkedList* create_list() {
    CircularLinkedList* list = (CircularLinkedList*)malloc(sizeof(CircularLinkedList));
    if (list) {
        list->last = NULL;
        list->size = 0;
    }
    return list;
}

void free_list(CircularLinkedList* list) {
    if (!list) return;
    
    while (!is_empty(list)) {
        delete_from_beginning(list);
    }
    
    free(list);
}

bool is_empty(CircularLinkedList* list) {
    return list->last == NULL;
}

int get_size(CircularLinkedList* list) {
    return list->size;
}

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node) {
        new_node->data = data;
        new_node->next = NULL;
    }
    return new_node;
}

// Insertion operations
bool insert_at_beginning(CircularLinkedList* list, int data) {
    Node* new_node = create_node(data);
    if (!new_node) return false;
    
    if (is_empty(list)) {
        new_node->next = new_node;
        list->last = new_node;
    } else {
        new_node->next = list->last->next;
        list->last->next = new_node;
    }
    
    list->size++;
    return true;
}

bool insert_at_end(CircularLinkedList* list, int data) {
    Node* new_node = create_node(data);
    if (!new_node) return false;
    
    if (is_empty(list)) {
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

bool insert_at_position(CircularLinkedList* list, int data, int position) {
    if (position < 0 || position > list->size) {
        return false;
    }
    
    if (position == 0) {
        return insert_at_beginning(list, data);
    }
    
    if (position == list->size) {
        return insert_at_end(list, data);
    }
    
    Node* new_node = create_node(data);
    if (!new_node) return false;
    
    Node* current = list->last->next; // Start from first node
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    list->size++;
    
    return true;
}

bool insert_after_value(CircularLinkedList* list, int data, int target_value) {
    if (is_empty(list)) return false;
    
    Node* current = list->last->next; // Start from first node
    do {
        if (current->data == target_value) {
            Node* new_node = create_node(data);
            if (!new_node) return false;
            
            new_node->next = current->next;
            current->next = new_node;
            
            if (current == list->last) {
                list->last = new_node;
            }
            
            list->size++;
            return true;
        }
        current = current->next;
    } while (current != list->last->next);
    
    return false;
}

bool insert_before_value(CircularLinkedList* list, int data, int target_value) {
    if (is_empty(list)) return false;
    
    // Special case: inserting before the first node
    if (list->last->next->data == target_value) {
        return insert_at_beginning(list, data);
    }
    
    Node* current = list->last->next; // Start from first node
    do {
        if (current->next->data == target_value) {
            Node* new_node = create_node(data);
            if (!new_node) return false;
            
            new_node->next = current->next;
            current->next = new_node;
            list->size++;
            return true;
        }
        current = current->next;
    } while (current != list->last);
    
    return false;
}

// Deletion operations
bool delete_from_beginning(CircularLinkedList* list) {
    if (is_empty(list)) return false;
    
    Node* first = list->last->next;
    
    if (first == list->last) { // Only one node
        free(first);
        list->last = NULL;
    } else {
        list->last->next = first->next;
        free(first);
    }
    
    list->size--;
    return true;
}

bool delete_from_end(CircularLinkedList* list) {
    if (is_empty(list)) return false;
    
    if (list->last->next == list->last) { // Only one node
        free(list->last);
        list->last = NULL;
    } else {
        Node* current = list->last->next;
        while (current->next != list->last) {
            current = current->next;
        }
        
        current->next = list->last->next;
        free(list->last);
        list->last = current;
    }
    
    list->size--;
    return true;
}

bool delete_at_position(CircularLinkedList* list, int position) {
    if (is_empty(list) || position < 0 || position >= list->size) {
        return false;
    }
    
    if (position == 0) {
        return delete_from_beginning(list);
    }
    
    Node* current = list->last->next; // Start from first node
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    
    Node* to_delete = current->next;
    current->next = to_delete->next;
    
    if (to_delete == list->last) {
        list->last = current;
    }
    
    free(to_delete);
    list->size--;
    
    return true;
}

bool delete_by_value(CircularLinkedList* list, int value) {
    if (is_empty(list)) return false;
    
    // Special case: deleting the first node
    if (list->last->next->data == value) {
        return delete_from_beginning(list);
    }
    
    Node* current = list->last->next; // Start from first node
    do {
        if (current->next->data == value) {
            Node* to_delete = current->next;
            current->next = to_delete->next;
            
            if (to_delete == list->last) {
                list->last = current;
            }
            
            free(to_delete);
            list->size--;
            return true;
        }
        current = current->next;
    } while (current != list->last);
    
    return false;
}

bool delete_all_occurrences(CircularLinkedList* list, int value) {
    if (is_empty(list)) return false;
    
    bool found = false;
    
    // Keep deleting while the value exists
    while (contains(list, value)) {
        delete_by_value(list, value);
        found = true;
    }
    
    return found;
}

// Search and access operations
Node* search(CircularLinkedList* list, int value) {
    if (is_empty(list)) return NULL;
    
    Node* current = list->last->next; // Start from first node
    do {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    } while (current != list->last->next);
    
    return NULL;
}

int get_at_position(CircularLinkedList* list, int position) {
    if (is_empty(list) || position < 0 || position >= list->size) {
        return INT_MIN; // Error value
    }
    
    Node* current = list->last->next; // Start from first node
    for (int i = 0; i < position; i++) {
        current = current->next;
    }
    
    return current->data;
}

int get_position_of_value(CircularLinkedList* list, int value) {
    if (is_empty(list)) return -1;
    
    Node* current = list->last->next; // Start from first node
    int position = 0;
    
    do {
        if (current->data == value) {
            return position;
        }
        current = current->next;
        position++;
    } while (current != list->last->next);
    
    return -1;
}

bool contains(CircularLinkedList* list, int value) {
    return search(list, value) != NULL;
}

// Display operations
void display_forward(CircularLinkedList* list) {
    if (is_empty(list)) {
        printf("List is empty.\n");
        return;
    }
    
    Node* current = list->last->next; // Start from first node
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != list->last->next);
    
    printf("(circular)\n");
}

void display_backward(CircularLinkedList* list) {
    if (is_empty(list)) {
        printf("List is empty.\n");
        return;
    }
    
    // Create an array to store values for reverse display
    int* values = (int*)malloc(list->size * sizeof(int));
    if (!values) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    Node* current = list->last->next; // Start from first node
    int index = 0;
    
    do {
        values[index++] = current->data;
        current = current->next;
    } while (current != list->last->next);
    
    for (int i = list->size - 1; i >= 0; i--) {
        printf("%d ", values[i]);
    }
    
    printf("(circular)\n");
    free(values);
}

void display_from_position(CircularLinkedList* list, int position, int count) {
    if (is_empty(list) || position < 0 || count <= 0) {
        printf("Invalid parameters or empty list.\n");
        return;
    }
    
    Node* current = list->last->next; // Start from first node
    
    // Move to starting position
    for (int i = 0; i < position % list->size; i++) {
        current = current->next;
    }
    
    // Display 'count' elements
    for (int i = 0; i < count; i++) {
        printf("%d ", current->data);
        current = current->next;
    }
    
    printf("\n");
}

// Utility operations
void reverse_list(CircularLinkedList* list) {
    if (is_empty(list) || list->size == 1) return;
    
    Node* prev = list->last;
    Node* current = list->last->next;
    Node* next;
    
    do {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    } while (current != list->last->next);
    
    list->last = list->last->next;
}

void sort_list(CircularLinkedList* list) {
    if (is_empty(list) || list->size == 1) return;
    
    // Simple bubble sort
    bool swapped;
    do {
        swapped = false;
        Node* current = list->last->next;
        
        for (int i = 0; i < list->size - 1; i++) {
            if (current->data > current->next->data) {
                // Swap data
                int temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

void remove_duplicates(CircularLinkedList* list) {
    if (is_empty(list) || list->size == 1) return;
    
    Node* current = list->last->next; // Start from first node
    
    do {
        Node* runner = current;
        while (runner->next != list->last->next) {
            if (runner->next->data == current->data) {
                Node* duplicate = runner->next;
                runner->next = duplicate->next;
                
                if (duplicate == list->last) {
                    list->last = runner;
                }
                
                free(duplicate);
                list->size--;
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    } while (current != list->last->next);
}

// Statistical operations
int find_max(CircularLinkedList* list) {
    if (is_empty(list)) return INT_MIN;
    
    int max = list->last->next->data;
    Node* current = list->last->next->next;
    
    while (current != list->last->next) {
        if (current->data > max) {
            max = current->data;
        }
        current = current->next;
    }
    
    return max;
}

int find_min(CircularLinkedList* list) {
    if (is_empty(list)) return INT_MAX;
    
    int min = list->last->next->data;
    Node* current = list->last->next->next;
    
    while (current != list->last->next) {
        if (current->data < min) {
            min = current->data;
        }
        current = current->next;
    }
    
    return min;
}

double calculate_average(CircularLinkedList* list) {
    if (is_empty(list)) return 0.0;
    
    long long sum = 0;
    Node* current = list->last->next; // Start from first node
    
    do {
        sum += current->data;
        current = current->next;
    } while (current != list->last->next);
    
    return (double)sum / list->size;
}

int count_occurrences(CircularLinkedList* list, int value) {
    if (is_empty(list)) return 0;
    
    int count = 0;
    Node* current = list->last->next; // Start from first node
    
    do {
        if (current->data == value) {
            count++;
        }
        current = current->next;
    } while (current != list->last->next);
    
    return count;
}

void print_list_info(CircularLinkedList* list) {
    printf("\n=== List Information ===\n");
    printf("Size: %d\n", list->size);
    printf("Empty: %s\n", is_empty(list) ? "Yes" : "No");
    
    if (!is_empty(list)) {
        printf("First element: %d\n", list->last->next->data);
        printf("Last element: %d\n", list->last->data);
        printf("Memory address of last node: %p\n", (void*)list->last);
        printf("Next of last points to: %p\n", (void*)list->last->next);
        printf("Circular structure: %s\n", 
               list->last->next != NULL ? "Valid" : "Invalid");
    }
}