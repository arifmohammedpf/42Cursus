#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"

int main(){

	const int n = 10;
	Animal* animals[n];
	for (int i = 0; i < n; i++){
			if (i < n/2){
					animals[i] = new Dog();
			}
			else{
					animals[i] = new Cat();
			}
	}

	for (int i = 0; i < n; i++){
			delete animals[i];
	}


	Dog base;
	base.getbrain()->setIdea(0, "I want to eat");
	std::cout << "base idea " << base.getbrain()->getIdea(0) << std::endl;
	{
			Dog clone;
			clone = base;
			std::cout << "clone idea: " << clone.getbrain()->getIdea(0) << std::endl;
			clone.getbrain()->setIdea(0, "I want to play");
			std::cout << "base idea: " << base.getbrain()->getIdea(0) << std::endl;
			std::cout << "clone idea: " << clone.getbrain()->getIdea(0) << std::endl;
			std::cout << "clone's Brain address: " << clone.getbrain() << std::endl;
			std::cout << "base's Brain address: " << base.getbrain() << std::endl;
	}
	std::cout << "base idea " << base.getbrain()->getIdea(0) << std::endl;
			return (0);
}