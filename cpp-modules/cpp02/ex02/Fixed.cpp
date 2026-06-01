#include "Fixed.hpp"


Fixed::Fixed(): _fixed(0)
{
}

Fixed::Fixed(int const num)
{
	this->setRawBits(num << this->_bits);
}

Fixed::Fixed(float const num)
{
	this->setRawBits(roundf(num * (1 << this->_bits)));
}

Fixed::Fixed(const Fixed &object)
{
	*this = object;
}

Fixed::~Fixed()
{
}

Fixed & Fixed::operator=(Fixed const &rhs)
{
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

bool	Fixed::operator>(const Fixed &rhs) const
{
	return (this->_fixed > rhs.getRawBits());
}

bool	Fixed::operator<(const Fixed &rhs) const
{
	return (this->_fixed < rhs.getRawBits());
}

bool	Fixed::operator>=(const Fixed &rhs) const
{
	return (this->_fixed >= rhs.getRawBits());
}

bool	Fixed::operator<=(const Fixed &rhs) const
{
	return (this->_fixed <= rhs.getRawBits());
}

bool	Fixed::operator==(const Fixed &rhs) const
{
	return (this->_fixed == rhs.getRawBits());
}

bool	Fixed::operator!=(const Fixed &rhs) const
{
	return (this->_fixed != rhs.getRawBits());
}

Fixed	Fixed::operator+(const Fixed &rhs) const
{
	return (this->toFloat() + rhs.toFloat());
}

Fixed	Fixed::operator-(const Fixed &rhs) const
{
	return (this->toFloat() - rhs.toFloat());
}

Fixed	Fixed::operator*(const Fixed &rhs) const
{
	return (this->toFloat() * rhs.toFloat());
}

Fixed	Fixed::operator/(const Fixed &rhs) const
{
	return (this->toFloat() / rhs.toFloat());
}

Fixed & Fixed::operator++()
{
	this->_fixed = this->_fixed + 1;
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed	tmp(*this);
	this->operator++();
	return (tmp);
}

Fixed & Fixed::operator--()
{
	this->_fixed = this->_fixed - 1;
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed	tmp(*this);
	this->operator--();
	return (tmp);
}

Fixed & Fixed::min(Fixed &a, Fixed &b)
{
	if (a < b)
		return (a);
	return (b);
}

Fixed & Fixed::max(Fixed &a, Fixed &b)
{
	if (a > b)
		return (a);
	return (b);
}

const Fixed & Fixed::min(const Fixed &a, const Fixed &b)
{
	if (a < b)
		return (a);
	return (b);
}

const Fixed & Fixed::max(const Fixed &a, const Fixed &b)
{
	if (a > b)
		return (a);
	return (b);
}