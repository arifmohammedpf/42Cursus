#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog: public Animal
{
	private:
		Brain *_brain;

	protected:
		std::string _type;
	
	public:
		Dog();
		Dog(Dog const &object);
		Dog &operator=(Dog const &rhs);
		~Dog();

		void	makeSound() const;
		std::string	getType() const;
		Brain *getbrain() const;
};

#endif