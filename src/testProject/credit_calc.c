#include "calc.h"

float calculate_annuity_payment(float principal, float interest_rate,
                                int term) {
  float r = interest_rate / 100 / 12;
  int n = term * 12;
  float payment = principal * r * pow(1 + r, n) / (pow(1 + r, n) - 1);
  return payment;
}

float calculate_differential_payment(float principal, float interest_rate,
                                     int term, int month) {
  float r = interest_rate / 100 / 12;
  int n = term * 12;
  float payment = principal / n + (principal - (month - 1) * principal / n) * r;
  return payment;
}

void calculate_credit(float principal, float interest_rate, int term,
                      const char* payment_type, float* payment,
                      float* overpayment, float* total_payment) {
  *total_payment = 0;
  *overpayment = 0;

  if (strcmp(payment_type, "annuity") == 0) {
    *payment = calculate_annuity_payment(principal, interest_rate, term);
    *total_payment = *payment * term * 12;
    *overpayment = *total_payment - principal;
  } else if (strcmp(payment_type, "differential") == 0) {
    for (int i = 1; i <= term * 12; i++) {
      *payment =
          calculate_differential_payment(principal, interest_rate, term, i);
      *total_payment += *payment;
    }
    *overpayment = *total_payment - principal;
  }
}
