#include "Fixed.hpp"


Fixed::Fixed(): _fixed(0)
{
	std::cout << "Default Constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &object)
{
	std::cout << "Copy Constructor called" << std::endl;
	*this = object;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

Fixed & Fixed::operator=(Fixed const &rhs)
{
	std::cout << "Copy Assignment Operator called" << std::endl;
	if (this != &rhs)
		this->_fixed = rhs.getRawBits();
	return (*this);
}

void	Fixed::setRawBits(int const raw)
{
	std::cout << "Set raw bits called" << std::endl;
	this->_fixed = raw;
}

int		Fixed::getRawBits() const
{
	std::cout << "Get raw bits called" << std::endl;
	return (this->_fixed);
}