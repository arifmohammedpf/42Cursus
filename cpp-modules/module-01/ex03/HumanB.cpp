#include "HumanB.hpp"

HumanB::HumanB(std::string name): _name(name)
{
	this->_WeaponB = NULL;
}

HumanB::~HumanB()
{
}

void	HumanB::setWeapon(Weapon &B)
{
	this->_WeaponB = &B;
}

void	HumanB::attack()
{
	if (_WeaponB)
		std::cout << this->_name << " attacks with their "
				<< this->_WeaponB->getType() << std::endl;
	else
		std::cout << this->_name << " has no weapon to attack." << std::endl;
}