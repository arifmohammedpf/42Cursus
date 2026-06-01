#include "iter.hpp"

int	main()
{
	int intArr[5] = {1, 2, 3, 4, 5};
	iter(intArr, 5, printElem);

	char charArr[5] = {'a', 'b', 'c', 'd', 'e'};
	iter(charArr, 5, printElem);
	return (0);
}