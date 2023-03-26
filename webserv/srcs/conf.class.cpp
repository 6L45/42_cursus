#include "conf.class.hpp"
#include <type_traits>
#include <string>

Conf::Conf()
{ } //nothing here, unauthorised constructor


Conf::Conf(std::string path_to_file)
	:	_max_connexion(1024),
		_line_read(0)
{
	std::ifstream fs;

	if (! __valide_conf_file_name(path_to_file))
		throw std::invalid_argument("Unvalid extention of configuration file");
	fs.open(path_to_file);
	fs.exceptions(std::ifstream::failbit); //may throw
	__parse_config_file(fs);
	fs.close();
	__check_conf_params();
	__print_everything();
}

/*
	It's pretty clear what this function is up for
*/
void	Conf::__parse_config_file(std::ifstream& fs)
{
	std::string line;

	while (!fs.eof())
	{
		__get_line(fs, line);
		__erase_comment(line);
		__erase_tab_space(line);
		
		if (line.empty())
			continue;
		if (!line.compare(0, 14, "max-connexion:"))
			__add_to<int>(this->_max_connexion, line.erase(0, line.find(':') + 1));
		else if (!line.compare(0, 23, "default-error-log-root:"))
			__add_to<std::string>(this->_default_error_root, line.erase(0, line.find(':') + 1));
		else if (!line.compare(0, 6, "server"))
			__parse_server(fs, line.erase(0,6));
		else
			__error_file_notif(_line_read, "unknown parameter");
	}
}

Conf::~Conf()
{
	
}

void	Conf::__parse_server(std::ifstream &fs, std::string& line)
{
	__server_conf new_serv;

	__erase_tab_space(line);
	if (line.empty() && !fs.eof())
		__get_line(fs, line);
	__erase_tab_space(line);
	if (line.empty() || line.front() != '{')
		return (__error_file_notif(_line_read, "missing '{'"));
	while (!fs.eof())
	{
		__get_line(fs, line);
		__erase_comment(line);
		__erase_tab_space(line);
		if (line.empty())
			continue;
		if (!line.compare(0, 12, "server-name:"))
			__add_to<std::string>(new_serv.server_name, line.erase(0, line.find(':') + 1));
		else if (!line.compare(0, 5, "port:"))
			__add_to<int>(new_serv.port, line.erase(0, line.find(':') + 1));
		else if (!line.compare(0, 5, "host:"))
		{
			line.erase(0, line.find(':') + 1);
			__erase_tab_space(line);
			while (!line.empty())
			{
				std::string temp;
				__get_info(temp, line);
				new_serv.host.push_back(temp);
				__erase_tab_space(line);
			}
		}
		else if (!line.compare(0, 5, "root:"))
			__add_to<std::string>(new_serv.root, line.erase(0, line.find(':') + 1));
		else if (!line.compare(0, 19, "unactive-max-delay:"))
			__add_to<unsigned int>(new_serv.unactive_max_delay, line.erase(0, line.find(':') + 1));
		else if (!line.compare(0, 23, "default-error-log-root:"))
			__add_to<std::string>(new_serv.default_error_root, line.erase(0, line.find(':') + 1));
		else if (!line.compare(0, 8, "location"))
			__parse_location(fs, line.erase(0,8), new_serv);
		else if (!line.compare(0, 3, "cgi"))
			__parse_cgi(fs, line.erase(0,3), new_serv);
		else if (!line.compare(0, 6, "index:"))
		{
			line.erase(0, line.find(':') + 1);
			__erase_tab_space(line);
			while (!line.empty())
			{
				std::string temp;
				__get_info(temp, line);
				new_serv.index.push_back(temp);
				__erase_tab_space(line);
			}
		}
		else if (!line.compare(0, 1, "}"))
			break ;
		else
			__error_file_notif(_line_read, "unknown parameter");
	}
	if (fs.eof() && (line.empty() || line.compare(0, 1, "}")))
		return (__error_file_notif(_line_read, "missing '}' for server"));
	line.erase(0,1);
	if (!line.empty())
		__error_file_notif(_line_read, "line ignored after '}'");
	_sc.push_back(new_serv);
}

