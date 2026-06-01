#include "Bureaucrat.hpp"

int main()
{
	Bureaucrat b("Bob", 5);
	std::cout << b << std::endl;
	b.gradeIncrement();
	std::cout << b << std::endl;
	b.gradeDecrement();
	std::cout << b << std::endl;
	Bureaucrat be("Nass", -8);
	std::cout << be << std::endl;
	return 0;
}