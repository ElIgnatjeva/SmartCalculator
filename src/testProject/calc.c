#include "calc.h"

int start(const char* input, const char* x_value, double* result) {
  char str[255] = {0};
  stackt* stack = NULL;
  int length = strlen(input);
  omit_spaces(input, str, length, x_value);

  int check = validate_input(str);
  if (check != 0) {
    printf("Invalid input.");
  } else {
    *result = convert_to_rpn(str, stack);
  }
  return check;
}

int validate_input(char* str) {
  int result_code = OK;
  int length = strlen(str);
  for (int i = 0; i < length; i++) {
    if (is_number(str[i]) == OK) {
      if (is_number(str[i + 1]) == ERROR && is_sign(str[i + 1]) == ERROR &&
          str[i + 1] != ')' && str[i + 1] != '\0' && str[i + 1] != '.' &&
          str[i + 1] != 'm') {
        result_code = ERROR;
      }
    } else if (is_sign(str[i]) == OK) {
      if (is_number(str[i + 1]) == ERROR && str[i + 1] != '(' &&
          is_function(str, i + 1) == ERROR) {
        result_code = ERROR;
      }
    } else if (str[i] == '(') {
      if (is_sign(str[i - 1]) == ERROR &&
          is_unary_plus_or_minus(str, i + 1) == ERROR &&
          is_number(str[i + 1]) == ERROR) {
        result_code = ERROR;
      }
    } else if (str[i] == 'm') {
      if (is_mod(str, i) == ERROR) {
        result_code = ERROR;
      } else {
        i += 2;
      }
    } else if (str[i] == 's') {
      if (is_sin(str, i) == ERROR) {
        if (is_sqrt(str, i) == ERROR) {
          result_code = ERROR;
        } else {
          i += 4;
        }
      } else {
        i += 3;
      }
    } else if (str[i] == 'c') {
      if (is_cos(str, i) == ERROR) {
        result_code = ERROR;
      } else {
        i += 3;
      }
    } else if (str[i] == 't') {
      if (is_tan(str, i) == ERROR) {
        result_code = ERROR;
      } else {
        i += 3;
      }
    } else if (str[i] == 'a') {
      if (is_asin(str, i) == ERROR && is_acos(str, i) == ERROR &&
          is_atan(str, i) == ERROR) {
        result_code = ERROR;
      } else {
        i += 4;
      }
    } else if (str[i] == 'l') {
      if (is_ln(str, i) == ERROR) {
        if (is_log(str, i) == ERROR) {
          result_code = ERROR;
        } else {
          i += 3;
        }
      } else {
        i += 2;
      }
    }
  }
  return result_code;
}

double convert_to_rpn(char* str, stackt* stack) {
  stackt* support = NULL;
  stackt* res = NULL;
  double resule_value = 0.0;
  int length = strlen(str);
  char value_in_support[255] = {0};
  char arr_number[255] = {0};
  int j = 0;
  for (int i = 0; i < length; i++) {
    if (is_number(str[i]) == OK || str[i] == '.') {
      arr_number[j++] = str[i];
      if (is_number(str[i + 1]) == ERROR && str[i + 1] != '.') {
        arr_number[j] = '\0';
        push(&stack, arr_number, 0, custom_number);
        j = 0;
      }
    } else if (is_function(str, i) == OK || str[i] == '(' || str[i] == '^') {
      if (str[i] == 'm') {
        push(&support, "0", 2, custom_mod);
        i += 2;
      } else if (str[i] == 's') {
        if (str[i + 1] == 'i') {
          push(&support, "0", 3, custom_sin);
          i += 2;
        } else if (str[i + 1] == 'q') {
          push(&support, "0", 3, custom_sqrt);
          i += 3;
        }
      } else if (str[i] == 'c') {
        push(&support, "0", 3, custom_cos);
        i += 2;
      } else if (str[i] == 't') {
        push(&support, "0", 3, custom_tan);
        i += 2;
      } else if (str[i] == 'a') {
        if (str[i + 1] == 's') {
          push(&support, "0", 3, custom_asin);
        } else if (str[i + 1] == 'c') {
          push(&support, "0", 3, custom_acos);
        } else if (str[i + 1] == 't') {
          push(&support, "0", 3, custom_atan);
        }
        i += 3;
      } else if (str[i] == 'l') {
        if (str[i + 1] == 'n') {
          push(&support, "0", 3, custom_ln);
          i += 1;
        } else if (str[i + 1] == 'o') {
          push(&support, "0", 3, custom_log);
          i += 2;
        }
      } else {
        push(&support, "0", get_precedence(str[i]), get_type(str[i]));
      }
    } else if (str[i] == ',') {
      while (support->type != custom_open_brace) {
        push(&stack, check_value_in_support(support, value_in_support),
             support->precedence, support->type);
        pop(&support);
      }
    } else if (get_type(str[i]) != 0 && str[i] != ')') {  // signs
      if (is_unary_plus_or_minus(str, i) == OK) {
        push(&stack, "0", 0, custom_number);
      }
      if (get_precedence(str[i]) > check_precedence_in_support(support)) {
        push(&support, "0", get_precedence(str[i]), get_type(str[i]));
      } else {
        while (get_precedence(str[i]) <= check_precedence_in_support(support)) {
          push(&stack, check_value_in_support(support, value_in_support),
               check_precedence_in_support(support), support->type);
          pop(&support);
        }
        push(&support, "0", get_precedence(str[i]), get_type(str[i]));
      }
    } else if (str[i] == ')') {
      while (support->type != custom_open_brace) {
        push(&stack, check_value_in_support(support, value_in_support),
             check_precedence_in_support(support), support->type);
        pop(&support);
      }
      if (support->type == custom_open_brace) {
        pop(&support);
      }
    }
  }
  while (is_empty(support) == 0) {
    push(&stack, check_value_in_support(support, value_in_support),
         check_precedence_in_support(support), support->type);
    pop(&support);
  }
  reverse(&stack);
  res = calculate(&stack);
  resule_value = res->value;
  delete_elem(&res, stack);
  return resule_value;
}

