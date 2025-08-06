#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_SIZE 1000

// Stack structure for operators
typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;

// Function prototypes
void init_stack(Stack* stack);
bool is_empty(Stack* stack);
bool is_full(Stack* stack);
void push(Stack* stack, char item);
char pop(Stack* stack);
char peek(Stack* stack);

bool is_operator(char c);
bool is_operand(char c);
int get_precedence(char op);
bool is_left_associative(char op);
bool is_right_associative(char op);

char* infix_to_postfix(const char* infix);
char* infix_to_prefix(const char* infix);
int evaluate_postfix(const char* postfix);
int evaluate_prefix(const char* prefix);

void remove_spaces(char* str);
bool is_valid_expression(const char* expr);
void print_step_by_step(const char* infix);

int main() {
    char infix[MAX_SIZE];
    char* postfix;
    char* prefix;
    int choice;
    
    printf("=== Optimized Infix to Postfix/Prefix Converter ===\n");
    
    while (1) {
        printf("\n=== MENU ===\n");
        printf("1. Convert Infix to Postfix\n");
        printf("2. Convert Infix to Prefix\n");
        printf("3. Evaluate Postfix Expression\n");
        printf("4. Evaluate Prefix Expression\n");
        printf("5. Step-by-step Conversion\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1:
                printf("Enter infix expression: ");
                scanf(" %[^\n]", infix);
                
                if (!is_valid_expression(infix)) {
                    printf("Invalid expression format!\n");
                    break;
                }
                
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
                printf("Enter infix expression: ");
                scanf(" %[^\n]", infix);
                
                if (!is_valid_expression(infix)) {
                    printf("Invalid expression format!\n");
                    break;
                }
                
                prefix = infix_to_prefix(infix);
                if (prefix) {
                    printf("Infix:   %s\n", infix);
                    printf("Prefix:  %s\n", prefix);
                    free(prefix);
                } else {
                    printf("Error in conversion!\n");
                }
                break;
                
            case 3:
                printf("Enter postfix expression: ");
                scanf(" %[^\n]", infix);
                
                int result_post = evaluate_postfix(infix);
                if (result_post != INT_MIN) {
                    printf("Postfix: %s\n", infix);
                    printf("Result:  %d\n", result_post);
                } else {
                    printf("Error in evaluation!\n");
                }
                break;
                
            case 4:
                printf("Enter prefix expression: ");
                scanf(" %[^\n]", infix);
                
                int result_pre = evaluate_prefix(infix);
                if (result_pre != INT_MIN) {
                    printf("Prefix: %s\n", infix);
                    printf("Result: %d\n", result_pre);
                } else {
                    printf("Error in evaluation!\n");
                }
                break;
                
            case 5:
                printf("Enter infix expression: ");
                scanf(" %[^\n]", infix);
                
                if (!is_valid_expression(infix)) {
                    printf("Invalid expression format!\n");
                    break;
                }
                
                print_step_by_step(infix);
                break;
                
            case 6:
                printf("Exiting program...\n");
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}

// Stack operations
void init_stack(Stack* stack) {
    stack->top = -1;
}

bool is_empty(Stack* stack) {
    return stack->top == -1;
}

bool is_full(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack* stack, char item) {
    if (!is_full(stack)) {
        stack->items[++stack->top] = item;
    }
}

char pop(Stack* stack) {
    if (!is_empty(stack)) {
        return stack->items[stack->top--];
    }
    return '\0';
}

char peek(Stack* stack) {
    if (!is_empty(stack)) {
        return stack->items[stack->top];
    }
    return '\0';
}

// Utility functions
bool is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || 
            c == '^' || c == '%');
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

bool is_right_associative(char op) {
    return (op == '^');
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

bool is_valid_expression(const char* expr) {
    int paren_count = 0;
    bool expecting_operand = true;
    
    for (int i = 0; expr[i]; i++) {
        char c = expr[i];
        
        if (c == ' ' || c == '\t') {
            continue;
        }
        
        if (c == '(') {
            paren_count++;
            expecting_operand = true;
        } else if (c == ')') {
            paren_count--;
            if (paren_count < 0) return false;
            expecting_operand = false;
        } else if (is_operand(c)) {
            if (!expecting_operand) return false;
            expecting_operand = false;
        } else if (is_operator(c)) {
            if (expecting_operand && c != '-' && c != '+') return false;
            expecting_operand = true;
        } else {
            return false; // Invalid character
        }
    }
    
    return paren_count == 0 && !expecting_operand;
}

// Shunting Yard Algorithm for Infix to Postfix
char* infix_to_postfix(const char* infix) {
    char* input = (char*)malloc(strlen(infix) + 1);
    strcpy(input, infix);
    remove_spaces(input);
    
    char* output = (char*)malloc(2 * strlen(input) + 1);
    Stack operator_stack;
    init_stack(&operator_stack);
    
    int output_index = 0;
    
    for (int i = 0; input[i]; i++) {
        char c = input[i];
        
        if (is_operand(c)) {
            output[output_index++] = c;
            output[output_index++] = ' ';
        } else if (c == '(') {
            push(&operator_stack, c);
        } else if (c == ')') {
            while (!is_empty(&operator_stack) && peek(&operator_stack) != '(') {
                output[output_index++] = pop(&operator_stack);
                output[output_index++] = ' ';
            }
            if (!is_empty(&operator_stack)) {
                pop(&operator_stack); // Remove '('
            }
        } else if (is_operator(c)) {
            while (!is_empty(&operator_stack) && 
                   peek(&operator_stack) != '(' &&
                   (get_precedence(peek(&operator_stack)) > get_precedence(c) ||
                    (get_precedence(peek(&operator_stack)) == get_precedence(c) && 
                     is_left_associative(c)))) {
                output[output_index++] = pop(&operator_stack);
                output[output_index++] = ' ';
            }
            push(&operator_stack, c);
        }
    }
    
    while (!is_empty(&operator_stack)) {
        output[output_index++] = pop(&operator_stack);
        output[output_index++] = ' ';
    }
    
    if (output_index > 0 && output[output_index - 1] == ' ') {
        output_index--;
    }
    output[output_index] = '\0';
    
    free(input);
    return output;
}

// Reverse string for prefix conversion
void reverse_string(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

// Convert infix to prefix
char* infix_to_prefix(const char* infix) {
    char* reversed_infix = (char*)malloc(strlen(infix) + 1);
    strcpy(reversed_infix, infix);
    reverse_string(reversed_infix);
    
    // Replace '(' with ')' and vice versa
    for (int i = 0; reversed_infix[i]; i++) {
        if (reversed_infix[i] == '(') {
            reversed_infix[i] = ')';
        } else if (reversed_infix[i] == ')') {
            reversed_infix[i] = '(';
        }
    }
    
    char* postfix = infix_to_postfix(reversed_infix);
    reverse_string(postfix);
    
    free(reversed_infix);
    return postfix;
}

// Evaluate postfix expression
int evaluate_postfix(const char* postfix) {
    Stack operand_stack;
    init_stack(&operand_stack);
    
    char* input = (char*)malloc(strlen(postfix) + 1);
    strcpy(input, postfix);
    
    char* token = strtok(input, " ");
    
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&operand_stack, atoi(token));
        } else if (is_operator(token[0]) && strlen(token) == 1) {
            if (operand_stack.top < 1) {
                free(input);
                return INT_MIN; // Error: insufficient operands
            }
            
            int operand2 = pop(&operand_stack);
            int operand1 = pop(&operand_stack);
            int result;
            
            switch (token[0]) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': 
                    if (operand2 == 0) {
                        free(input);
                        return INT_MIN; // Division by zero
                    }
                    result = operand1 / operand2; 
                    break;
                case '%': 
                    if (operand2 == 0) {
                        free(input);
                        return INT_MIN; // Division by zero
                    }
                    result = operand1 % operand2; 
                    break;
                case '^': 
                    result = 1;
                    for (int i = 0; i < operand2; i++) {
                        result *= operand1;
                    }
                    break;
                default:
                    free(input);
                    return INT_MIN; // Invalid operator
            }
            push(&operand_stack, result);
        } else if (isalpha(token[0])) {
            printf("Variable '%s' found. Enter its value: ", token);
            int value;
            scanf("%d", &value);
            push(&operand_stack, value);
        }
        
        token = strtok(NULL, " ");
    }
    
    free(input);
    
    if (operand_stack.top == 0) {
        return operand_stack.items[0];
    } else {
        return INT_MIN; // Error: invalid expression
    }
}

