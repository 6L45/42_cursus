template<typename T>
const char* Array<T>::OoBException::what() const throw()
{
	return "ArrayException: index out of bounds";
}

template<typename T>
Array<T>::Array()
{
	this->_size = 0;
	this->_arr = NULL;
}

template<typename T>
Array<T>::Array(Array const &model)
{
	if (model._size > 0)
	{
		this->_arr = new T[model._size];
		for (unsigned int i = 0; i < model._size; i++)
			this->_arr[i] = model._arr[i];
	}
	else
		this->_arr = NULL;
	this->_size = model._size;
}

template<typename T>
Array<T>::Array(unsigned int n)
{
	this->_size = n;
	this->_arr = new T[n];
	for (unsigned int i = 0; i < n; i++)
		this->_arr[i] = 1;
}

template<typename T>
Array<T>::~Array()
{
	if (this->_arr)
		delete [] this->_arr;
}

template<typename T>
size_t	Array<T>::size(void) const
{
	return (this->_size);
}

template<typename T>
void	Array<T>::print() const
{
	for (unsigned int i = 0; i < this->_size; i++)
		std::cout << '[' << this->_arr[i] << ']' << " ";
	std::cout << std::endl;
}

template<typename T>
T		&Array<T>::operator[](unsigned int n)
{
	if (n >= this->_size)
		throw Array::OoBException();
	return (this->_arr[n]);
}

template<typename T>
const T	&Array<T>::operator[](unsigned int n) const
{
	return (operator[](n));
}

template<typename T>
Array<T>	&Array<T>::operator=(Array<T> const &model)
{
	if (this->_arr)
	{
		delete [] this->_arr;
		this->_arr = NULL;
	}
	if (model._arr)
	{
		this->_arr = new T[model._size];
		for (unsigned int i = 0; i < model._size; i++)
			this->_arr[i] = model._arr[i];
	}
	this->_size = model._size;
	return (*this);
}
