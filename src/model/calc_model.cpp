#include "calc_model.h"

namespace s21 {
// private functions
void Calculator::generateTokens(const std::string& expression,
                                std::string& tokens) {
  bool lastWasOperand = false;
  tokens.clear();
  const char* ptr = expression.c_str();

  while (*ptr != '\0') {
    char current = *ptr;
    std::string token;

    if (std::isdigit(current) || current == '.') {
      parseNumber(ptr, token);
      tokens += token + " ";
      lastWasOperand = true;
    } else if (current == 'x' || current == '+' || current == '-' ||
               current == '*' || current == '/' || current == '^' ||
               current == '(' || current == ')') {
      processOperator(ptr, tokens, lastWasOperand);
    } else if (std::isalpha(current)) {
      readAlphaToken(ptr, token);
      tokens += token + " ";
    } else {
      ++ptr;
    }
  }
  tokens += "w ";
}

bool Calculator::isValidExpression(const std::string& expression) {
  int balance = 0;
  bool isValid = true;
  bool lastWasOperand = false;
  bool flag_x = true;
  char prevChar = '(';
  int flag = 0;

  for (size_t i = 0; i < expression.size() && isValid; i++) {
    char currentChar = expression[i];
    if (currentChar == '(') {
      balance++;
      lastWasOperand = false;
      flag = 0;
      flag_x = true;
    } else if (currentChar == ')') {
      balance--;
      if (balance < 0 || !lastWasOperand) {
        isValid = false;
      }
      lastWasOperand = true;
      flag = 0;
      flag_x = false;
    } else if (currentChar == 'x' && lastWasOperand) {
      isValid = false;
    } else if (currentChar == 'x' && flag_x) {
      lastWasOperand = true;
      flag_x = false;
    } else if (std::isalpha(currentChar)) {
      isValid =
          processFunction(expression, i, balance, lastWasOperand, isValid);
      flag = 0;
      flag_x = true;
    } else if ((std::isdigit(currentChar) && prevChar != 'x') ||
               (std::isdigit(prevChar) && currentChar == '.' && flag == 0)) {
      lastWasOperand = true;
      if (currentChar == '.') {
        flag = 1;
      }
      flag_x = false;
    } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' ||
               currentChar == '/' || currentChar == '^') {
      checkOperatorValidity(currentChar, prevChar, lastWasOperand, isValid);
      lastWasOperand = false;
      flag = 0;
      flag_x = true;
    } else if (std::isspace(currentChar)) {
      isValid = false;
    }

    prevChar = currentChar;
  }

  return balance == 0 && lastWasOperand && isValid;
}

void Calculator::parseNumber(const char*& ptr, std::string& token) {
  while (std::isdigit(*ptr) || *ptr == '.') {
    token.push_back(*ptr);
    ++ptr;
  }
}

void Calculator::processOperator(const char*& ptr, std::string& tokens,
                                 bool& lastWasOperand) {
  char current = *ptr;
  std::string token;

  if ((current == '+' || current == '-') && !lastWasOperand) {
    token = (current == '+') ? "p" : "u";
    tokens += token + " ";
    ++ptr;
  } else {
    token.push_back(current);
    tokens += token + " ";
    ++ptr;
  }

  lastWasOperand = (current == 'x' || current == ')');
}

void Calculator::readAlphaToken(const char*& ptr, std::string& token) {
  while (std::isalpha(*ptr)) {
    token.push_back(*ptr);
    ++ptr;
  }
  ++ptr;
}

int Calculator::checkPriority(const std::string& token) {
  if (token == "(")
    return 0;
  else if (token == "+" || token == "-")
    return 1;
  else if (token == "*" || token == "/")
    return 2;
  else if (token == "^")
    return 3;
  else if (token == "u" || token == "p")
    return 4;
  else if (strchr("mcstal", token[0]))
    return 0;
  return -1;
}

