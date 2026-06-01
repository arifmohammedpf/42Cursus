#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat: public Animal
{
	private:
		Brain *_brain;
	protected:
		std::string _type;
	
	public:
		Cat();
		Cat(Cat const &object);
		Cat &operator=(Cat const &rhs);
		~Cat();

		void	makeSound() const;
		std::string	getType() const;
		Brain	*getBrain() const;
};

#endif