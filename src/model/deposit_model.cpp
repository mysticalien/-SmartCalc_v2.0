#include "deposit_model.h"

namespace s21 {

DepositCalculator::DepositResult DepositCalculator::calculateDepositIncome(
    const DepositInfo& deposit) {
  DepositResult result = {0.0, 0.0, 0.0};

  double totalAmount = deposit.depositAmount;
  double totalInterest = 0.0;

  const double keyRate = 0.16;
  int termInDays =
      (deposit.termUnit == 0) ? deposit.depositTerm : deposit.depositTerm * 30;

  totalInterest = calculateInterest(totalAmount, deposit.interestRate,
                                    termInDays, deposit.capitalization);

  if (deposit.additionalDeposits) {
    int frequency = calculateFrequency(deposit.depositFrequency);
    if (frequency <= 0 || termInDays * frequency < termInDays) {
      throw std::invalid_argument("Invalid deposit frequency or term.");
    }

    totalAmount +=
        ((termInDays / 360) * frequency) * deposit.additionalDepositAmount;
    double additionalDepositInterest =
        calculateInterest(deposit.additionalDepositAmount, deposit.interestRate,
                          termInDays * frequency, deposit.capitalization);

    totalAmount += additionalDepositInterest;
    totalInterest += additionalDepositInterest;
  }

  double untaxableIncome = 1000000.0 * keyRate;
  double tax = calculateTax(totalInterest, untaxableIncome);
  double netInterest = totalInterest - tax;
  totalAmount += netInterest;

  result.totalAmount = totalAmount;
  result.totalInterest = totalInterest;
  result.tax = tax;

  return result;
}

double DepositCalculator::calculateInterest(double depositAmount,
                                            double interestRate, int termInDays,
                                            int capitalization) {
  double ratePerPeriod = interestRate / 100.0;
  switch (capitalization) {
    case 0:
      return depositAmount * ratePerPeriod * termInDays / 365.0;
    case 1:
      return depositAmount *
             (std::pow(1 + ratePerPeriod / 365, termInDays) - 1);
    case 2:
      return depositAmount *
             (std::pow(1 + ratePerPeriod / 12, termInDays / 30.0) - 1);
    case 3:
      return depositAmount *
             (std::pow(1 + ratePerPeriod / 6, termInDays / 60.0) - 1);
    case 4:
      return depositAmount *
             (std::pow(1 + ratePerPeriod / 4, termInDays / 120.0) - 1);
    case 5:
      return depositAmount *
             (std::pow(1 + ratePerPeriod / 3, termInDays / 120.0) - 1);
    case 6:
      return depositAmount *
             (std::pow(1 + ratePerPeriod / 2, termInDays / 180.0) - 1);
    case 7:
      return depositAmount *
             (std::pow(1 + ratePerPeriod, termInDays / 365.0) - 1);
    default:
      throw std::invalid_argument("Invalid capitalization type.");
  }
}

double DepositCalculator::calculateTax(double interestAmount,
                                       double untaxableIncome) {
  double taxableIncome = interestAmount - untaxableIncome;
  return taxableIncome > 0 ? taxableIncome * 0.13 : 0.0;
}

int DepositCalculator::calculateFrequency(int depositFrequency) {
  switch (depositFrequency) {
    case 1:
      return 12;
    case 2:
      return 6;
    case 3:
      return 4;
    case 4:
      return 3;
    case 5:
      return 2;
    case 6:
      return 1;
    default:
      return 0;
  }
}

}  // namespace s21

// int main() {
//	s21::DepositCalculator::DepositInfo deposit = {
//			10000.0,  // depositAmount
//			12,       // depositTerm in months
//			5.0,      // interestRate in percent
//			1,        // termUnit: 0 for days, 1 for months
//			2,        // capitalization: 0 - none, 1 - daily, 2 -
// monthly, etc. 			1,        // depositFrequency: 0 - none,
// 1 - monthly, etc. 			true,
//// additionalDeposits: true if additional deposits are made
/// 500.0     //
// additionalDepositAmount
//	};
//
//	try {
//		s21::DepositCalculator::DepositResult result =
// s21::DepositCalculator::calculateDepositIncome(deposit);
// std::cout << "Total interest earned: " << result.totalInterest << std::endl;
// std::cout << "Tax amount: " << result.tax << std::endl;
// std::cout << "Total amount at the end of the term: " << result.totalAmount <<
// std::endl; 	} catch (const std::exception& e) { 		std::cerr <<
// "Error: " << e.what() << std::endl;
//	}
//
//	return 0;
//  }
