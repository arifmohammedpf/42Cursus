#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string _target) : AForm("ShruberryCreationForm", 145, 137), _target(_target)
{
	std::cout << "ShrubberyCreationForm Default Constructor called" << std::endl;
	this->write_ascii_tree();
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &object) : AForm(object), _target(object.getTarget())
{
	std::cout << "ShrubberyCreationForm Copy Constructor called" << std::endl;
	*this = object;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm const &rhs)
{
	std::cout << "ShrubberyCreationForm Copy Assignment Operator called" << std::endl;
	if (this != &rhs)
		AForm::operator=(rhs);
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << "ShrubberyCreationForm Destructor called" << std::endl;
}

std::string ShrubberyCreationForm::getTarget() const
{
	return (this->_target);
}

void ShrubberyCreationForm::write_ascii_tree() const
{
	std::ofstream file;

	file.open((this->_target + "_shrubbery").c_str());
	if (file.fail())
		throw ShrubberyCreationForm::MyCustomException();
	file << "    oxoxoo    ooxoo \n"
		 << "	ooxoxo oo  oxoxooo\n"
		 << "   oooo xxoxoo ooo ooox\n"
		 << "	oxo o oxoxo  xoxxoxo\n"
		 << "	oxo xooxoooo o ooo\n"
		 << "		ooo\\oo\\  /o/o\n"
		 << "			\\  \\/ /\n"
		 << "			|   /\n"
		 << "			|  |\n"
		 << "			| D|\n"
		 << "			|  |\n"
		 << "			|  |\n"
		 << "	______/____\\____\n";
	file.close();
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	try
	{
		if (this->getSigned())
		{
			if (executor.getGrade() <= this->getExecGrade())
			{
				this->write_ascii_tree();
				std::cout << this->_target << "_shruberry tree has been created" << std::endl;
			}
			else
				throw AForm::GradeTooLowException();
		}
		else
			throw std::runtime_error("Bureaucrat Form not signed");
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

const char *ShrubberyCreationForm::MyCustomException::what() const throw()
{
	return ("Couldn't Create/Open File");
}