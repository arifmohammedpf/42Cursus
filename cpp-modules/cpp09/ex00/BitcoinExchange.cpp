#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(std::string infile)
{
	if (!this->readDataFile())
		return;
	if (!this->calculate(infile))
		return;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &object)
{
	*this = object;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	if (this != &rhs)
	{
		this->_rates = rhs._rates;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

bool BitcoinExchange::readDataFile()
{
	std::ifstream data("data.csv");
	std::string line;

	if (data.fail())
	{
		std::cout << "Error: Cannot Open Data File" << std::endl;
		data.close();
		return (false);
	}
	getline(data, line);
	while (!(data.eof()))
	{
		getline(data, line);

		std::stringstream str(line);
		std::string date, rate;
		getline(str, date, ',');
		getline(str, rate);
		this->_rates[date] = atof(rate.c_str());
	}
	data.close();
	return (true);
}

bool BitcoinExchange::isValidDateValues(std::string year, std::string month, std::string day)
{
	int y = atoi(year.c_str());
	int m = atoi(month.c_str());
	int d = atoi(day.c_str());

	if (y < 2009 || y > 2022)
		return (false);
	if (m < 1 || m > 12)
		return (false);
	if (d < 1 || d > 31)
		return (false);
	if ((m == 2 && d > 28) && (y != 2012 && y != 2016 && y != 2020))
		return (false);
	if ((m == 2 && d > 29))
		return (false);
	if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30)
        return (false);
	return (true);
}

bool BitcoinExchange::isValidDate(std::string date)
{
	std::stringstream str(date);
	std::string year, month, day;

	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return (false);
	}
	getline(str, year, '-');
	getline(str, month, '-');
	getline(str, day);
	if (!this->isValidDateValues(year, month, day))
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return (false);
	}
	return (true);
}

bool BitcoinExchange::isValidDelim(std::string date)
{
	if (date.find(" | ") != 10)
	{
		std::cout << "Error: Invalid Delimiter" << std::endl;
		return (false);
	}
	return (true);
}

float BitcoinExchange::isValidValue(std::string value)
{
	float val = atof(value.c_str());
	if (val < 0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return (-1);
	}
	if (val > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return (-1);
	}
	return (val);
}

std::string BitcoinExchange::lowerBound(std::string date)
{
	std::stringstream str(date);
	std::string year, month, day, newDate;

	getline(str, year, '-');
	getline(str, month, '-');
	getline(str, day);
	int y = atoi(year.c_str());
	int m = atoi(month.c_str());
	int d = atoi(day.c_str());
	if (d > 1)
		d--;
	else if (m > 1)
	{
		d = 31;
		m--;
	}
	else if (y > 2008)
	{
		d = 31;
		m = 12;
		y--;
	}
	std::stringstream nwDate;
	nwDate << y << '-' << std::setw(2) << std::setfill('0') << m << '-' << std::setw(2) << std::setfill('0') << d;
	newDate = nwDate.str();
	return (newDate);
}

void BitcoinExchange::getDateAndPrint(std::string date, float val)
{
	if (this->_rates.find(date) != this->_rates.end())
	{
		float result = val * this->_rates[date];
		std::cout << date << " => " << std::fixed << std::setprecision(2) << val;
		std::cout << " = " << result << std::endl;
		return;
	}
	else if (date >= "2009-01-02")
	{
		date = this->lowerBound(date);
		this->getDateAndPrint(date, val);
	}
}

void BitcoinExchange::parseDates(std::string line)
{
	std::stringstream str(line);
	std::string date, delim, value;
	float val;

	str >> date >> delim >> value;

	val = this->isValidValue(value);
	if (!(this->isValidDate(date)) || !(this->isValidDelim(line)) || val == -1)
		return;
	this->getDateAndPrint(date, val);
}

bool BitcoinExchange::calculate(std::string inf)
{
	std::ifstream infile(inf.c_str());
	std::string line;

	if (infile.fail())
	{
		std::cout << "Error: Input file Error" << std::endl;
		infile.close();
		return (false);
	}
	getline(infile, line);
	if (line != "date | value")
	{
		std::cout << "Error: Invalid File Format" << std::endl;
		infile.close();
		return (false);
	}
	else
	{
		while (getline(infile, line))
		{
			this->parseDates(line);
		}
	}
	infile.close();
	return (true);
}