void Conf::__parse_location(std::ifstream &fs, std::string &line, __server_conf& sc)
{
	__location new_location;

	// new_location.methods = 0;
	// new_location.options = 0;
	// new_location.body_limits = 0;
	// new_location.body_min_size = 0;
	
	//_SC_DIRACTIVATE(new_location);

	__erase_tab_space(line);
	__get_info(new_location.loc, line);
	__erase_tab_space(line);
	if (line.empty() && !fs.eof())
		__get_line(fs, line);
	__erase_tab_space(line);
	if (line.empty() || line.front() != '{')
		return (__error_file_notif(_line_read, "missing '{'"));
	while (!fs.eof())
	{
		__get_line(fs, line);
		__erase_comment(line);
		__erase_tab_space(line);
		if (!line.compare(0, 5, "root:"))
			__add_to<std::string>(new_location.root, line.erase(0, line.find(':') + 1));
		else if (!line.compare(0, 18, "directory-browser:"))
		{
			std::string second_arg;
			line.erase(0, line.find(':') + 1);
			__add_to(second_arg, line);
			if (! second_arg.compare(0, 3, "on"))
				_SC_DIRACTIVATE(new_location);
			else if (! second_arg.compare(0, 4, "off"))
				_SC_DIROFF(new_location);
			else
				__error_file_notif(_line_read, "unknown parameter");
		}
		else if (!line.compare(0, 18, "post-directory:"))
		{
			line.erase(0, line.find(':') + 1);
			__erase_tab_space(line);
			__get_info(new_location.post_dir, line);
		}
		else if (!line.compare(0, 4, "html"))
			__parse_html(fs, line.erase(0,4), new_location);
		// else if (!line.compare(0, 4, "cgi:"))
		// {
		// 	std::string frst;
		// 	std::string scnd;
			
		// 	line.erase(0, line.find(':') + 1);
		// 	__erase_tab_space(line);
		// 	__get_info(frst, line);
		// 	__erase_tab_space(line);
		// 	__get_info(scnd, line);
		// 	__erase_tab_space(line);
		// 	new_location.cgi.push_back(make_pair(frst,scnd));
		// 	if (!line.empty())
		// 		__error_file_notif(_line_read, "lastest arguments are ignored");
		// }
		else if (!line.compare(0, 6, "index:"))
		{
			line.erase(0, line.find(':') + 1);
			__erase_tab_space(line);
			while (!line.empty())
			{
				std::string temp;
				__get_info(temp, line);
				new_location.index.push_back(temp);
				__erase_tab_space(line);
			}
		}
		else if (!line.compare(0, 1, "}"))
			break ;
		else
			__error_file_notif(_line_read, "unknown parameter");
	}
	if (fs.eof() && (line.empty() || line.compare(0, 1, "}")))
		return (__error_file_notif(_line_read, "missing '}' for server"));
	line.erase(0,1);
	if (!line.empty())
		__error_file_notif(_line_read, "line ignored after '}'");
	sc.location.push_back(new_location);
}

void Conf::__parse_cgi(std::ifstream &fs, std::string &line, __server_conf& sc)
{
	__cgi new_cgi;

	// new_location.methods = 0;
	// new_location.options = 0;
	// new_location.body_limits = 0;
	// new_location.body_min_size = 0;
	
	//_SC_DIRACTIVATE(new_location);

	__erase_tab_space(line);
	__get_info(new_cgi.loc, line);
	__erase_tab_space(line);
	if (line.empty() && !fs.eof())
		__get_line(fs, line);
	__erase_tab_space(line);
	if (line.empty() || line.front() != '{')
		return (__error_file_notif(_line_read, "missing '{'"));
	while (!fs.eof())
	{
		__get_line(fs, line);
		__erase_comment(line);
		__erase_tab_space(line);
		// if (!line.compare(0, 5, "root:"))
		// 	__add_to<std::string>(new_location.root, line.erase(0, line.find(':') + 1));
		// else if (!line.compare(0, 18, "directory-browser:"))
		// {
		// 	std::string second_arg;
		// 	line.erase(0, line.find(':') + 1);
		// 	__add_to(second_arg, line);
		// 	if (! second_arg.compare(0, 3, "on"))
		// 		_SC_DIRACTIVATE(new_location);
		// 	else if (! second_arg.compare(0, 4, "off"))
		// 		_SC_DIROFF(new_location);
		// 	else
		// 		__error_file_notif(_line_read, "unknown parameter");
		// }
		// else if (!line.compare(0, 18, "post-directory:"))
		// {
		// 	line.erase(0, line.find(':') + 1);
		// 	__erase_tab_space(line);
		// 	__get_info(new_location.post_dir, line);
		// }
		if (!line.compare(0, 4, "html"))
			__parse_html(fs, line.erase(0,4), new_cgi);
		else if (!line.compare(0, 9, "cgi-path:"))
			__add_to<std::string>(new_cgi.cgi_path, line.erase(0, line.find(':') + 1));
		// else if (!line.compare(0, 4, "cgi:"))
		// {
		// 	std::string frst;
		// 	std::string scnd;
			
		// 	line.erase(0, line.find(':') + 1);
		// 	__erase_tab_space(line);
		// 	__get_info(frst, line);
		// 	__erase_tab_space(line);
		// 	__get_info(scnd, line);
		// 	__erase_tab_space(line);
		// 	new_cgi.cgi.push_back(make_pair(frst,scnd));
		// 	if (!line.empty())
		// 		__error_file_notif(_line_read, "lastest arguments are ignored");
		// }
		// else if (!line.compare(0, 6, "index:"))
		// {
		// 	line.erase(0, line.find(':') + 1);
		// 	__erase_tab_space(line);
		// 	while (!line.empty())
		// 	{
		// 		std::string temp;
		// 		__get_info(temp, line);
		// 		new_location.index.push_back(temp);
		// 		__erase_tab_space(line);
		// 	}
		// }
		else if (!line.compare(0, 1, "}"))
			break ;
		else
			__error_file_notif(_line_read, "unknown parameter");
	}
	if (fs.eof() && (line.empty() || line.compare(0, 1, "}")))
		return (__error_file_notif(_line_read, "missing '}' for server"));
	line.erase(0,1);
	if (!line.empty())
		__error_file_notif(_line_read, "line ignored after '}'");
	sc.cgi.push_back(new_cgi);
}

