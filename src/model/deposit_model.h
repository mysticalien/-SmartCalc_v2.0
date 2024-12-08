#ifndef DEPOSIT_MODEL_H
#define DEPOSIT_MODEL_H

#include <cmath>
#include <iostream>

namespace s21 {

class DepositCalculator {
 public:
  struct DepositInfo {
    double depositAmount;
    int depositTerm;
    double interestRate;
    int termUnit;  // 0 for days, 1 for months
    int capitalization;
    int depositFrequency;  // 0 for none, 1 for monthly, 2 for once in 2 months,
                           // etc.
    bool additionalDeposits;  // true for additional deposits, false otherwise
    double additionalDepositAmount;
  };

  struct DepositResult {
    double totalAmount;
    double totalInterest;
    double tax;
  };

  static DepositResult calculateDepositIncome(const DepositInfo& deposit);

 private:
  static double calculateInterest(double depositAmount, double interestRate,
                                  int termInDays, int capitalization);
  static double calculateTax(double interestAmount, double untaxableIncome);
  static int calculateFrequency(int depositFrequency);
};

}  // namespace s21

#endif  // DEPOSIT_MODEL_H
