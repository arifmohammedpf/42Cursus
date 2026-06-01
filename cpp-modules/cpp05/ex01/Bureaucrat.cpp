#include "Bureaucrat.hpp"


Bureaucrat::Bureaucrat(): _name("No Name"), _grade(125)
{
	std::cout << "Bureaucrat Default Constructor called" << std::endl;
}

Bureaucrat::Bureaucrat(std::string name, int grade): _name(name), _grade(grade)
{
	std::cout << "Bureaucrat Name Constructor called" << std::endl;
	try
	{
		if (grade > 150)
			throw Bureaucrat::GradeTooLowException();
		else if (grade < 1)
			throw Bureaucrat::GradeTooHighException();
		else
			this->_grade = grade;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

Bureaucrat::Bureaucrat(Bureaucrat const &object)
{
	std::cout << "Bureaucrat Copy Constructor called" << std::endl;
	*this = object;
}

Bureaucrat & Bureaucrat::operator=(Bureaucrat const &rhs)
{
	std::cout << "Bureaucrat Copy Assignment Operator = called" << std::endl;
	if (this != &rhs)
	{
		this->_grade = rhs.getGrade();
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &out, Bureaucrat const &rhs) {
	std::cout << "Bureaucrat Stream Insertion Operator << called" << std::endl;
    out << rhs.getName() << ", bureaucrat grade " << rhs.getGrade() << ".";
    return (out);
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Bureaucrat Destructor called" << std::endl;
}

int	Bureaucrat::getGrade() const
{
	return (this->_grade);
}

std::string Bureaucrat::getName() const
{
	return (this->_name);
}

void	Bureaucrat::gradeDecrement()
{
	try
	{
		if (this->_grade > 150)
			throw Bureaucrat::GradeTooLowException();
		else if (this->_grade < 1)
			throw Bureaucrat::GradeTooHighException();
		else
			this->_grade++;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}

void	Bureaucrat::gradeIncrement()
{
	try
	{
		if (this->_grade > 150)
			throw Bureaucrat::GradeTooLowException();
		else if (this->_grade < 1)
			throw Bureaucrat::GradeTooHighException();
		else
			this->_grade--;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return("Grade Too High");
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return("Grade Too Low");
}

void	Bureaucrat::signForm(Form &form)
{
	try
	{
		form.beSigned(*this);
		std::cout << this->_name << " signed " << form.getName() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << this->_name << " couldn't sign " << form.getName() << 
				" because " << e.what() << '\n';
	}
}