#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Invalid Arguments" << std::endl;
		std::cout << "Usage: ./btc <file>" << std::endl;
		return (1);
	}

	BitcoinExchange exchangeRate(argv[1]);
	return (0);
}