#ifndef DEPOSITCALC_CONTROLLER_H
#define DEPOSITCALC_CONTROLLER_H

#include "../model/deposit_model.h"

namespace s21 {

class DepositCalcController {
 public:
  explicit DepositCalcController();
  ~DepositCalcController();

  s21::DepositCalculator::DepositResult calculateResult(
      double depositAmount, int depositTerm, double interestRate, int termUnit,
      int capitalization, int depositFrequency, double additionalDepositAmount);

 private:
  s21::DepositCalculator* depositCalculator_;
};

}  // namespace s21

#endif  // DEPOSITCALC_CONTROLLER_H
