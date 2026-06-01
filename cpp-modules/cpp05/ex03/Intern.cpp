#include "Intern.hpp"

Intern::Intern()
{
	std::cout << "Intern Default Constructor called" << std::endl;
}

Intern::Intern(const Intern &object)
{
	std::cout << "Intern Copy Constructor called" << std::endl;
	*this = object;
}

Intern & Intern::operator=(const Intern &rhs)
{
	std::cout << "Intern Copy Assignment Operator called" << std::endl;
	if (this != &rhs)
	{}
	return (*this);
}

Intern::~Intern()
{
	std::cout << "Intern Destructor called" << std::endl;
}

AForm	*Intern::makeForm(std::string name, std::string target)
{
	std::string formNames[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};
	AForm *forms[3] = {new ShrubberyCreationForm(target), new RobotomyRequestForm(target), new PresidentialPardonForm(target)};
	for (int i = 0; i < 3; i++) {
		if (name == formNames[i]) {
			delete forms[(i + 1) % 3];
			delete forms[(i + 2) % 3];
			return forms[i];
		}
	}
	delete forms[0];
	delete forms[1];
	delete forms[2];
	throw std::runtime_error("Form not found");
}