template <class T>
void	Conf::__parse_html(std::ifstream &fs, std::string& line, T& loc)
{
	__erase_tab_space(line);
	if (line.empty() && !fs.eof())
		__get_line(fs, line);
	__erase_tab_space(line);
	if (line.empty() || line.front() != '{')
		return (__error_file_notif(_line_read, "missing '{'"));
	while (!fs.eof())
	{
		__get_line(fs, line);
		__erase_comment(line);
		__erase_tab_space(line);
		if (line.empty())
			continue;
		else if (!line.compare(0, 8, "methods:"))
		{
			line.erase(0, line.find(':') + 1);
			__erase_tab_space(line);
			while (!line.empty())
			{
				if (!line.compare(0, 3, "GET"))
					loc.methods = (loc.methods | (1 << 0));
				else if (!line.compare(0, 4, "POST"))
					loc.methods = (loc.methods | (1 << 1));
				else if (!line.compare(0, 6, "DELETE"))
					loc.methods = (loc.methods | (1 << 2));
				else if (!line.compare(0, 3, "PUT"))
					loc.methods = (loc.methods | (1 << 3));
				else if (!line.compare(0, 4, "HEAD"))
					loc.methods = (loc.methods | (1 << 4));
				else
					__error_file_notif(_line_read, "unknown method");
				__erase_word(line);
				__erase_tab_space(line);
			}
		}
		else if (!line.compare(0, 16, "body-size-limit:"))
			__add_to<int>(loc.body_limits, line.erase(0, line.find(':') + 1));
		else if (!line.compare(0, 14, "body-min-size:"))
			__add_to<int>(loc.body_min_size, line.erase(0, line.find(':') + 1));
		else if (!line.compare(0, 1, "}"))
			break ;
		else
			__error_file_notif(_line_read, "unknown parameter");
	}
}

template<class T>
void	Conf::__add_to(T& to, std::string& s)
{
	T temp;

	// Checking if there is an argument
	__erase_tab_space(s);
	if (s.empty())
		return (__error_file_notif(_line_read, "parameter without arguments"));
	//Extract the info, may throw
	try
	{
		__get_info(temp, s); //petit probleme si int plus grand que le nombre de port max
	}
	catch (std::invalid_argument e)
	{
		return (__error_file_notif(_line_read, e.what()));
	}
	catch (std::out_of_range e)
	{
		return (__error_file_notif(_line_read, e.what()));
	}
	catch (std::exception e)
	{
		return (__error_file_notif(_line_read, e.what()));
	}
	// Checking if the good number of argument is given
	__erase_tab_space(s);
	if (!s.empty())
		return (__error_file_notif(_line_read, "too much arguments"));
	to = temp;
}

