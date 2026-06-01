#ifndef SPAN_HPP
# define SPAN_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>

class Span
{
	private:
		unsigned int		_max;
		std::vector<int>	_vec;
		
		class	ContainerEmptyException : public std::exception
		{
			public:
				const char *what() const throw();
		};
		class	ContainerMaxException : public std::exception
		{
			public:
				const char *what() const throw();
		};

	public:
		Span();
		Span(unsigned int N);
		Span(Span const &object);
		Span & operator=(Span const &rhs);
		~Span();

		void	addNumber(int num);
		int		shortestSpan();
		int		longestSpan();
		void	addMoreNum(int size);
};

#endif