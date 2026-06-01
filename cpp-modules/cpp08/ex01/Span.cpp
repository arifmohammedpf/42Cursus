#include "Span.hpp"

Span::Span()
{
}

Span::Span(unsigned int N) : _max(N)
{
}

Span::Span(Span const &object)
{
	*this = object;
}

Span &Span::operator=(Span const &rhs)
{
	if (this != &rhs)
	{
		this->_max = rhs._max;
		this->_vec = rhs._vec;
	}
	return (*this);
}

Span::~Span()
{
}

void Span::addNumber(int num)
{
	if (this->_vec.size() == this->_max)
		throw Span::ContainerMaxException();
	if (num < 0)
		throw std::runtime_error("Number is Negative");
	this->_vec.push_back(num);
}

int Span::shortestSpan()
{
	int minSpan;

	if (this->_vec.size() < 1)
		throw Span::ContainerEmptyException();
	std::sort(this->_vec.begin(), this->_vec.end());
	minSpan = this->_vec[1] - this->_vec[0];
	for (unsigned int i = 1; i < this->_vec.size() - 1; i++)
	{
		if (this->_vec[i + 1] - this->_vec[i] < minSpan)
			minSpan = this->_vec[i + 1] - this->_vec[i];
	}
	return (minSpan);
}

int Span::longestSpan()
{
	int lngSpan;

	if (this->_vec.size() < 1)
		throw Span::ContainerEmptyException();
	std::sort(this->_vec.begin(), this->_vec.end());
	lngSpan = this->_vec[this->_vec.size() - 1] - this->_vec[0];
	return (lngSpan);
}

void Span::addMoreNum(int size)
{
    if (this->_vec.size() + size > this->_max)
        throw ContainerMaxException();
    for (int i = 0; i < size; i++)
    {
        this->_vec.push_back(rand() % 100);
    }
}

const char *Span::ContainerMaxException::what() const throw()
{
	return ("Container(Vector) Is Full");
}

const char *Span::ContainerEmptyException::what() const throw()
{
	return ("Container(Vector) Is Empty");
}