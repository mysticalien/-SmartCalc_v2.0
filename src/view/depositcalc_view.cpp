#include "depositcalc_view.h"

#include "ui_depositcalc.h"

DepositCalc::DepositCalc(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::DepositCalc),
      controller_(new s21::DepositCalcController()) {
  ui->setupUi(this);

  QIntValidator *intValidator = new QIntValidator(0, 100, this);
  ui->lineEdit_deposit_term->setValidator(intValidator);

  QDoubleValidator *doubleValidator = new QDoubleValidator(this);
  ui->lineEdit_deposit_amount->setValidator(doubleValidator);
  ui->lineEdit_rate->setValidator(doubleValidator);
  ui->lineEdit_sum->setValidator(doubleValidator);
}

DepositCalc::~DepositCalc() {
  delete controller_;
  delete ui;
}

void DepositCalc::on_lineEdit_deposit_amount_editingFinished() {
  depositAmount = ui->lineEdit_deposit_amount->text().toDouble();
}

void DepositCalc::on_lineEdit_deposit_term_editingFinished() {
  depositTerm =
      ui->lineEdit_deposit_term->text().toInt();  // Исправлено на toInt()
}

void DepositCalc::on_lineEdit_rate_editingFinished() {
  interestRate = ui->lineEdit_rate->text().toDouble();
}

void DepositCalc::on_comboBox_term_currentIndexChanged(int index) {
  termUnit = index;
}

void DepositCalc::on_comboBox_currency_currentIndexChanged(int index) {
  currency = index;
}

void DepositCalc::on_lineEdit_sum_editingFinished() {
  additionalDepositAmount = ui->lineEdit_sum->text().toDouble();
}

void DepositCalc::on_comboBox_replenishment_currentIndexChanged(int index) {
  depositFrequency = index;
}

void DepositCalc::on_comboBox_capitalization_currentIndexChanged(int index) {
  capitalization = index;
}

void DepositCalc::on_pushButton_result_clicked() {
  ui->label_interest2->setText("0.00");
  ui->label_taxAmount2->setText("0.00");
  ui->label_total2->setText("0.00");

  if (!ui->lineEdit_deposit_amount->text().isEmpty() &&
      !ui->lineEdit_deposit_term->text().isEmpty() &&
      !ui->lineEdit_rate->text().isEmpty() &&
      ui->comboBox_term->currentIndex() != -1 &&
      ui->comboBox_currency->currentIndex() != -1 &&
      ui->comboBox_replenishment->currentIndex() != -1 &&
      ui->comboBox_capitalization->currentIndex() != -1) {
    s21::DepositCalculator::DepositResult result = controller_->calculateResult(
        depositAmount, depositTerm, interestRate, termUnit, capitalization,
        depositFrequency, additionalDepositAmount);

    ui->label_interest2->setText(QString::number(result.totalInterest, 'f', 2));
    ui->label_taxAmount2->setText(QString::number(result.tax, 'f', 2));
    ui->label_total2->setText(QString::number(result.totalAmount, 'f', 2));
  } else {
    ui->label_interest2->setText("Error: Not all fields filled");
    ui->label_taxAmount2->setText("Error: Not all fields filled");
    ui->label_total2->setText("Error: Not all fields filled");
  }
}
