#include "loan_model.h"

#include <iostream>

namespace s21 {

double CreditCalculator::ConvertYearsToMonths(double years) const {
  return years * 12;
}

long double CreditCalculator::CalculateOverpaymentOnCredit(
    long double loan_amount, long double total_payment) const {
  return total_payment - loan_amount;
}

long double CreditCalculator::CalculateMonthlyDifferentiatedPayment(
    long double total_payment, double loan_term_in_months) const {
  return total_payment / loan_term_in_months;
}

long double CreditCalculator::CalculateTotalAnnuityPayment(
    long double monthly_annuity_payment, double loan_term_in_months) const {
  return monthly_annuity_payment * loan_term_in_months;
}

long double CreditCalculator::CalculateMonthlyAnnuityPayment(
    long double principal, double periods,
    long double annual_interest_rate) const {
  long double interest =
      annual_interest_rate /
      (12 * 100);  // Convert annual interest rate to monthly decimal
  long double annuity_payment = interest * std::powl(1 + interest, periods) /
                                (std::powl(1 + interest, periods) - 1);
  return annuity_payment * principal;
}

long double CreditCalculator::CalculateTotalDifferentiatedPayment(
    long double loan_amount, double loan_term_in_months,
    long double annual_interest_rate) const {
  long double total_payment = 0;
  long double interest =
      annual_interest_rate /
      (12 * 100);  // Convert annual interest rate to monthly decimal
  int periods = static_cast<int>(loan_term_in_months);

  for (int month = 1; month <= periods; ++month) {
    long double differentiated_payment =
        loan_amount / periods +
        interest * (loan_amount - (loan_amount * (month - 1)) / periods);
    total_payment += differentiated_payment;
  }

  return total_payment;
}

}  // namespace s21
//
// int main() {
//	s21::CreditCalculator calculator;
//
//	long double principal = 10000.0;
//	double periods = 24.0;
//	long double annual_interest_rate = 8.0;
//
//	long double annuity_payment =
// calculator.CalculateMonthlyAnnuityPayment(principal, periods,
// annual_interest_rate); 	long double total_differentiated_payment =
// calculator.CalculateTotalDifferentiatedPayment(principal, periods,
// annual_interest_rate);
//
//	std::cout << "Monthly Annuity Payment: " << annuity_payment <<
// std::endl; 	std::cout << "Total Differentiated Payment: " <<
// total_differentiated_payment << std::endl;
//
//	return 0;
//}
