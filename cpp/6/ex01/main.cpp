# include <iostream>
# include <string>
# include <stdint.h>
# include <typeinfo>

class Data
{
	public:
		std::string	s1;
		int 		n;
		std::string	s2;
};

uintptr_t	*serialize(Data *ptr)
{
	uintptr_t *raw = reinterpret_cast<uintptr_t *>(ptr);

	return (raw); 
}

Data	*deserialize(uintptr_t *raw)
{
	Data *dt = reinterpret_cast<Data *>(raw);
	return (dt);
}

int	main()
{
	Data		*dt = new Data;
	uintptr_t	*raw = serialize(dt);
	Data		*bck = deserialize(raw);

	std::cout << "address : " << dt << std::endl;
	std::cout << "var type : " << typeid(dt).name() << std::endl << std::endl;

	std::cout << "address : " << raw << std::endl;
	std::cout << "var type : " << typeid(raw).name() << std::endl << std::endl;
	
	std::cout << "address : " << bck << std::endl;
	std::cout << "var type : " << typeid(bck).name() << std::endl << std::endl;

	delete bck;
	return (0);
}
