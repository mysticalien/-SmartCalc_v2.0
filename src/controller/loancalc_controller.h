// loancalc_controller.h
#ifndef LOANCALC_CONTROLLER_H
#define LOANCALC_CONTROLLER_H

#include "../model/loan_model.h"

class LoanCalcController {
 public:
  explicit LoanCalcController(s21::CreditCalculator* model)
      : loanCalculator_(model),
        totalAmount_(0),
        term_(0),
        interestRate_(0),
        isYears_(false) {}

  ~LoanCalcController() { delete loanCalculator_; }

  void setTotalAmount(long double amount) { totalAmount_ = amount; }

  void setTerm(double term) { term_ = term; }

  void setInterestRate(long double rate) { interestRate_ = rate; }

  void setIsYears(bool isYears) { isYears_ = isYears; }

  long double getTotalAmount() const { return totalAmount_; }

  double getTerm() const { return term_; }

  long double getInterestRate() const { return interestRate_; }

  bool isYears() const { return isYears_; }

  long double calculateMonthlyAnnuityPayment() const {
    return loanCalculator_->CalculateMonthlyAnnuityPayment(totalAmount_, term_,
                                                           interestRate_);
  }

  long double calculateTotalAnnuityPayment(long double monthlyPayment) const {
    return loanCalculator_->CalculateTotalAnnuityPayment(monthlyPayment, term_);
  }

  long double calculateOverpaymentOnCredit(long double totalPayment) const {
    return loanCalculator_->CalculateOverpaymentOnCredit(totalAmount_,
                                                         totalPayment);
  }

  long double calculateMonthlyDifferentiatedPayment() const {
    return loanCalculator_->CalculateMonthlyDifferentiatedPayment(totalAmount_,
                                                                  term_);
  }

  long double calculateTotalDifferentiatedPayment() const {
    return loanCalculator_->CalculateTotalDifferentiatedPayment(
        totalAmount_, term_, interestRate_);
  }

  double convertYearsToMonths(double years) const {
    return loanCalculator_->ConvertYearsToMonths(years);
  }

 private:
  s21::CreditCalculator* loanCalculator_;
  long double totalAmount_;
  double term_;
  long double interestRate_;
  bool isYears_;
};

#endif  // LOANCALC_CONTROLLER_H
