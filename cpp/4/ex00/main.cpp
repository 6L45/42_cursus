#include "animal.hpp"
#include "goodPet.hpp"
#include "wrongPet.hpp"

void	wrongMain()
{
	const wrongAnimal* meta = new wrongAnimal();
	const wrongAnimal* i = new wrongCat();

	std::cout << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound();
	meta->makeSound();
	delete i;
	delete meta;
}

int	main()
{
	Animal *a = new Animal();
	Animal b(*a);
	Animal c = *a;
	Animal d;

	out a->getType() nl;
	out b.getType() nl;
	out c.getType() nl;

	d = *a;

	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	

	const Animal* i = new Cat();

	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound();
	j->makeSound();
	meta->makeSound();

	Cat l;
	Cat k;

	l = k;
	l = *reinterpret_cast<const Cat*>(i);

	delete i;
	delete j;
	delete a;
	delete meta;

	wrongMain();

	return (0);
}
