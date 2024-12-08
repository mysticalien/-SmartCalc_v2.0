#include "depositcalc_controller.h"

namespace s21 {

DepositCalcController::DepositCalcController() {
  depositCalculator_ = new DepositCalculator();
}

DepositCalcController::~DepositCalcController() { delete depositCalculator_; }

s21::DepositCalculator::DepositResult DepositCalcController::calculateResult(
    double depositAmount, int depositTerm, double interestRate, int termUnit,
    int capitalization, int depositFrequency, double additionalDepositAmount) {
  DepositCalculator::DepositInfo deposit;
  deposit.depositAmount = depositAmount;
  deposit.depositTerm = depositTerm;
  deposit.interestRate = interestRate;
  deposit.termUnit = termUnit;
  deposit.capitalization = capitalization;
  deposit.depositFrequency = depositFrequency;
  deposit.additionalDeposits = (depositFrequency != 0);
  deposit.additionalDepositAmount = additionalDepositAmount;

  return depositCalculator_->calculateDepositIncome(deposit);
}

}  // namespace s21
