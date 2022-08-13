#ifndef FORM_HPP
# define FORM_HPP

# include "bureaucrat.hpp"

class Bureaucrat;

/*----------------------------------- ABSTRACT FORM ----------------------------------*/
class Form
{
	public:
	/*CONSTRUCTS DESTRUCT*/
		Form(std::string, int g2sign, int g2ex);
		virtual ~Form() {};

	/*PUBLIC METHOD*/
		void	gradeTooHighExecption();
		void	gradeTooLowExecption();
		void	beSigned(const Bureaucrat &);
		void	execute(Bureaucrat const &) const;
		virtual	void	whatNeedsToBeDone() const = 0;

	/*GETTTER SETTER*/
		std::string	getName() const;
		int			getSignLvl() const;
		int			getExLvl() const;
		bool		getStatus() const;
		void		setSignLvl(int);
		void		setExLvl(int);
		void		setStatus(bool);

	private :
		std::string	_name;
		bool		_signed;
		int			_g2ex;
		int			_g2sign;
};

std::ostream	&operator<<(std::ostream &, Form &);


/*-------------------------------------- FORM+ --------------------------------------*/
class ShrubberyCreationForm : public Form
{
	public :
		ShrubberyCreationForm(std::string target)
			: Form("Shrubbery", 145, 137) , _target(target) {};
		ShrubberyCreationForm(ShrubberyCreationForm const &, std::string);
		~ShrubberyCreationForm() {};

		ShrubberyCreationForm	&operator=(ShrubberyCreationForm const &);

		void	whatNeedsToBeDone() const;

	private	:
		std::string	_target;

};

class RobotomyRequestForm : public Form
{
	public :
		RobotomyRequestForm(std::string target)
			: Form("Robotomy", 72, 45) , _target(target) {};
		RobotomyRequestForm(RobotomyRequestForm const &, std::string);
		~RobotomyRequestForm() {};

		RobotomyRequestForm	&operator=(RobotomyRequestForm const &);

		void	whatNeedsToBeDone() const;

	private	:
		std::string	_target;
};

class PresidentialPardonForm : public Form
{
	public :
		PresidentialPardonForm(std::string target)
			: Form("Pardon", 25, 5) , _target(target) {};
		PresidentialPardonForm(PresidentialPardonForm const &, std::string);
		~PresidentialPardonForm() {};

		PresidentialPardonForm	&operator=(PresidentialPardonForm const &);

		void	whatNeedsToBeDone() const;

	private	:
		std::string	_target;
};

#endif
