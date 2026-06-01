#include "ClapTrap.hpp"

ClapTrap::ClapTrap(): _name(""), _hitPoints(100), _energyPoints(50), _attackDamage(20)
{
	std::cout << "ClapTrap Default Constructor called" << std::endl;
}
ClapTrap::ClapTrap(std::string name): _name(name), _hitPoints(100), _energyPoints(50), _attackDamage(20)
{
	std::cout << "ClapTrap Parameterized Constructor called" << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const &object)
{
	std::cout << "ClapTrap Copy Constructor called" << std::endl;
	*this = object;
}

ClapTrap & ClapTrap::operator=(ClapTrap const &rhs)
{
	std::cout << "ClapTrap Copy Assignment Operator called" << std::endl;
	if (this != &rhs)
	{
		this->_name = rhs._name;
		this->_hitPoints = rhs._hitPoints;
		this->_attackDamage = rhs._attackDamage;
		this->_energyPoints = rhs._energyPoints;
	}
	return (*this);
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap Destructor Called" << std::endl;
}

void	ClapTrap::attack(const std::string &target)
{
	std::cout << "ClapTrap attack() is called." << std::endl;
	if (!this->_hitPoints)
	{
		std::cout << "ClapTrap " << this->_name << " has no hit points."
				<< std::endl;
		return ;
	}
	else if (!this->_energyPoints)
	{
		std::cout << "ClapTrap " << this->_name << " has no energy points."
				<< std::endl;
		return ;
	}
	this->_energyPoints -= 1;
	if (target.length())
		std::cout << "ClapTrap " << this->_name << " attacks " << target
				<< ", causing " << this->_attackDamage << " points of damage !"
				<< std::endl;
	else
		std::cout << "Target not set" << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << "ClapTrap takeDamage() is called." << std::endl;
	if (int(amount) < 0)
	{
		std::cout << "Invalid Damage value" << std::endl;
		return ;
	}
	else if (int(amount) > this->_hitPoints)
	{
		this->_hitPoints = 0;
		std::cout << "ClapTrap " << this->_name << " has " << this->_hitPoints 
				<< " hitPoints left." << std::endl;
		return ;
	}
	else
	{
		this->_hitPoints -= (int)amount;
		std::cout << "ClapTrap " << this->_name << " has " << this->_hitPoints 
				<< " hitPoints left." << std::endl;
		return ;
	}
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	std::cout << "ClapTrap beRepaired() is called." << std::endl;
	if (!this->_hitPoints)
	{
		std::cout << "ClapTrap " << this->_name << " has no hit points."
				<< std::endl;
		return ;
	}
	else if (!this->_energyPoints)
	{
		std::cout << "ClapTrap " << this->_name << " has no energy points."
				<< std::endl;
		return ;
	}
	this->_energyPoints -= 1;
	this->_hitPoints += (int)amount;
	std::cout << "ClapTrap " << this->_name << " has " << this->_hitPoints
			<< " hitPoints left." << std::endl;
	std::cout << "ClapTrap " << this->_name << " has " << this->_energyPoints
			<< " energyPoints left." << std::endl;
}