#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "Weapon.hpp"

class HumanA
{
	private:
		Weapon &_WeaponA;
		std::string _name;
	public:
		HumanA(std::string name, Weapon &A);
		~HumanA();

		void	attack();
};

#endif