// calculator_controller.h
#ifndef MAINWINDOW_CONTROLLER_H
#define MAINWINDOW_CONTROLLER_H

#include "../model/calc_model.h"
#include "ui_mainwindow.h"

class CalculatorController {
 public:
  CalculatorController(s21::Calculator *model) : model_(model) {}
  bool isValidExpression(const std::string &expression) const {
    return model_->isValidExpression(expression);
  }
  std::string replaceX(const std::string &expression,
                       const std::string &x_value) const {
    return model_->replaceX(expression, x_value);
  }
  int RPNcalculator(const std::string &expression, long double *result) const {
    return model_->RPNcalculator(expression, result);
  }

 private:
  s21::Calculator *model_;
};

#endif  // MAINWINDOW_CONTROLLER_H
