#include "AForm.hpp"

AForm::AForm(): _name("No Name"), _isSigned(false), _signGrade(1), _execGrade(5) 
{
	std::cout << "AForm Default Constructor called" << std::endl;
}

AForm::AForm(std::string name, int _signGrade, int _execGrade):
	_name(name), _isSigned(false), _signGrade(_signGrade),
	_execGrade(_execGrade)
{
	std::cout << "AForm Name Constructor called" << std::endl;
	try
	{
		if (this->_execGrade > 150 || this->_signGrade > 150)
			throw AForm::GradeTooLowException();
		else if (this->_execGrade < 1 || this->_signGrade < 1)
			throw AForm::GradeTooHighException();			
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

AForm::AForm(AForm const &object):
	_name(object._name), _isSigned(object._isSigned),
	_signGrade(object._signGrade), _execGrade(object._execGrade)
{
	std::cout << "AForm Copy Constructor called" << std::endl;
}

AForm & AForm::operator=(AForm const &rhs)
{
	std::cout << "AForm Copy Assignment Operator = called" << std::endl;
	if (this != &rhs)
	{
		this->_isSigned= rhs.getSigned();
	}
	return(*this);
}

std::ostream &operator<<(std::ostream &out, AForm const &rhs)
{
	std::cout << "AForm Stream Insertion Operator << called" << std::endl;
	out << "AForm name: " << rhs.getName() << std::endl;
	out << "Grade to sign: " << rhs.getSignGrade() << std::endl;
	out << "Grade to execute: " << rhs.getExecGrade() << std::endl;
	out << "Signed: " << rhs.getSigned() << std::endl;
	return (out);
}

AForm::~AForm()
{
	std::cout << "AForm Destructor called" << std::endl;
}

void	AForm::beSigned(Bureaucrat const &rhs)
{
	if (rhs.getGrade() > this->_signGrade)
		throw AForm::GradeTooLowException();
	else
		this->_isSigned = true;
}

bool	AForm::getSigned() const
{
	return (this->_isSigned);
}

int	AForm::getSignGrade() const
{
	return (this->_signGrade);
}

int	AForm::getExecGrade() const
{
	return (this->_execGrade);
}

std::string AForm::getName() const
{
	return (this->_name);
}

const char* AForm::GradeTooHighException::what() const throw()
{
	return("Grade Too High");
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return("Grade Too Low");
}