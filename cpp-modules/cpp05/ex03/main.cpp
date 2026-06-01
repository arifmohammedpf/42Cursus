#include "Intern.hpp"

int main()
{
	{
		std::string formName = "shrubbery creation"; 
		std::string formTarget = "Gorms";
		if (formName.empty() || formTarget.empty()) 
		{
				throw std::invalid_argument("Invalid parameters");
		}
		std::cout << "-----------------------------------------------------------------------------" << std::endl;
		Intern intern;
		std::cout << "-----------------------------------------------------------------------------" << std::endl;
		Bureaucrat bureaucrat("John", 1);
		std::cout << "-----------------------------------------------------------------------------" << std::endl;
		AForm *f = intern.makeForm(formName, formTarget);
		std::cout << "-----------------------------------------------------------------------------" << std::endl;
		std::cout << *f;
		std::cout << "-----------------------------------------------------------------------------" << std::endl;
		bureaucrat.signAForm(*f);
		std::cout << "-----------------------------------------------------------------------------" << std::endl;
		std::cout << (*f).getSigned() << std::endl;
		std::cout << "-----------------------------------------------------------------------------" << std::endl;
		bureaucrat.executeForm(*f);
		std::cout << "-----------------------------------------------------------------------------" << std::endl;
		delete f;
		std::cout << "-----------------------------------------------------------------------------" << std::endl;
	}
}