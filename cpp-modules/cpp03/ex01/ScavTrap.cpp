#include "ScavTrap.hpp"

ScavTrap::ScavTrap(): ClapTrap()
{
	std::cout << "ScavTrap Default Constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name): ClapTrap(name)
{
	std::cout << "ScavTrap Parameterized Constructor called" << std::endl;
}

ScavTrap::ScavTrap(ScavTrap const &object): ClapTrap(object)
{
	std::cout << "ScavTrap Copy Constructor called" << std::endl;
}

ScavTrap & ScavTrap::operator=(ScavTrap const &rhs)
{
	std::cout << "ScavTrap Copy Assignment Operator called" << std::endl;
	if (this != &rhs)
	{
		ClapTrap::operator=(rhs);
	}
	return (*this);
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap Destructor Called" << std::endl;
}

void	ScavTrap::attack(const std::string &target)
{
	std::cout << "ScavTrap attack() is called." << std::endl;
	if (!this->_hitPoints)
	{
		std::cout << "ScavTrap " << this->_name << " has no hit points."
				<< std::endl;
		return ;
	}
	else if (!this->_energyPoints)
	{
		std::cout << "ScavTrap " << this->_name << " has no energy points."
				<< std::endl;
		return ;
	}
	this->_energyPoints -= 1;
	if (target.length())
		std::cout << "ScavTrap " << this->_name << " attacks " << target
				<< ", causing " << this->_attackDamage << " points of damage !"
				<< std::endl;
	else
		std::cout << "Target not set" << std::endl;
}

void	ScavTrap::guardGate()
{
	std::cout << "ScavTrap guardGate() is called." << std::endl;
	std::cout << "ScavTrap " << this->_name << "is now in Gate Keeper Mode."
			<< std::endl;
}