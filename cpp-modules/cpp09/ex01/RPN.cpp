#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(std::string input)
{
	this->calculate(input);
}

RPN::RPN(const RPN &object)
{
	*this = object;
}

RPN &RPN::operator=(const RPN &rhs)
{
	if (this != &rhs)
	{
		this->_stack = rhs._stack;
	}
	return (*this);
}

RPN::~RPN()
{
}

bool RPN::isOperator(std::string token)
{
	if (token == "+" || token == "-" || token == "*" || token == "/")
		return (true);
	return (false);
}

void RPN::doOperation(std::string op)
{
	if (this->_stack.size() < 2)
	{
		throw std::runtime_error("Error");
	}

	int b = this->_stack.top();
	this->_stack.pop();
	int a = this->_stack.top();
	this->_stack.pop();

	int result;

	if (op == "+")
		result = a + b;
	else if (op == "-")
		result = a - b;
	else if (op == "*")
		result = a * b;
	else if (op == "/")
	{
		if (b == 0)
		{
			throw std::runtime_error("Error: Division by zero");
		}
		result = a / b;
	}

	this->_stack.push(result);
}

void RPN::calculate(std::string input)
{
	std::stringstream ss(input);
	std::string token;

	while (ss >> token)
	{
		if (this->isOperator(token))
		{
			this->doOperation(token);
		}
		else if (token.size() == 1 && isdigit(token[0]))
		{
			int num = atoi(token.c_str());
			this->_stack.push(num);
		}
		else
		{
			throw std::runtime_error("Error");
		}
	}

	if (this->_stack.size() != 1)
	{
		throw std::runtime_error("Error");
	}

	std::cout << this->_stack.top() << std::endl;
}