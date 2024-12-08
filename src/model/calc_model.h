#ifndef S21_CALC_MODEL_H_
#define S21_CALC_MODEL_H_

#include <cmath>
#include <iostream>
#include <sstream>
#include <stack>

namespace s21 {

constexpr int MAX_LEN = 256;  // Максимальная длина выражения

class Calculator {
 public:
  // Функция для замены x на значение
  std::string replaceX(const std::string &expression,
                       const std::string &value_of_x);

  // Основная функция для вычисления результата выражения
  int RPNcalculator(const std::string &expression, long double *result);

  // Функция для проверки валидности выражения
  bool isValidExpression(const std::string &expression);

 private:
  // Функция, создающая строку токенов из выражения
  void generateTokens(const std::string &expression, std::string &tokens);

  // Функция для парсинга числа из строки
  void parseNumber(const char *&ptr, std::string &token);

  // Функция для обработки операторов в выражении
  void processOperator(const char *&ptr, std::string &tokens,
                       bool &lastWasOperand);

  // Функция для чтения алфавитного токена из строки
  void readAlphaToken(const char *&ptr, std::string &token);

  // Функция для определения приоритета оператора
  int checkPriority(const std::string &
                        token);  // функция для опеределения приоритета операции

  // Функция для обработки закрывающей скобки
  void handleClosingParenthesis(std::string &temp,
                                std::stack<std::string> &operators,
                                int &is_fun);

  // Функция для обработки оператора
  void handleOperator(const std::string &token, std::string &temp,
                      std::stack<std::string> &operators);

  // Функция, реализующая преобразование выражения в обратную польскую нотацию
  // (RPN)
  void RPN(
      std::string &tokens,
      std::string &temp);  // функция, реалищующая обратную польскую нотацию

  // Функция для выполнения арифметических операций
  int processOperation(std::stack<long double> &stack, long double &result,
                       char sign);

  // Функция для выполнения математических функций (например, sqrt, sin)
  int processFunctions(std::stack<long double> &stack, long double &result,
                       const std::string &func);

  // Функция для обработки токена в выражении
  int processToken(const std::string &token, std::stack<long double> &stack,
                   long double &result);

  // Функция для обработки математической функции в выражении
  bool processFunction(const std::string &expression, size_t &i, int &balance,
                       bool &lastWasOperand, bool &isValid);

  // Функция для проверки валидности оператора
  void checkOperatorValidity(char currentChar, char prevChar,
                             bool lastWasOperand, bool &isValid);

  // Функция для подсчета количества вхождений символа в строке
  int countOccurrences(const std::string &expression,
                       char x);  // функция для подсчета количества повторений

  // Вспомогательная функция для вычисления результата выражения
  int calculate(const std::string &expression, long double *result);
};

}  // namespace s21

#endif  // S21_CALC_MODEL_H_
