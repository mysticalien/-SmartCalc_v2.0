#include "loancalc_view.h"

#include <QDoubleValidator>
#include <QIntValidator>
#include <QMessageBox>

#include "ui_loancalc.h"

LoanCalc::LoanCalc(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::LoanCalc),
      controller(new LoanCalcController(new s21::CreditCalculator)) {
  ui->setupUi(this);
  QIntValidator *intValidator = new QIntValidator(0, 100, this);
  ui->term->setValidator(intValidator);
  QDoubleValidator *doubleValidator = new QDoubleValidator(this);
  ui->totalAmount->setValidator(doubleValidator);
  ui->rate->setValidator(intValidator);
}

LoanCalc::~LoanCalc() {
  delete controller;
  delete ui;
}

void LoanCalc::on_totalAmount_editingFinished() {
  controller->setTotalAmount(ui->totalAmount->text().toDouble());
}

void LoanCalc::on_term_editingFinished() {
  controller->setTerm(ui->term->text().toDouble());
}

void LoanCalc::on_rate_editingFinished() {
  controller->setInterestRate(ui->rate->text().toDouble());
}

void LoanCalc::on_Annuity_clicked() {
  setText();
  if (validateInputs()) {
    long double monthlyPayment = controller->calculateMonthlyAnnuityPayment();
    ui->monthlyPayment->setText(QString::number(monthlyPayment, 'g', 7));
    long double totalPayment =
        controller->calculateTotalAnnuityPayment(monthlyPayment);
    ui->totalPayment->setText(QString::number(totalPayment, 'g', 7));
    long double overpayment =
        controller->calculateOverpaymentOnCredit(totalPayment);
    ui->Overpayment->setText(QString::number(overpayment, 'g', 7));
  } else {
    printError();
  }
}

void LoanCalc::on_Differentiated_clicked() {
  setText();
  if (validateInputs()) {
    long double monthlyPayment =
        controller->calculateMonthlyDifferentiatedPayment();
    ui->monthlyPayment->setText(QString::number(monthlyPayment, 'g', 7));
    long double totalPayment =
        controller->calculateTotalDifferentiatedPayment();
    ui->totalPayment->setText(QString::number(totalPayment, 'g', 7));
    long double overpayment =
        controller->calculateOverpaymentOnCredit(totalPayment);
    ui->Overpayment->setText(QString::number(overpayment, 'g', 7));
  } else {
    printError();
  }
}

bool LoanCalc::validateInputs() {
  if (!ui->totalAmount->text().isEmpty() && !ui->term->text().isEmpty() &&
      !ui->rate->text().isEmpty() &&
      (ui->months->isChecked() || ui->years->isChecked())) {
    controller->setInterestRate(ui->rate->text().toDouble());
    controller->setTerm(ui->term->text().toDouble());
    controller->setTotalAmount(ui->totalAmount->text().toDouble());
    if (controller->isYears()) {
      controller->setTerm(
          controller->convertYearsToMonths(controller->getTerm()));
    }
    return true;
  }
  return false;
}

void LoanCalc::printError() {
  ui->monthlyPayment->setText("Error: Not all fields filled");
  ui->totalPayment->setText("Error: Not all fields filled");
  ui->Overpayment->setText("Error: Not all fields filled");
}

void LoanCalc::setText() {
  ui->Overpayment->setText("00.00");
  ui->totalPayment->setText("00.00");
  ui->Overpayment->setText("00.00");
}

void LoanCalc::on_years_clicked() { controller->setIsYears(true); }

void LoanCalc::on_months_clicked() { controller->setIsYears(false); }
