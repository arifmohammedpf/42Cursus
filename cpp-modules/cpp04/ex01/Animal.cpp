#include "Animal.hpp"

Animal::Animal(): _type("Animal")
{
	std::cout << "Animal Default Constructor called" << std::endl;
}


Animal::Animal(Animal const &object)
{
	std::cout << "Animal Copy Constructor called" << std::endl;
	*this = object;
}

Animal & Animal::operator=(Animal const &rhs)
{
	std::cout << "Animal Copy Assignment Operator called" << std::endl;
	if (this != &rhs)
		this->_type = rhs._type;
	return (*this);
}

Animal::~Animal()
{
	std::cout << "Animal Default Destructor called" << std::endl;
}

void	Animal::makeSound() const
{
	std::cout << "Animal makes sound ..." << std::endl;
}

std::string Animal::getType() const
{
	return (this->_type);
}