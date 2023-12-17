#include "calc.h"

void test_calculator(const char* input, const char* x_value, double* result,
                     double* expected);
void test_input(const char* input, const char* x_value, double* result,
                int* expected_code);
void test_credit_calculator(float principal, float interest_rate, int term,
                            const char* payment_type, float* payment,
                            float* overpayment, float* total_payment,
                            float* expected_payment,
                            float* expected_overpayment,
                            float* expected_total_payment);