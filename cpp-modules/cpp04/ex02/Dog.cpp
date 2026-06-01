#include "Dog.hpp"


Dog::Dog(): _brain(new Brain()),  _type("Dog")
{
	std::cout << "Dog Default Constructor called" << std::endl;
}


Dog::Dog(Dog const &object): Animal(object)
{
	std::cout << "Dog Copy Constructor called" << std::endl;
	*this = object;
}

Dog & Dog::operator=(Dog const &rhs)
{
	std::cout << "Dog Copy Assignment Operator called" << std::endl;
	if (this != &rhs) {
		delete _brain; // Clean up existing brain
		_brain = new Brain(*rhs._brain); // Deep copy the brain
		_type = rhs._type;
	}
	return (*this);
}

Dog::~Dog()
{
	std::cout << "Dog Destructor called" << std::endl;
	delete (this->_brain);
}

void	Dog::makeSound() const
{
	std::cout << "Dog::makeSound() called" << std::endl;
	std::cout << "Dog makes sound ... Woof" << std::endl;
}

std::string	Dog::getType() const
{
	std::cout << "Dog::getType() called" << std::endl;
	return (this->_type);
}

Brain	*Dog::getbrain() const
{
	return (this->_brain);
}