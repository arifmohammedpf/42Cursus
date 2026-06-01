#include "Zombie.hpp"

int main()
{
	Zombie *zoom = newZombie("Zombie 1");
	zoom->announce();
	delete zoom;
	randomChump("Zombie 2");
}