void reverse(stackt** head) {
  stackt* prev = NULL;
  stackt* current = *head;
  stackt* next = NULL;
  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  *head = prev;
}

stackt* calculate(stackt** stack) {
  while ((*stack)->next != NULL) {
    stackt* operand1 = *stack;
    stackt* operand2 = operand1->next;
    stackt* operand3;
    if (operand2->next != NULL) {
      operand3 = operand2->next;
    }
    if (operand2->type == custom_number) {
      while (1) {
        if (operand3->precedence) {
          break;
        }
        operand1 = operand2;
        operand2 = operand1->next;
        operand3 = operand2->next;
      }
      if (operand3->type >= custom_minus && operand3->type <= custom_pow) {
        calculate_binary(stack, operand1, operand2, operand3);
      } else {
        calculate_unary(stack, operand2, operand3);
      }
    } else {
      calculate_unary(stack, operand1, operand2);
    }
  }
  //    print_stack(*stack);
  return *stack;
}

void calculate_binary(stackt** stack, stackt* operand1, stackt* operand2,
                      stackt* operand3) {
  double res = 0;
  if (operand3->type == custom_plus) {
    res = operand1->value + operand2->value;
  } else if (operand3->type == custom_minus) {
    res = operand1->value - operand2->value;
    // print_stack(*stack);
  } else if (operand3->type == custom_mult) {
    res = operand1->value * operand2->value;
    // print_stack(*stack);
  } else if (operand3->type == custom_div) {
    res = operand1->value / operand2->value;
    // print_stack(*stack);
  } else if (operand3->type == custom_pow) {
    res = pow(operand1->value, operand2->value);
    // print_stack(*stack);
  } else if (operand3->type == custom_mod) {
    res = fmod(operand1->value, operand2->value);
    // print_stack(*stack);
  }
  operand1->precedence = 0;
  operand1->type = custom_number;
  operand1->value = res;
  delete_elem(stack, operand3);
  delete_elem(stack, operand2);
}

void calculate_unary(stackt** stack, stackt* operand1, stackt* operand2) {
  double res = 0;
  if (operand2->type == custom_sin) {
    res = sin(operand1->value);
  } else if (operand2->type == custom_cos) {
    res = cos(operand1->value);
  } else if (operand2->type == custom_tan) {
    res = tan(operand1->value);
  } else if (operand2->type == custom_asin) {
    res = asin(operand1->value);
  } else if (operand2->type == custom_acos) {
    res = acos(operand1->value);
  } else if (operand2->type == custom_atan) {
    res = atan(operand1->value);
  } else if (operand2->type == custom_sqrt) {
    res = sqrt(operand1->value);
  } else if (operand2->type == custom_ln) {
    res = log(operand1->value);
  } else if (operand2->type == custom_log) {
    res = log10(operand1->value);
  }
  operand1->precedence = 0;
  operand1->type = custom_number;
  operand1->value = res;
  delete_elem(stack, operand2);
}
