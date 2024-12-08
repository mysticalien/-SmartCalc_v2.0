//
// Created by Mystic Alien on 7/29/24.
//

#ifndef CALC_TEST_LOAN_MODEL_H
#define CALC_TEST_LOAN_MODEL_H

#include <cmath>

namespace s21 {

class CreditCalculator {
 public:
  // Methods for credit calculations
  double ConvertYearsToMonths(double years) const;

  long double CalculateOverpaymentOnCredit(long double loan_amount,
                                           long double total_payment) const;

  long double CalculateMonthlyDifferentiatedPayment(
      long double total_payment, double loan_term_in_months) const;

  long double CalculateTotalAnnuityPayment(long double monthly_annuity_payment,
                                           double loan_term_in_months) const;

  long double CalculateMonthlyAnnuityPayment(
      long double principal, double periods,
      long double annual_interest_rate) const;

  long double CalculateTotalDifferentiatedPayment(
      long double loan_amount, double loan_term_in_months,
      long double annual_interest_rate) const;
};

}  // namespace s21

#endif  // CALC_TEST_LOAN_MODEL_H
