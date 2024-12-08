#ifndef DEPOSITCALC_H
#define DEPOSITCALC_H

#include <QDialog>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QMessageBox>

#include "../controller/depositcalc_controller.h"

namespace Ui {
class DepositCalc;
}

class DepositCalc : public QDialog {
  Q_OBJECT

 public:
  explicit DepositCalc(QWidget *parent = nullptr);
  ~DepositCalc();

 private slots:
  void on_lineEdit_deposit_amount_editingFinished();
  void on_lineEdit_deposit_term_editingFinished();
  void on_lineEdit_rate_editingFinished();
  void on_comboBox_term_currentIndexChanged(int index);
  void on_comboBox_currency_currentIndexChanged(int index);
  void on_lineEdit_sum_editingFinished();
  void on_comboBox_replenishment_currentIndexChanged(int index);
  void on_pushButton_result_clicked();
  void on_comboBox_capitalization_currentIndexChanged(int index);

 private:
  Ui::DepositCalc *ui;
  s21::DepositCalcController *controller_;
  double depositAmount;
  int depositTerm;
  double interestRate;
  int termUnit;  // 0 for days, 1 for months
  int capitalization;
  int depositFrequency;  // 0 for none, 1 for monthly, 2 for once in 2 months,
                         // etc.
  double additionalDepositAmount;
  int currency;
};

#endif  // DEPOSITCALC_H
