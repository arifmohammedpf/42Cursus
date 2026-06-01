#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <fstream>

class ShrubberyCreationForm : public AForm
{
private:
	std::string	_target;
	void	write_ascii_tree() const;
	class MyCustomException : public std::exception
	{
		public:
			const char *what() const throw();
	};
public:
	ShrubberyCreationForm(std::string _target);
	ShrubberyCreationForm(ShrubberyCreationForm const &object);
	ShrubberyCreationForm & operator=(ShrubberyCreationForm const &rhs);
	~ShrubberyCreationForm();

	void	execute(Bureaucrat const &executor) const;
	std::string	getTarget() const;
};

#endif