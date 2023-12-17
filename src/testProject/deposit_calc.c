#include "calc.h"

float calculate_tax(float amount, float tax_rate) {
  return amount * tax_rate / 100;
}

void calculate_deposit(float deposit_amount, int term, float interest_rate,
                       float tax_rate, int payout_period,
                       int interest_compounding, float *interest_earned,
                       float *tax_amount, float *final_amount) {
  *interest_earned = 0;
  *tax_amount = 0;
  *final_amount = deposit_amount;

  float monthly_interest_rate = interest_rate / 100 / 12;
  int num_of_payouts = term * 12 / payout_period;

  for (int i = 1; i <= num_of_payouts; i++) {
    // Добавляем пополнение (если есть)
    float deposit = 0;
    printf("Введите сумму пополнения за период %d: ", i);
    scanf("%f", &deposit);
    *final_amount += deposit;

    // Вычисляем начисленные проценты
    float interest = *final_amount * monthly_interest_rate;
    *interest_earned += interest;

    // Вычитаем налог на начисленные проценты (если есть)
    float tax = calculate_tax(interest, tax_rate);
    *tax_amount += tax;
    *final_amount += interest - tax;

    // Проверяем, нужна ли капитализация процентов
    if (interest_compounding) {
      *final_amount += interest - tax;
    }

    // Обработка частичного снятия (если есть)
    float withdrawal = 0;
    printf("Введите сумму частичного снятия за период %d: ", i);
    scanf("%f", &withdrawal);
    *final_amount -= withdrawal;
  }
}

int deposit_calc() {
  float deposit_amount;  // Сумма вклада
  int term;              // Срок размещения (в годах)
  float interest_rate;   // Процентная ставка
  float tax_rate;        // Налоговая ставка
  int payout_period;  // Периодичность выплат процентов (в месяцах)
  int interest_compounding;  // Капитализация процентов (1 - да, 0 - нет)

  printf("Введите сумму вклада: ");
  scanf("%f", &deposit_amount);

  printf("Введите срок размещения (в годах): ");
  scanf("%d", &term);

  printf("Введите процентную ставку: ");
  scanf("%f", &interest_rate);

  printf("Введите налоговую ставку: ");
  scanf("%f", &tax_rate);

  printf("Введите периодичность выплат процентов (в месяцах): ");
  scanf("%d", &payout_period);

  printf("Введите капитализацию процентов (1 - да, 0 - нет): ");
  scanf("%d", &interest_compounding);

  float interest_earned, tax_amount, final_amount;
  calculate_deposit(deposit_amount, term, interest_rate, tax_rate,
                    payout_period, interest_compounding, &interest_earned,
                    &tax_amount, &final_amount);

  printf("\nРезультаты:\n");
  printf("Начисленные проценты: %.2f\n", interest_earned);
  printf("Сумма налога: %.2f\n", tax_amount);
  printf("Сумма на вкладе к концу срока: %.2f\n", final_amount);

  return 0;
}
