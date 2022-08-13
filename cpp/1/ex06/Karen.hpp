#ifndef KAREN_HPP
#define KAREN_HPP

#include <iostream>
#include <functional>

class Karen
{
	public:
	
		Karen();
		~Karen();

		void complain(std::string level);
	
	private:

		typedef struct s_response
		{
			std::string alert_lvl;
			void (Karen::*func)(void);
		}				t_resp;
		
		t_resp	resp[4];

		void debug(void);
		void info(void);
		void warning(void);
		void error(void);
};

#endif
