#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "creditcalc.h"
#include <iostream>
extern "C" {
#include "calc.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_pushButton_dot_clicked() {
    if (!(ui->result_show->text().contains('.'))) {
        ui->result_show->setText(ui->result_show->text() + ".");
    }
}

void MainWindow::on_pushButton_equal_clicked() {
    double result = 0.0;
    std::string text = ui->result_show->text().toUtf8().constData();
    std::string x_value = ui->x_value->text().toUtf8().constData();

    const char *str = text.c_str();
    const char *str_x = x_value.c_str();
    char res_str[255] = {0};
    int code = start(str, str_x, &result);
    if (code == 0) {
        snprintf(res_str, 255, "%.7lf", result);
        ui->result_show->setText(res_str);
    } else {
        ui->result_show->setText("Invalid input");
    }
}

void MainWindow::on_graphButton_2_clicked() {
    std::string input = ui->result_show->text().toUtf8().constData();
    const char* str = input.c_str();

    double x_max = ui->x_max_box->text().toDouble(); //Конец интервала, где рисуем график по оси Ox
    double x_min = ui->x_min_box->text().toDouble(); // Начало интервала, где рисуем график по оси Ox
    double y_max = ui->y_max_box->text().toDouble();
    double y_min = ui->x_min_box->text().toDouble();

    double h = 0.1; //Шаг, с которым будем пробегать по оси Ox
    int N = (x_max - x_min) / h + 2; //Вычисляем количество точек, которые будем отрисовывать
    QVector<double> x(N), y(N); //Массивы координат точек

    double X;

    x.clear();
    y.clear();
    ui->customPlot->clearGraphs();
    ui->customPlot->replot();

    if (x_min > x_max || y_min > y_max) {
        ui->x_min_line->setText("Error");
    } else {
        for (X = x_min; X <= x_max + h; X += h) {
            double Y = 0.0;
            std::string x_value_str = std::to_string(X);
            const char* x_value_char_array = x_value_str.c_str();
            int val = start(str, x_value_char_array, &Y);
            if (val == 0) {
                x.push_back(X);
                y.push_back(Y);
            }
        }
    }

    ui->customPlot->clearGraphs();//Если нужно, но очищаем все графики

    //Добавляем один график в widget
    ui->customPlot->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->customPlot->graph(0)->addData(x, y);

    //Установим область, которая будет показываться на графике
    ui->customPlot->xAxis->setRange(x_min, x_max);
    ui->customPlot->yAxis->setRange(y_min, y_max);
    ui->customPlot->replot();
}

void MainWindow::on_allClear_clicked() {
    ui->result_show->clear();
    ui->x_value->clear();
    ui->customPlot->replot();
    ui->x_max_box->clear();
    ui->x_min_box->clear();
    ui->y_max_box->clear();
    ui->y_min_box->clear();
}


void MainWindow::on_pushButton_x_clicked() {
    ui->result_show->insert("x");
}


void MainWindow::on_pushButton_0_clicked() {
    ui->result_show->insert("0");
}


void MainWindow::on_pushButton_1_clicked() {
     ui->result_show->insert("1");
}


void MainWindow::on_pushButton_2_clicked() {
     ui->result_show->insert("2");
}


void MainWindow::on_pushButton_3_clicked() {
     ui->result_show->insert("3");
}


void MainWindow::on_pushButton_4_clicked() {
     ui->result_show->insert("4");
}


void MainWindow::on_pushButton_5_clicked() {
     ui->result_show->insert("5");
}


void MainWindow::on_pushButton_6_clicked() {
     ui->result_show->insert("6");
}


void MainWindow::on_pushButton_7_clicked() {
     ui->result_show->insert("7");
}


void MainWindow::on_pushButton_8_clicked() {
     ui->result_show->insert("8");
}


void MainWindow::on_pushButton_9_clicked() {
     ui->result_show->insert("9");
}


void MainWindow::on_pushButton_div_clicked() {
     ui->result_show->insert("/");
}


void MainWindow::on_pushButton_mult_clicked() {
     ui->result_show->insert("*");
}


void MainWindow::on_pushButton_minus_clicked() {
     ui->result_show->insert("-");
}


void MainWindow::on_pushButton_plus_clicked() {
     ui->result_show->insert("+");
}


void MainWindow::on_pushButton_ln_clicked() {
     ui->result_show->insert("ln(");
}


void MainWindow::on_pushButton_log_clicked() {
     ui->result_show->insert("log(");
}


void MainWindow::on_pushButton_sqrt_clicked() {
     ui->result_show->insert("sqrt(");
}


void MainWindow::on_pushButton_mod_clicked() {
     ui->result_show->insert("mod(");
}


void MainWindow::on_openBracket_clicked() {
     ui->result_show->insert("(");
}

void MainWindow::on_closeBracket_clicked() {
     ui->result_show->insert(")");
}

void MainWindow::on_pushButton_sin_clicked() {
     ui->result_show->insert("sin(");
}

void MainWindow::on_pushButton_cos_clicked() {
     ui->result_show->insert("cos(");
}

void MainWindow::on_pushButton_tan_clicked() {
     ui->result_show->insert("tan(");
}


void MainWindow::on_pushButton_asin_2_clicked() {
     ui->result_show->insert("asin(");
}


void MainWindow::on_pushButton_acos_clicked() {
     ui->result_show->insert("acos(");
}


void MainWindow::on_pushButton_atan_clicked() {
     ui->result_show->insert("atan(");
}

void MainWindow::on_creditCalc_clicked() {
//     this->hide();
     CreditCalc creditCalc;
     creditCalc.setModal(true);
     creditCalc.exec();
}


void MainWindow::on_pushButton_pow_clicked()
{
    ui->result_show->insert("^");
}

