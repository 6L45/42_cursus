
template <typename T>
MutantStack<T>& MutantStack<T>::operator=(const MutantStack<T> & model)
{
	this->c = model.c;
	return (*this);
}

template <typename T>
typename MutantStack<T>::iterator	MutantStack<T>::begin(void)
{
	return (this->c.begin());
}

template <typename T>
typename MutantStack<T>::iterator	MutantStack<T>::end(void)
{
	return (this->c.end());
}
