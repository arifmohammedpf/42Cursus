#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"

int main()
{
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    const WrongAnimal* wmeta = new WrongAnimal();
    const WrongAnimal* wcat = new WrongCat();

    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    std::cout << wcat->getType() << " " << std::endl;

    i->makeSound(); //will output the cat sound!
    j->makeSound();
    wcat->makeSound();
    meta->makeSound();
    wmeta->makeSound();
    
    delete i;
    delete j;
    delete meta;
    delete wcat;
    delete wmeta;
}