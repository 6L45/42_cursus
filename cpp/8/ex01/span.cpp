#include "span.hpp"

Span::Span(unsigned int n)
{
	this->_n = n;
}

Span::Span(unsigned int n, int random)
{
	(void)random;
	this->_n = n;
	for (unsigned int i = 0; i < n; i++)
		this->_vec.push_back(rand());
}

Span::Span(Span const &model)
{
	this->_n = model._n;
	this->_vec = model._vec;
}

Span::~Span()
{
 ;
}

Span	&Span::operator=(Span const &model)
{
	if (this == &model)
		return *this;
	this->_n = model._n;
	this->_vec = model._vec;

	return *this;
}

void	Span::addNumber(int n)
{
	if (this->_vec.size() >= this->_n)
		throw std::runtime_error("Span is already full!");
	this->_vec.push_back(n);
}

int		Span::shortestSpan() const
{
	if (this->_vec.empty() || this->_vec.size() == 1)
		throw std::runtime_error("Span is empty or contains only one element!");
	
	std::vector<int> copy = this->_vec;
	std::sort(copy.begin(), copy.end());

	int min_diff = INT_MAX;
	int prev = *copy.begin();
	for (std::vector<int>::iterator iter = copy.begin() + 1; iter != copy.end(); iter++)
	{
		min_diff = std::min(min_diff, *iter - prev);
		prev = *iter;
	}

	return (min_diff);
}

int		Span::longestSpan() const
{
	if (this->_vec.empty() || this->_vec.size() == 1)
		throw std::runtime_error("Span is empty or contains only one element!");

	std::vector<int> copy = this->_vec;
	std::sort(copy.begin(), copy.end());

	return (copy.back() - copy.front());
}
