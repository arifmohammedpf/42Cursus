#include "Zombie.hpp"

int main()
{
	int n = 3;

	Zombie *zom = zombieHorde(n, "abc");
	delete[] zom;
}