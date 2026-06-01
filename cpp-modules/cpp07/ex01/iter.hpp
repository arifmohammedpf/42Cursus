#ifndef ITER_HPP
#define ITER_HPP

# include <iostream>

template< typename T >
void	printElem(T const &elem)
{
	std::cout << elem << std::endl;
}

template< typename T >
void	iter(T *arr, int len, void(*f)(T const &elem))
{
	for (int i = 0; i < len; i++)
		f(arr[i]);
	
}

#endif