void Calculator::handleClosingParenthesis(std::string& temp,
                                          std::stack<std::string>& operators,
                                          int& is_fun) {
  bool is_end = false;
  bool pair = false;

  while (!is_end && !pair) {
    if (!operators.empty()) {
      std::string top = operators.top();
      if (top == "sin" || top == "cos" || top == "tan" || top == "asin" ||
          top == "acos" || top == "atan" || top == "sqrt" || top == "log" ||
          top == "mod") {
        is_fun--;
        temp += top + " ";
        operators.pop();
        pair = true;
      } else if (top == "(") {
        operators.pop();
        is_fun--;
        pair = true;
      } else {
        temp += top + " ";
        operators.pop();
      }
    } else {
      is_end = true;
    }
  }
}

void Calculator::handleOperator(const std::string& token, std::string& temp,
                                std::stack<std::string>& operators) {
  while (!operators.empty()) {
    std::string prevOperator = operators.top();
    if (checkPriority(token) > checkPriority(prevOperator) ||
        (checkPriority(token) == checkPriority(prevOperator) &&
         checkPriority(token) == 3)) {
      break;
    } else {
      temp += operators.top() + " ";
      operators.pop();
    }
  }
  operators.push(token);
}

void Calculator::RPN(std::string& tokens, std::string& temp) {
  std::stack<std::string> operators;
  temp.clear();
  std::istringstream iss(tokens);
  std::string token;
  int is_fun = 0;

  while (iss >> token) {
    if (token == "w") {
      break;
    } else if (strchr("0123456789.x", token[0])) {
      temp += token + " ";
    } else if (strchr("*/+-^", token[0])) {
      handleOperator(token, temp, operators);
    } else if (strchr("mcstalup(", token[0])) {
      operators.push(token);
      is_fun++;
    } else if (token == ")") {
      handleClosingParenthesis(temp, operators, is_fun);
    }
  }

  while (!operators.empty()) {
    temp += operators.top() + " ";
    operators.pop();
  }

  temp += "w ";
}

int Calculator::processOperation(std::stack<long double>& stack,
                                 long double& result, char sign) {
  if (stack.size() < 2) {
    return 0;
  }

  long double value1 = stack.top();
  stack.pop();
  long double value2 = stack.top();
  stack.pop();

  switch (sign) {
    case '+':
      result = value2 + value1;
      break;
    case '-':
      result = value2 - value1;
      break;
    case '*':
      result = value2 * value1;
      break;
    case '/':
      result = value2 / value1;
      break;
    case '^':
      result = powl(value2, value1);
      break;
    default:
      return 0;
  }

  return std::isnan(result) == 0 ? 1 : 0;
}

int Calculator::processFunctions(std::stack<long double>& stack,
                                 long double& result, const std::string& func) {
  if (stack.empty()) {
    return 0;
  }

  long double value = stack.top();
  stack.pop();

  if (func == "mod") {
    result = fabsl(value);
  } else if (func == "acos") {
    result = acosl(value);
  } else if (func == "asin") {
    result = asinl(value);
  } else if (func == "atan") {
    result = atanl(value);
  } else if (func == "cos") {
    result = cosl(value);
  } else if (func == "sin") {
    result = sinl(value);
  } else if (func == "tan") {
    result = tanl(value);
  } else if (func == "sqrt") {
    result = sqrtl(value);
  } else if (func == "ln") {
    result = logl(value);
  } else if (func == "log") {
    result = log10l(value);
  } else {
    return 0;
  }

  return std::isnan(result) == 0 ? 1 : 0;
}

int Calculator::processToken(const std::string& token,
                             std::stack<long double>& stack,
                             long double& result) {
  int flag = 1;
  if (token.empty()) {
    return 0;
  }

  if (std::isdigit(token[0]) || token[0] == '.') {
    long double value = std::stold(token);
    stack.push(value);
  } else if (strchr("*/+-^", token[0])) {
    flag = processOperation(stack, result, token[0]);
    if (flag == 1) {
      stack.push(result);
    }
  } else if (token[0] == 'u' || token[0] == 'p') {
    int sign = (token[0] == 'u') ? -1 : 1;
    if (stack.empty()) {
      return 0;
    }
    long double value = stack.top();
    stack.pop();
    stack.push(sign * value);
  } else {
    flag = processFunctions(stack, result, token);
    if (flag == 1) {
      stack.push(result);
    }
  }

  return flag;
}

