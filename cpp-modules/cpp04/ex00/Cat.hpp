#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"

class Cat: public Animal
{
	protected:
		std::string _type;
	
	public:
		Cat();
		Cat(Cat const &object);
		Cat &operator=(Cat const &rhs);
		~Cat();

		void	makeSound() const;
		std::string	getType() const;
};

#endif