// Evaluate prefix expression
int evaluate_prefix(const char* prefix) {
    char* reversed = (char*)malloc(strlen(prefix) + 1);
    strcpy(reversed, prefix);
    reverse_string(reversed);
    
    int result = evaluate_postfix(reversed);
    free(reversed);
    return result;
}

// Print step-by-step conversion
void print_step_by_step(const char* infix) {
    char* input = (char*)malloc(strlen(infix) + 1);
    strcpy(input, infix);
    remove_spaces(input);
    
    char output[MAX_SIZE] = "";
    Stack operator_stack;
    init_stack(&operator_stack);
    
    int output_index = 0;
    
    printf("\nStep-by-step Infix to Postfix conversion:\n");
    printf("%-10s %-15s %-15s %-20s\n", "Step", "Symbol", "Output", "Operator Stack");
    printf("%-10s %-15s %-15s %-20s\n", "----", "------", "------", "---------------");
    
    int step = 1;
    
    for (int i = 0; input[i]; i++) {
        char c = input[i];
        char stack_str[MAX_SIZE] = "";
        
        // Build stack string for display
        for (int j = 0; j <= operator_stack.top; j++) {
            char temp[2] = {operator_stack.items[j], '\0'};
            strcat(stack_str, temp);
        }
        
        if (is_operand(c)) {
            output[output_index++] = c;
            output[output_index++] = ' ';
            output[output_index] = '\0';
            
            printf("%-10d %-15c %-15s %-20s\n", step++, c, output, stack_str);
        } else if (c == '(') {
            push(&operator_stack, c);
            
            // Update stack string
            stack_str[0] = '\0';
            for (int j = 0; j <= operator_stack.top; j++) {
                char temp[2] = {operator_stack.items[j], '\0'};
                strcat(stack_str, temp);
            }
            
            printf("%-10d %-15c %-15s %-20s\n", step++, c, output, stack_str);
        } else if (c == ')') {
            while (!is_empty(&operator_stack) && peek(&operator_stack) != '(') {
                output[output_index++] = pop(&operator_stack);
                output[output_index++] = ' ';
            }
            if (!is_empty(&operator_stack)) {
                pop(&operator_stack); // Remove '('
            }
            output[output_index] = '\0';
            
            // Update stack string
            stack_str[0] = '\0';
            for (int j = 0; j <= operator_stack.top; j++) {
                char temp[2] = {operator_stack.items[j], '\0'};
                strcat(stack_str, temp);
            }
            
            printf("%-10d %-15c %-15s %-20s\n", step++, c, output, stack_str);
        } else if (is_operator(c)) {
            while (!is_empty(&operator_stack) && 
                   peek(&operator_stack) != '(' &&
                   (get_precedence(peek(&operator_stack)) > get_precedence(c) ||
                    (get_precedence(peek(&operator_stack)) == get_precedence(c) && 
                     is_left_associative(c)))) {
                output[output_index++] = pop(&operator_stack);
                output[output_index++] = ' ';
            }
            push(&operator_stack, c);
            output[output_index] = '\0';
            
            // Update stack string
            stack_str[0] = '\0';
            for (int j = 0; j <= operator_stack.top; j++) {
                char temp[2] = {operator_stack.items[j], '\0'};
                strcat(stack_str, temp);
            }
            
            printf("%-10d %-15c %-15s %-20s\n", step++, c, output, stack_str);
        }
    }
    
    // Pop remaining operators
    while (!is_empty(&operator_stack)) {
        output[output_index++] = pop(&operator_stack);
        output[output_index++] = ' ';
        output[output_index] = '\0';
        
        char stack_str[MAX_SIZE] = "";
        for (int j = 0; j <= operator_stack.top; j++) {
            char temp[2] = {operator_stack.items[j], '\0'};
            strcat(stack_str, temp);
        }
        
        printf("%-10d %-15s %-15s %-20s\n", step++, "pop", output, stack_str);
    }
    
    // Remove trailing space
    if (output_index > 0 && output[output_index - 1] == ' ') {
        output[output_index - 1] = '\0';
    }
    
    printf("\nFinal Result: %s\n", output);
    free(input);
}