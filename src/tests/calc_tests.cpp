#include "../model/calc_model.h"
#include "../model/deposit_model.h"
#include "../model/loan_model.h"
#include "gtest/gtest.h"

class CalculatorTest : public ::testing::Test {
 protected:
  s21::Calculator calc;
  s21::CreditCalculator creditCalc;
  s21::DepositCalculator depositCalc;

  static constexpr long double EPSILON = 1e-6;
  static constexpr long double EPSILON2 = 0.01;
};

// Тесты для стандартного калькулятора
TEST_F(CalculatorTest, SimpleExpressionTest1) {
  const std::string expression = "(3.5+2.2)*(8.4-6.1)+sqrt(25)";
  long double result = 0;
  EXPECT_EQ(calc.RPNcalculator(expression, &result), 0);
  EXPECT_NEAR(result, 18.110000, EPSILON);
}

TEST_F(CalculatorTest, SimpleExpressionTest2) {
  const std::string expression = "(4.8*(7.2-3.6))/2+cos(60)";
  long double result = 0;
  EXPECT_EQ(calc.RPNcalculator(expression, &result), 0);
  EXPECT_NEAR(result, 7.687587, EPSILON);
}

TEST_F(CalculatorTest, ReplaceXTest) {
  const std::string expression = "(3.5+x)+sqrt(x)";
  const std::string x_value = "4.5678";
  std::string new_string = calc.replaceX(expression, x_value);
  long double result = 0;
  EXPECT_EQ(calc.RPNcalculator(new_string, &result), 0);
  EXPECT_NEAR(result, 10.205041, EPSILON);
}

TEST_F(CalculatorTest, SimpleAddition) {
  long double result;
  EXPECT_EQ(calc.RPNcalculator("1+1", &result), 0);
  EXPECT_EQ(result, 2.0);
}

TEST_F(CalculatorTest, SimpleAddition2) {
  long double result;
  EXPECT_EQ(calc.RPNcalculator("-9+1", &result), 0);
  EXPECT_EQ(result, -8.0);
}

TEST_F(CalculatorTest, SimpleMod) {
  long double result;
  EXPECT_EQ(calc.RPNcalculator("mod(-2)", &result), 0);
  EXPECT_EQ(result, 2.0);
}

TEST_F(CalculatorTest, SimpleAtan) {
  long double result;
  EXPECT_EQ(calc.RPNcalculator("atan(1)", &result), 0);
  EXPECT_NEAR(result, 0.785398, EPSILON);
}

TEST_F(CalculatorTest, AdditionMultiplication) {
  long double result;
  EXPECT_EQ(calc.RPNcalculator("2+3*4", &result), 0);
  EXPECT_EQ(result, 14.0);
}

TEST_F(CalculatorTest, ParenthesesAndOperations) {
  long double result;
  EXPECT_EQ(calc.RPNcalculator("1+2*(3+4)", &result), 0);
  EXPECT_EQ(result, 15.0);
}

TEST_F(CalculatorTest, SinFunction) {
  long double result;
  EXPECT_EQ(calc.RPNcalculator("sin(1)", &result), 0);
  EXPECT_NEAR(result, 0.841471, EPSILON);
}

TEST_F(CalculatorTest, SqrtFunction) {
  long double result;
  EXPECT_EQ(calc.RPNcalculator("sqrt(9)", &result), 0);
  EXPECT_NEAR(result, 3.0, EPSILON);
}

TEST_F(CalculatorTest, LnFunction) {
  long double result;
  EXPECT_EQ(calc.RPNcalculator("ln(9)", &result), 0);
  EXPECT_NEAR(result, 2.197224, EPSILON);
}

TEST_F(CalculatorTest, InvalidExpressions) {
  long double result;

  EXPECT_EQ(calc.RPNcalculator("", &result), 1);

  EXPECT_EQ(calc.RPNcalculator("1++2", &result), 1);

  EXPECT_EQ(calc.RPNcalculator("(1+2", &result), 1);

  EXPECT_EQ(calc.RPNcalculator("sin(x+2", &result), 1);

  EXPECT_EQ(calc.RPNcalculator("cos(x+2", &result), 1);

  EXPECT_EQ(calc.RPNcalculator("tan(x+2", &result), 1);

  EXPECT_EQ(calc.RPNcalculator("mod(", &result), 1);
}

// Тесты для кредитного калькулятора
TEST_F(CalculatorTest, LoanCalculationTest1) {
  long double result = creditCalc.CalculateOverpaymentOnCredit(100000, 108333);
  EXPECT_NEAR(result, 8333.000000, EPSILON);
}

TEST_F(CalculatorTest, LoanCalculationTest2) {
  long double result =
      creditCalc.CalculateMonthlyDifferentiatedPayment(100000, 24);
  EXPECT_NEAR(result, 4166.666667, EPSILON);
}

TEST_F(CalculatorTest, LoanCalculationTest3) {
  long double result = creditCalc.CalculateMonthlyAnnuityPayment(100000, 24, 8);
  EXPECT_NEAR(result, 4522.729146, EPSILON);
}

