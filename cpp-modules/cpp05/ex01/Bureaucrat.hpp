#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include "Form.hpp"

class Form;
class Bureaucrat
{
	private:
		const std::string _name;
		int			_grade;
		
	public:
		Bureaucrat();
		Bureaucrat(std::string name, int grade);
		Bureaucrat(Bureaucrat const &object);
		Bureaucrat & operator=(Bureaucrat const &rhs);
		~Bureaucrat();
		std::string	getName() const;
		int			getGrade() const;
		void		gradeIncrement();
		void		gradeDecrement();
		void		signForm(Form &form);
		class GradeTooHighException : public std::exception
		{
			public:
				const char *what() const throw();
		};
		
		class GradeTooLowException : public std::exception
		{
			public:
				const char *what() const throw();
		};

};

std::ostream &operator<<(std::ostream &out, Bureaucrat const &rhs);

#endif