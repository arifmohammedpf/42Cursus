#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain Default Constructor called" << std::endl;
}


Brain::Brain(Brain const &Object)
{
	std::cout << "Brain Copy Constructor called" << std::endl;
	*this = Object;
}

Brain & Brain::operator=(Brain const &rhs)
{
	std::cout << "Brain Copy Assignment Operator called" << std::endl;
	if (this != &rhs)
	{
		for(int i = 0; i < 100; i++)
			this->ideas[i] = rhs.ideas[i];
	}
	return (*this);
}

Brain::~Brain()
{
	std::cout << "Brain Destructor called" << std::endl;
}

void Brain::setIdea(int idx, const std::string &idea) {
	if (idx >= 0 && idx < 100) {
			this->ideas[idx] = idea;
	}
	else {
			throw std::out_of_range("Invalid index");
	}   
}

const std::string &Brain::getIdea(int idx) const {
	if (idx >= 0 && idx < 100) {
			return this->ideas[idx];
	}
	throw std::out_of_range("Invalid index");
}