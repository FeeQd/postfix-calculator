#pragma once

#include <string>

class Calculator {
public:
	// Конструкторы.
	Calculator(): value_(0) {};
	Calculator(const std::string& line);
	
	// Деструктор.
	~Calculator();

	void convertInfixToPostfix(); //  Change infix to postfix notations.
	void countValue(); // Count postfix expression
	
	std::string postfix() const; // returns postfix_ 
	double value() const; // returns counted value
private:
	std::string infix_;
	std::string postfix_;
	double value_;

	bool isOperator(const char& c);
	bool precedence(const char& left_operator, const char& right_operator);
	double countOperation(const char& operation, double o1, double o2);
};
