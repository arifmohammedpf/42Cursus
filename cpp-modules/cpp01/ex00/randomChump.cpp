#include "Zombie.hpp"

void	randomChump(std::string name)
{
	Zombie zom = Zombie(name);
	zom.announce();
}