TEST_F(CalculatorTest, LoanCalculationTest4) {
  long double result = creditCalc.CalculateTotalAnnuityPayment(4522, 24);
  EXPECT_NEAR(result, 108528, EPSILON);
}

TEST_F(CalculatorTest, LoanCalculationTest5) {
  long double result =
      creditCalc.CalculateTotalDifferentiatedPayment(100000, 24, 8);
  EXPECT_NEAR(result, 108333.333333, EPSILON);
}

// Тесты для депозитного калькулятора
TEST_F(CalculatorTest, DepositCalculationTest1) {
  s21::DepositCalculator::DepositInfo deposit = {10000.0, 12, 15.0, 1, 0, 0, 0};
  s21::DepositCalculator::DepositResult result =
      depositCalc.calculateDepositIncome(deposit);
  EXPECT_NEAR(result.totalAmount, 11479.45, EPSILON2);
  EXPECT_NEAR(result.totalInterest, 1479.45, EPSILON2);
  EXPECT_NEAR(result.tax, 0.0, EPSILON2);
}

TEST_F(CalculatorTest, DepositCalculationTest2) {
  s21::DepositCalculator::DepositInfo deposit = {10000.0, 24, 15.0, 1,
                                                 4,       4,  true, 100.0};
  s21::DepositCalculator::DepositResult result =
      depositCalc.calculateDepositIncome(deposit);
  EXPECT_NEAR(result.totalAmount, 13259.77, EPSILON2);
  EXPECT_NEAR(result.totalInterest, 2565.78, EPSILON2);
  EXPECT_NEAR(result.tax, 0.0, EPSILON2);
}

TEST_F(CalculatorTest, DepositCalculationTest3) {
  s21::DepositCalculator::DepositInfo deposit = {10000.0, 24, 15.0, 1,
                                                 3,       3,  true, 100.0};
  s21::DepositCalculator::DepositResult result =
      depositCalc.calculateDepositIncome(deposit);
  EXPECT_NEAR(result.totalAmount, 14703.19, EPSILON2);
  EXPECT_NEAR(result.totalInterest, 3676.04, EPSILON2);
  EXPECT_NEAR(result.tax, 0.0, EPSILON2);
}

TEST_F(CalculatorTest, DepositCalculationTest4) {
  s21::DepositCalculator::DepositInfo deposit = {10000.0, 2, 15.0, 1,
                                                 1,       1, true, 100.0};
  s21::DepositCalculator::DepositResult result =
      depositCalc.calculateDepositIncome(deposit);
  EXPECT_NEAR(result.totalAmount, 10318.44, EPSILON2);
  EXPECT_NEAR(result.totalInterest, 284.01, EPSILON2);
  EXPECT_NEAR(result.tax, 0.0, EPSILON2);
}

TEST_F(CalculatorTest, DepositCalculationTest5) {
  s21::DepositCalculator::DepositInfo deposit = {10000.0, 2, 15.0, 0,
                                                 5,       5, true, 100.0};
  s21::DepositCalculator::DepositResult result =
      depositCalc.calculateDepositIncome(deposit);
  EXPECT_NEAR(result.totalAmount, 10008.46, EPSILON2);
  EXPECT_NEAR(result.totalInterest, 8.29, EPSILON2);
  EXPECT_NEAR(result.tax, 0.0, EPSILON2);
}

TEST_F(CalculatorTest, DepositCalculationTest6) {
  s21::DepositCalculator::DepositInfo deposit = {10000.0, 2, 15.0, 0,
                                                 2,       2, true, 100.0};
  s21::DepositCalculator::DepositResult result =
      depositCalc.calculateDepositIncome(deposit);
  EXPECT_NEAR(result.totalAmount, 10009.28, EPSILON2);
  EXPECT_NEAR(result.totalInterest, 8.78, EPSILON2);
  EXPECT_NEAR(result.tax, 0.0, EPSILON2);
}

TEST_F(CalculatorTest, DepositCalculationTest7) {
  s21::DepositCalculator::DepositInfo deposit = {10000.0, 10, 15.0, 1,
                                                 6,       6,  true, 100.0};
  s21::DepositCalculator::DepositResult result =
      depositCalc.calculateDepositIncome(deposit);
  EXPECT_NEAR(result.totalAmount, 11306.61, EPSILON2);
  EXPECT_NEAR(result.totalInterest, 1293.80, EPSILON2);
  EXPECT_NEAR(result.tax, 0.0, EPSILON2);
}

TEST_F(CalculatorTest, DepositCalculationTest8) {
  s21::DepositCalculator::DepositInfo deposit = {10000.0, 30, 15.0, 1,
                                                 7,       5,  true, 100.0};
  s21::DepositCalculator::DepositResult result =
      depositCalc.calculateDepositIncome(deposit);
  EXPECT_NEAR(result.totalAmount, 14712.95, EPSILON2);
  EXPECT_NEAR(result.totalInterest, 4213.73, EPSILON2);
  EXPECT_NEAR(result.tax, 0.0, EPSILON2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
