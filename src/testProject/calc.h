#ifndef CALC_H_
#define CALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define ERROR 1

typedef enum precedence {
  custom_number = 0,
  custom_x,            // 1
  custom_open_brace,   // 2
  custom_close_brace,  // 3
  custom_minus,        // 4
  custom_plus,         // 5
  custom_mult,         // 6
  custom_div,          // 7
  custom_mod,          // 8
  custom_pow,          // 9
  custom_sin,          // 10
  custom_cos,
  custom_tan,
  custom_asin,
  custom_acos,
  custom_atan,
  custom_sqrt,
  custom_ln,
  custom_log
} type_t;

typedef struct node {
  double value;
  int precedence;
  type_t type;
  struct node* next;
} stackt;

int start(const char* input, const char* x_value, double* result);
int validate_input(char* str);
void omit_spaces(const char* str, char* str2, int length, const char* x_value);
double custom_atoi(char c);
double is_digit(char c);
int is_sign(char c);
int is_number(char c);
int is_unary_plus_or_minus(char* str, int i);

int is_empty(stackt* s);
int get_precedence(char op);
void push(stackt** stack_top, char* value, int precedence, type_t type);
void pop(stackt** stack_top);

int is_function(char* str, int i);
type_t get_type(char c);
double convert_to_rpn(char* str, stackt* stack);

int check_precedence_in_support(stackt* s);
char* check_value_in_support(stackt* s, char* value_in_support);

void print_stack(stackt* stack);
void reverse(stackt** stack);
stackt* calculate(stackt** stack);
char* get_value(char* buffer, double expression);

void delete_elem(stackt** root, stackt* lst);

int is_mod(char* str, int start);
int is_cos(char* str, int start);
int is_sin(char* str, int start);
int is_tan(char* str, int start);
int is_asin(char* str, int start);
int is_acos(char* str, int start);
int is_atan(char* str, int start);
int is_sqrt(char* str, int start);
int is_ln(char* str, int start);
int is_log(char* str, int start);

void calculate_binary(stackt** stack, stackt* operand1, stackt* operand2,
                      stackt* operand3);
void calculate_unary(stackt** stack, stackt* operand2, stackt* operand3);
float calculate_annuity_payment(float principal, float interest_rate, int term);
float calculate_differential_payment(float principal, float interest_rate,
                                     int term, int month);
void calculate_credit(float principal, float interest_rate, int term,
                      const char* payment_type, float* payment,
                      float* overpayment, float* total_payment);

// int deposit_calc();
// void calculate_deposit(float deposit_amount, int term, float interest_rate,
//                        float tax_rate, int payout_period,
//                        int interest_compounding, float* interest_earned,
//                        float* tax_amount, float* final_amount);
// float calculate_tax(float amount, float tax_rate);

#endif  // CALC_H_
