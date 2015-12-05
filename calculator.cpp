#include "Calculator.h"

#include <cctype>
#include <stack>
#include <cmath>
#include <vector>

using std::string;

Calculator::Calculator(const string& line):
	value_(0)
{
	for (int i = 0; i < line.length(); ++i)
		if (line[i] != ' ')
			infix_ += line[i];
}
Calculator::~Calculator()
{
}

string Calculator::postfix() const
{
	return postfix_;
}

double Calculator::value() const
{
	return value_;
}

// Check if it`s an operation symbol
bool Calculator::isOperator(const char & c)
{
	switch (c) 
	{
	case'+':
	case'-':
	case'*':
	case'/':
	case'^':
		return true;
	default:
		return false;
	}
}

// Compares the priorities of operations
bool Calculator::precedence(const char & left_operator, const char & right_operator)
{
	if (left_operator == right_operator && left_operator == '^') {
		return false;
	}
	else if (left_operator == '^') {
		return true;
	}
	else if (right_operator == '^') {
		return false;
	}
	else if (left_operator == '*' || left_operator == '/' ) {
		return true;
	}
	else if (right_operator == '*' || right_operator == '/') {
		return false;
	}

	return true;
}

// Counts operation
double Calculator::countOperation(const char & operation, double o1, double o2)
{
	double ans;
	switch (operation)
	{
	case'+': {
		ans = o1 + o2;
		break;
	}
	case'-': {
		ans = o2 - o1;
		break;
	}
	case'*': {
		ans = o1*o2;
		break;
	}
	case'/': {
		ans = o2 / o1;
		break;
	}
	case'^': {
		ans = pow(o2, o1);
		break;
	}
	}
	return ans;
}


// change infix string to postfix
void Calculator::convertInfixToPostfix()
{
	std::stack<char> stack;   // Стэк операций.
	infix_ = '(' + infix_ + ')';
	for (std::size_t i = 0; i < infix_.length(); ++i) {
		const char current = infix_[i];
	
		if (isalnum(current) || current == '.') {
			postfix_ += current;  
		} else 
			if (current == '(') {
				stack.push(current);  
			} else  
				if (isOperator(current)) { 
					if (current == '-' && infix_[i-1] == '(')
						postfix_ = postfix_  + '0'; // Unary minus
					char right_operator = current;
					// If the priority of operator is higher, than it`s being popped from the stack
					while (!stack.empty() && precedence(stack.top(), right_operator) && isOperator(stack.top())) {
						postfix_ = postfix_ + ' ' + stack.top();
						stack.pop();
					}
					postfix_ += ' ';
					stack.push(right_operator);   .
				} else  
					if (current == ')') {
						while (!stack.empty() && stack.top() != '(') {
							postfix_ = postfix_ + ' ' + stack.top();
							stack.pop();
						}
						// If there are no "(" added at the beginning, then input incorrect
						if (stack.empty())
							throw std::runtime_error(" Incorrect input! ");
						stack.pop(); // Delete "("
						postfix_ = postfix_ + ' ';
					}
	}

\
	while (!stack.empty() && stack.top() != '(') {
		postfix_ = postfix_ + ' ' + stack.top();
		stack.pop();
	}
	postfix_ += ' ';
}

// Counts expression.
void Calculator::countValue()
{
	std::stack<double> stack; // Stack of operations.
	string tmp; // To add number to postfix string.

	for (size_t i = 0; i < postfix_.length(); ++i) {
		char current = postfix_[i];
		if (current == '.' || isalnum(current)) {
			tmp += current;
		} else
			if (isspace(current) && (isalnum(postfix_[i - 1]) || postfix_[i - 1] == '.')) {
				stack.push(stod(tmp));
				tmp = "";
			} else
				if (isOperator(current)) {
					if (tmp != "") {
						stack.push(stod(tmp));
						tmp = "";
					}
					double o1 = stack.top();
					stack.pop();
					double o2 = stack.top();
					stack.pop();
					stack.push(countOperation(current, o1, o2));
				}
	}
	value_ = stack.top();
}
