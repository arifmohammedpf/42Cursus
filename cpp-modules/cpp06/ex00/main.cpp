#include "ScalarConverter.hpp"

bool is_num(std::string str)
{
	if ((str.find_first_not_of("0123456789") == std::string::npos)
		|| (str.find_first_not_of("-0123456789") == std::string::npos && str[0] == '-'))
		return (true);
	return (false);
}

bool is_float(std::string str)
{
	if ((str.find_first_not_of("0123456789.f") == std::string::npos)
		|| (str.find_first_not_of("-0123456789.f") == std::string::npos && str[0] == '-'))
		return (true);
	return (false);
}

bool is_double(std::string str)
{
	if ((str.find_first_not_of("0123456789.") == std::string::npos)
		|| (str.find_first_not_of("-0123456789.") == std::string::npos && str[0] == '-'))
		return (true);
	return (false);
}

bool is_char(std::string str)
{
	if (str.length() == 1 || str == "nan" || str == "inf" || str == "-inf" || str == "nanf" || str == "inff" || str == "-inff")
		return (true);
	return (false);
}

bool is_convertable(std::string str)
{
	if (is_num(str) || is_double(str) || is_float(str) || is_char(str))
		return (true);
	return (false);
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (is_convertable(argv[1]) && argv[1][0])
		{
			ScalarConverter::convert(argv[1]);
			return (0);
		}
		std::cout << "Invalid Argument" << std::endl;
		return (1);
	}
	std::cout << "Invalid Number of arguments. -- usage : ./convert <arg>" << std::endl;
	return (1);
}