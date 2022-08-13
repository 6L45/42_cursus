#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <stdexcept>
# include <string>

class Bureaucrat
{
	public:
		Bureaucrat(std::string, int);
		Bureaucrat(Bureaucrat const &);
		~Bureaucrat();

		std::string	getName() const;
		int			getGrade() const;
		void		promotion();
		void		retrogradation();

		Bureaucrat	&operator=(Bureaucrat const &);

	private:
		const std::string	_name;
		int					_grade;
		
		void	gradeTooHightExecption();
		void	gradeTooLowExecption();
};

std::ostream	&operator<<(std::ostream &, Bureaucrat &);

#endif