/* 
	Transform the info into the unsigned int pointed by c
	the used caracter are erased from input string
*/
void	Conf::__get_info(unsigned int &c, std::string& raw)
{
	size_t	size;

	c = std::stoi(raw, &size); //may throw (when int is bigger than INT_MAX)
	raw.erase(0, size);
}

/* 
	Transform the info into the int pointed by c
	the used caracter are erased from input string
*/
void	Conf::__get_info(int &c, std::string& raw)
{
	size_t	size;

	c = std::stoi(raw, &size); //may throw (when int is bigger than INT_MAX)
	raw.erase(0, size);
}

/* 
	Extract the info in string type
	the used caracters are erased from input string
*/
void	Conf::__get_info(std::string &c, std::string& raw)
{
	c = raw;
	__erase_from_char(__erase_from_char(c, ' '), '\t');
	raw.erase(0, c.length());
}

/*
	Print in stderr the error message and the line of the config file where the error occures
*/
void	Conf::__error_file_notif(const int line, const std::string& error) const
{
	std::cerr << "line " << line << ": " << error << std::endl;
}

/*
	Erasing all the comment section of the line
*/
std::string&	Conf::__erase_comment(std::string& s) const
{
	return (__erase_from_char(s, '#'));
}

/*
	Erasing all the string after the caracter c
*/
std::string&	Conf::__erase_from_char(std::string& s, char c) const
{
	return (s.erase(std::min(s.find(c), s.length()), std::string::npos));
}

/*
	Erasing all the space and tab at the begginig of the line
*/
std::string::iterator	Conf::__erase_tab_space(std::string& s) const
{
	std::string::iterator it;

	for (it = s.begin(); it != s.end(); it++)
			if (*it != ' ' && *it != '\t')
				break;
	return (s.erase(s.begin(), it)); //what happens if erase(begin(),begin())
}

/*
	Erasing the first word of the line
*/
std::string&	Conf::__erase_word(std::string& s) const
{
	int f_space = s.find(' ');
	int f_tab = s.find('\t');

	int f_erase = f_space == -1 ? f_tab : f_space;
	f_erase = f_tab == -1 ? f_erase : std::min(f_erase, f_tab); // all four condiitions are treated

	s.erase(0,f_erase);
	return (s);
}

/* Same as getline but incrementing current line index */
void	Conf::__get_line(std::ifstream &fs, std::string& line)
{
	_line_read++;
	try
	{
		std::getline(fs, line);
	}
	catch(const std::exception& e)
	{
		;
	}
}

/*
	Verbose printing all the info we get from the configuration file
*/
void	Conf::__print_everything() const
{
	std::cout << "Configuration file parsing" << std::endl;
	std::cout << "Max connexion authorised - " << this->_max_connexion << std::endl;
	if (this->_default_error_root.empty())
		std::cout << "No default root for log error initialised" << std::endl;
	else
		std::cout << "Default root for log errors - " << this->_default_error_root << std::endl;
	for (std::vector<__server_conf>::const_iterator it = _sc.begin(); it != _sc.end(); it++)
	{
		std::cout << "Server : " << it->server_name << std::endl;
		std::cout << "	Port - " << it->port << std::endl;
		std::cout << "	Host - ";
		for (std::vector<std::string>::const_iterator c_it = it->host.begin(); c_it != it->host.end(); c_it++)
			std::cout << *c_it << " ";
		std::cout << std::endl;
		std::cout << "	Root - " << it->root << std::endl;
		if (it->default_error_root.empty())
			std::cout << "	No default root for log error initialised" << std::endl;
		else
			std::cout << "	Default root for log errors - " << it->default_error_root << std::endl;
		std::cout << "	Index - ";
		for (std::vector<std::string>::const_iterator c_it = it->index.begin(); c_it != it->index.end(); c_it++)
				std::cout << *c_it << " ";
		std::cout << std::endl;
		std::cout << "Locations : " << std::endl;
		for (std::vector<__location>::const_iterator c_it = it->location.begin(); c_it != it->location.end(); c_it++)
		{
			std::cout << "	'" << c_it->loc << "'" << std::endl;
			std::cout << "	Index - ";
			for (std::vector<std::string>::const_iterator cc_it = c_it->index.begin(); cc_it != c_it->index.end(); cc_it++)
				std::cout << *cc_it << " ";
			std::cout << std::endl;
			std::cout << "	Root - " << c_it->root << std::endl;
			std::cout << "	Body limit size (min:max) - " << c_it->body_min_size << ":" << c_it->body_limits << std::endl;
			if (!SC_DIRISACTIVE((*c_it)))
				std::cout << "	The Directory browsing is OFF" << std::endl;
			else
				std::cout << "	The Directory browsing is ON" << std::endl;
			std::cout << "	available methods : ";
			if (c_it->methods & (1 << 0))
				std::cout << "GET ";
			if (c_it->methods & (1 << 1))
				std::cout << "POST ";
			if (c_it->methods & (1 << 2))
				std::cout << "DELETE ";
			if (c_it->methods & (1 << 3))
				std::cout << "PUT ";
			if (c_it->methods & (1 << 4))
				std::cout << "HEAD ";
			if (!c_it->methods)
				std::cout << "none";
			std::cout << std::endl << std::endl;
		}
		for (std::vector<__cgi>::const_iterator c_it = it->cgi.begin(); c_it != it->cgi.end(); c_it++)
		{
			std::cout << "CGI	'" << c_it->loc << "'" << std::endl;
			std::cout << "	cgi path" << c_it->cgi_path << std::endl;
			std::cout << "	Body limit size (min:max) - " << c_it->body_min_size << ":" << c_it->body_limits << std::endl;
			std::cout << "	available methods : ";
			if (c_it->methods & (1 << 0))
				std::cout << "GET ";
			if (c_it->methods & (1 << 1))
				std::cout << "POST ";
			if (c_it->methods & (1 << 2))
				std::cout << "DELETE ";
			if (c_it->methods & (1 << 3))
				std::cout << "PUT ";
			if (c_it->methods & (1 << 4))
				std::cout << "HEAD ";
			if (!c_it->methods)
				std::cout << "none";
			std::cout << std::endl << std::endl;
		}
		std::cout << std::endl << std::endl;
	}
	std::cout << "End of Conifguration file parsing" << std::endl;
}

