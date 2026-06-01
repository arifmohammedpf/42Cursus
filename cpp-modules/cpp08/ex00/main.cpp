# include "easyfind.hpp"

int main()
{
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	try
	{
		std::cout << easyfind(v, 5) << std::endl;
		std::cout << easyfind(v, 11) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}