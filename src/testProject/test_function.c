#include "test_function.h"

void test_calculator(const char* input, const char* x_value, double* result,
                     double* expected) {
  char str[255] = {0};
  int length = strlen(input);
  omit_spaces(input, str, length, x_value);
  stackt* stack = NULL;

  *result = convert_to_rpn(str, stack);
  if ((fabs(*result - *expected) > 0.000001)) {
    printf("\n%s", input);
    printf("\033[0;31m\nreceived: %lf\nexpected: %lf\033[0m\n", *result,
           *expected);
  }
}

void test_input(const char* input, const char* x_value, double* result,
                int* expected_code) {
  int received_code = start(input, x_value, result);
  if (received_code != *expected_code) {
    printf("%s", input);
    printf("\033[0;31m\nreceived: %d\nexpected: %d\033[0m\n", received_code,
           *expected_code);
  }
}

void test_credit_calculator(float principal, float interest_rate, int term,
                            const char* payment_type, float* payment,
                            float* overpayment, float* total_payment,
                            float* expected_payment,
                            float* expected_overpayment,
                            float* expected_total_payment) {
  calculate_credit(principal, interest_rate, term, payment_type, payment,
                   overpayment, total_payment);
  if ((fabs(*payment - *expected_payment) > 0.000001)) {
    printf("\033[0;31m\nreceived: %lf\nexpected: %lf\033[0m\n", *payment,
           *expected_payment);
  }
  if ((fabs(*overpayment - *expected_overpayment) > 0.000001)) {
    printf("\033[0;31m\nreceived: %lf\nexpected: %lf\033[0m\n", *overpayment,
           *expected_overpayment);
  }
  if ((fabs(*total_payment - *expected_total_payment) > 0.000001)) {
    printf("\033[0;31m\nreceived: %lf\nexpected: %lf\033[0m\n", *total_payment,
           *expected_total_payment);
  }
}