/*	
		Check if the extention of configuration file is valid
		File form : *.conf (defined with MACRO  CONF_EXTENTION_S_NAME in case of changing)
		note : better to put this in config structure
*/	
bool	Conf::__valide_conf_file_name(const std::string& file_name) const
{
	return (!(file_name.rfind(CONF_EXTENTION_S_NAME) == std::string::npos
		|| file_name.compare(file_name.rfind(CONF_EXTENTION_S_NAME), std::string::npos, CONF_EXTENTION_S_NAME)));
}

/*

*/
void	Conf::__check_conf_params()
{
	/*
		_max_connection - default value existe so no need to verify if initiliased
		_default_error_rooot - not used in the program so nevermind
	*/
	;
	/*
		need to check each conf of servers
	*/
	for (std::vector<__server_conf>::iterator it = _sc.begin(); it != _sc.end();)
	{
		try
		{
			__check_conf_server_params(*it);
			it++;
		}
		catch(config_validity_exception& e)
		{
			std::cerr << "Incomplete server configuration: " << e.what() << std::endl;
			_sc.erase(it);
			std::cout << "Server deleted" << std::endl;
			it = _sc.begin();
		}
		catch(const std::exception& e)
		{
			std::cerr << "Incomplete server configuration: " << e.what() << std::endl;
			_sc.erase(it);
			std::cout << "Server deleted" << std::endl;
			it = _sc.begin();
		}
	}
}

void	Conf::__check_conf_server_params(const __server_conf& server)
{
	if (server.server_name.empty())
		throw config_validity_exception(const_cast<char *>("server name missing"));
	if (server.root.empty())
		throw config_validity_exception(const_cast<char *>("need to set default root for the server"));
	if (server.port <= 0)
		throw config_validity_exception(const_cast<char *>("unvalid port value"));
	if (server.host.empty())
		throw config_validity_exception(const_cast<char *>("missing host name"));
	if (server.unactive_max_delay < 100)
		throw config_validity_exception(const_cast<char *>("unreasonble unactive max value delay"));
	for (std::vector<__location>::const_iterator c_it = server.location.begin(); c_it != server.location.end(); c_it++)
	{
		if (c_it->loc.empty())
			throw config_validity_exception(const_cast<char *>("missing location position"));
	}
	for (std::vector<__cgi>::const_iterator c_it = server.cgi.begin(); c_it != server.cgi.end(); c_it++)
	{
		if (c_it->loc.empty())
			throw config_validity_exception(const_cast<char *>("missing cgi extention"));
		if (c_it->cgi_path.empty())
			throw config_validity_exception(const_cast<char *>("missing cgi path"));
	}
}