bool Calculator::processFunction(const std::string& expression, size_t& i,
                                 int& balance, bool& lastWasOperand,
                                 bool& isValid) {
  std::string functionName;
  size_t j = 0;

  if (lastWasOperand) {
    isValid = false;
  }

  bool bracket_found = false;

  while ((std::isalpha(expression[i]) && j < 15) || (expression[i] == '(')) {
    functionName += expression[i++];
    if (expression[i] == '(') {
      bracket_found = true;
      functionName += expression[i++];
    }
    if (bracket_found) {
      break;
    }
  }

  if (functionName == "sin(" || functionName == "cos(" ||
      functionName == "mod(" || functionName == "ln(" ||
      functionName == "tan(" || functionName == "log(" ||
      functionName == "acos(" || functionName == "asin(" ||
      functionName == "atan(" || functionName == "sqrt(") {
    lastWasOperand = false;
    balance++;
  } else {
    isValid = false;
  }

  i--;

  return isValid;
}

void Calculator::checkOperatorValidity(char currentChar, char prevChar,
                                       bool lastWasOperand, bool& isValid) {
  if (prevChar == '+' || prevChar == '-' || prevChar == '*' ||
      prevChar == '/' || prevChar == '^') {
    isValid = false;
  }
  if (!lastWasOperand && currentChar != '-' && currentChar != '+') {
    isValid = false;
  }
}

int Calculator::countOccurrences(const std::string& expression, char x) {
  int count = 0;
  for (char ch : expression) {
    if (ch == x) {
      ++count;
    }
  }
  return count;
}

int Calculator::calculate(const std::string& expression, long double* result) {
  std::string temp = expression;
  int flag = 1;

  std::stack<long double> stack;

  char* token = std::strtok(&temp[0], " ");
  while (token != NULL && flag == 1 && strcmp(token, "w") != 0) {
    if (!processToken(token, stack, *result)) {
      flag = 0;
    }
    if (flag == 1) {
      token = std::strtok(NULL, " ");
    }
  }

  if (!stack.empty()) {
    *result = stack.top();
    stack.pop();
  } else {
    flag = 0;
  }

  return flag;
}

// public functions
std::string Calculator::replaceX(const std::string& expression,
                                 const std::string& value_of_x) {
  int count = countOccurrences(expression, 'x');
  size_t value_len = value_of_x.length();
  size_t new_length = expression.length() - count + (count * (value_len + 2));

  std::string result;
  result.reserve(new_length);

  for (char ch : expression) {
    if (ch == 'x') {
      result += '(';
      result += value_of_x;
      result += ')';
    } else {
      result += ch;
    }
  }

  return result;
}

int Calculator::RPNcalculator(const std::string& expression,
                              long double* result) {
  if (expression.empty()) {
    return 1;
  }

  bool has_error = false;

  if (isValidExpression(expression)) {
    std::string tokens;
    tokens.reserve(MAX_LEN * 2);
    generateTokens(expression, tokens);

    std::string temp(MAX_LEN * 2, '\0');
    RPN(tokens, temp);
    has_error = !calculate(temp, result);

  } else {
    has_error = true;
  }

  return has_error;
}
}  // namespace s21

// int main() {
//	s21::Calculator calculator;
//	std::string expression = "3.1466666666+(-2*5)-sqrt(9.0)+mod(3)";
//	long double result;
//	if (calculator.RPNcalculator(expression, &result) == 0) {
//		std::cout << "Result: " << result << std::endl;
//	} else {
//		std::cout << "Invalid expression" << std::endl;
//	}
//	return 0;
// }
