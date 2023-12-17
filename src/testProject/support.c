#include "calc.h"

/**
 * @brief
 *
 * @param s - stack
 * @return int 1(true), 0(false)
 */
int is_empty(stackt* s) { return s == NULL; }

int get_precedence(char op) {
  //    int priority = 0;
  if (op == '+' || op == '-')
    return 1;
  else if (op == '*' || op == '/' || op == 'm')
    return 2;
  else if (op == '^' || op == 's' || op == 'c' || op == 't' || op == 'l')
    return 3;
  else
    return 0;
}

type_t get_type(char c) {
  type_t type = 0;
  if (c == '+') {
    type = custom_plus;
  } else if (c == '-') {
    type = custom_minus;
  } else if (c == '*') {
    type = custom_mult;
  } else if (c == '(') {
    type = custom_open_brace;
  } else if (c == ')') {
    type = custom_close_brace;
  } else if (c == '/') {
    type = custom_div;
  } else if (c == '^') {
    type = custom_pow;
  }
  return type;
}

int check_precedence_in_support(stackt* s) {
  if (s == NULL) {
    return 0;
  } else {
    return s->precedence;
  }
}

char* check_value_in_support(stackt* s, char* value_in_support) {
  double value = s->value;
  sprintf(value_in_support, "%lf", value);
  return value_in_support;
}

void push(stackt** stack_top, char* value, int precedence, type_t type) {
  if (*stack_top == NULL) {
    stackt* new_node = (stackt*)malloc(sizeof(stackt));
    sscanf(value, "%lf", &new_node->value);
    new_node->precedence = precedence;
    new_node->type = type;
    new_node->next = NULL;
    *stack_top = new_node;
  } else {
    stackt* new_node = (stackt*)malloc(sizeof(stackt));
    sscanf(value, "%lf", &new_node->value);
    new_node->precedence = precedence;
    new_node->type = type;
    new_node->next = *stack_top;
    *stack_top = new_node;
  }
}

void pop(stackt** stack_top) {
  if (*stack_top != NULL) {
    stackt* temp = *stack_top;
    *stack_top = (*stack_top)->next;
    free(temp);
  }
}

void print_stack(stackt* stack) {
  printf("Stack:\n");

  if (stack == NULL) {
    printf("Empty\n");
    return;
  }

  stackt* current = stack;
  while (current != NULL) {
    // printf("Value: %.2f, Precedence: %d, Type: %u\n", current->value,
    // current->precedence, current->type);
    printf("%.2f ", current->value);
    current = current->next;
  }
  printf("\n");
}

void delete_elem(stackt** root, stackt* lst) {
  stackt* temp;
  temp = *root;
  if (*root == lst) {
    temp = (*root)->next;
    free(*root);
    *root = temp;
  } else {
    while (temp->next != lst) {
      temp = temp->next;
    }
    temp->next = lst->next;
    free(lst);
  }
}

char* get_value(char* buffer, double expression) {
  sprintf(buffer, "%lf", expression);
  return buffer;
}
