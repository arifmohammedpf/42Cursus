#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cstdlib>

class RPN
{
    private:
        std::stack<int> _stack;
        bool isOperator(std::string token);
        void doOperation(std::string op);
        void calculate(std::string input);

    public:
        RPN();
        RPN(std::string input);
        RPN(const RPN &object);
        RPN &operator=(const RPN &rhs);
        ~RPN();
};

#endif