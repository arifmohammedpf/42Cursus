#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &A): _WeaponA(A), _name(name)
{
}

HumanA::~HumanA()
{
}

void	HumanA::attack()
{
	std::cout << this->_name << " attacks with their "
			<< this->_WeaponA.getType() << std::endl;
}