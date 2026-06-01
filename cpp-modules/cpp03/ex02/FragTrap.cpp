#include "FragTrap.hpp"

FragTrap::FragTrap(): ClapTrap()
{
	std::cout << "FragTrap Default Construtor is called." << std::endl;
}

FragTrap::FragTrap(std::string name): ClapTrap(name)
{
	std::cout << "FragTrap Parameterized Constructor called" << std::endl;
}

FragTrap::FragTrap(FragTrap const &object) : ClapTrap(object)
{
	std::cout << "FragTrap Copy Constructor called" << std::endl;
}

FragTrap & FragTrap::operator=(FragTrap const &rhs)
{
	std::cout << "FragTrap Copy Assignment Operator called" << std::endl;
	if (this != &rhs)
	{	
		ClapTrap::operator=(rhs);
	}
	return (*this);
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap Destructor Called" << std::endl;
}

void	FragTrap::attack(const std::string &target)
{
	std::cout << "FragTrap attack() is called." << std::endl;
	if (!this->_hitPoints)
	{
		std::cout << "FragTrap " << this->_name << " has no hit points."
				<< std::endl;
		return ;
	}
	else if (!this->_energyPoints)
	{
		std::cout << "FragTrap " << this->_name << " has no energy points."
				<< std::endl;
		return ;
	}
	this->_energyPoints -= 1;
	if (target.length())
		std::cout << "FragTrap " << this->_name << " attacks " << target
				<< ", causing " << this->_attackDamage << " points of damage !"
				<< std::endl;
	else
		std::cout << "Target not set" << std::endl;
}


void	FragTrap::highFiveGuys()
{
	std::cout << "FragTrap " << this->_name << " is asking for HighFive"
			<< std::endl;
}