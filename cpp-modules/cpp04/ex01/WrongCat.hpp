#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

#include "WrongAnimal.hpp"

class WrongCat: public WrongAnimal
{
	protected:
		std::string _type;
	
	public:
		WrongCat();
		WrongCat(WrongCat const &object);
		WrongCat &operator=(WrongCat const &rhs);
		~WrongCat();

		void	makeSound() const;
		std::string	getType() const;
};

#endif