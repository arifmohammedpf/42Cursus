#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <iostream>
#include <string>

class WrongAnimal
{
	protected:
		std::string _type;
		
	public:
		WrongAnimal();
		WrongAnimal(WrongAnimal const &object);
		WrongAnimal &operator=(WrongAnimal const &rhs);
		~WrongAnimal();

		void	makeSound() const;
		std::string	getType() const;
};

#endif