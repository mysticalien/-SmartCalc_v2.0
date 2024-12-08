#ifndef LOANCALC_VIEW_H
#define LOANCALC_VIEW_H

#include <QDialog>
#include <QMessageBox>

#include "../controller/loancalc_controller.h"
#include "../model/loan_model.h"

namespace Ui {
class LoanCalc;
}

class LoanCalc : public QDialog {
  Q_OBJECT

 public:
  explicit LoanCalc(QWidget *parent = nullptr);
  ~LoanCalc();

 private slots:
  void on_totalAmount_editingFinished();
  void on_term_editingFinished();
  void on_Annuity_clicked();
  void on_Differentiated_clicked();
  void on_rate_editingFinished();
  void on_years_clicked();
  void on_months_clicked();

 private:
  bool validateInputs();
  void printError();
  void setText();
  Ui::LoanCalc *ui;
  LoanCalcController *controller;
};

#endif  // LOANCALC_VIEW_H
