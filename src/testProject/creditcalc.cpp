#include "creditcalc.h"
#include "ui_creditcalc.h"
#include <iostream>
extern "C" {
#include "calc.h"
}

CreditCalc::CreditCalc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditCalc) {
    ui->setupUi(this);
}

CreditCalc::~CreditCalc() {
    delete ui;
}

void CreditCalc::on_pushButton_clicked() {
    float credit_sum = ui->credit_sum->text().toFloat();
    int credit_duration = ui->credit_duration->text().toInt();
    float interest_rate = ui->interest_rate->text().toFloat();
    std::string type = " ";
    if (ui->annuity->isChecked()) {
        type = "annuity";
    } else if (ui->differential->isChecked()) {
        type = "differential";
    }

    const char* payment_type = type.c_str();
    float payment = 0.0, overpayment = 0.0, total_payment = 0.0;

    if (strcmp(payment_type, "annuity") == 0) {
        calculate_credit(credit_sum, interest_rate, credit_duration, payment_type, &payment, &overpayment, &total_payment);
        QString monthly_payment = QString::number(payment, 'f', 7);
        ui->monthly_payment->setText(monthly_payment);
    } else if (strcmp(payment_type, "differential") == 0) {
        float payment = calculate_differential_payment(credit_sum, interest_rate, credit_duration, 1);
        float payment_last_month = calculate_differential_payment(credit_sum, interest_rate, credit_duration, credit_duration * 12);
        QString monthly_payment_first = QString::number(payment, 'f', 7);
        QString monthly_payment_last = QString::number(payment_last_month, 'f', 7);
        ui->monthly_payment->setText(monthly_payment_first + "..." + monthly_payment_last);

        calculate_credit(credit_sum, interest_rate, credit_duration, payment_type, &payment, &overpayment, &total_payment);
    }

    QString overpayment_str = QString::number(overpayment, 'f', 7);
    ui->overpayment->setText(overpayment_str);

    QString total_payment_str = QString::number(total_payment, 'f', 7);
    ui->total_payment->setText(total_payment_str);
}

void CreditCalc::on_pushButton_2_clicked() {
    ui->credit_sum->clear();
    ui->credit_duration->clear();
    ui->interest_rate->clear();
    ui->monthly_payment->clear();
    ui->overpayment->clear();
    ui->total_payment->clear();
}

