#include "Fixed.hpp"


Fixed::Fixed(): _fixed(0)
{
	std::cout << "Default Constructor called" << std::endl;
}

Fixed::Fixed(int const num)
{
	std::cout << "Int Constructor called" << std::endl;
	this->setRawBits(num << this->_bits);
}

Fixed::Fixed(float const num)
{
	std::cout << "Float Constructor called" << std::endl;
	this->setRawBits(roundf(num * (1 << this->_bits)));
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
	this->_fixed = raw;
}

int		Fixed::getRawBits() const
{
	return (this->_fixed);
}

std::ostream & operator<<(std::ostream &out, Fixed const &rhs)
{
	out << rhs.toFloat();
	return (out);
}

float	Fixed::toFloat() const
{
	return (roundf(this->_fixed) / (1 << this->_bits));
}

int	Fixed::toInt() const
{
	return (this->_fixed >> this->_bits);
}