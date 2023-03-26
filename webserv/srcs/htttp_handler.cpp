#include "http_handler.hpp" 

// GLOBALS POUR LE LOL + easy init
t_errs		g_errs;
t_ret		g_ret;
t_ext		g_ext;
memelord	g_gif;
extern int	g_bs;
extern char	**environ;
// --------------------------------------------------------

/*
	delete this please
	just for testing
	Get request count
*/
// int	g_getcount = 0;








//	CLASS BUILDER ------------------------------------------------------------
void	Http_handler::__privates_init()
{
	this->_cgi_fds.first = 0;
	this->_cgi_fds.second = 0;
	this->_pid = 0;
	this->_pidwrite = 0;
	this->_valid = 0;
	this->_loc = NULL;
	this->_status = 13421342; //pour ne pas trigger le WIFEXITED
	this->header_http1		= "HTTP/1.1 ";
	this->header_content_len	= "Content-Length: ";
	this->header_content_loc	= "Content-Location: ";
	this->header_content_type	= "Content-Type: ";
	this->header_date 		= "Date: ";
	this->header_last_modif		= "Last-Modified: ";
	this->header_connect		= "Connection: ";
	this->header_server		= "Server: FT_Webserv/1.0.0";
	this->header_encoding		= "Transfer-Encoding: identity";
	this->header_location		= "Location: ";
	this->header_alternate		= "Alternates: ";
}

// CONSTRUCT
Http_handler::Http_handler(std::string &request, int &fd)
{
	// std::cout << "---------------------------------------------- REQUEST" << std::endl;

	this->_fd = fd;
	this->__privates_init();

	// Read the first line from the string stream
	std::istringstream	iss(request);
	std::string		line;

	std::getline(iss, line);

	// Split the first line into its individual components
	std::istringstream	firstLineStream(line);
	std::string			version;

	// get essential element from request 1rst line (method / address) + version to check validity
	firstLineStream >> this->_method >> this->_address >> version;

	// if url contains query data
	if (this->_address.find('?') != std::string::npos)
	{
		this->_query = this->_address.substr(this->_address.find('?'));
		this->_query.erase(0,1);
		this->_address.erase(this->_address.find('?'));
	}
 	// format addresse clean multiple '/' possible
	// and interpret %hex_value to ascii
	this->__clean_address();
	this->_req_dict.insert(std::make_pair(this->_method, this->_address));
	
	// std::cout << line << std::endl; // <------------------------------------cout
	
	//build dico of http fields
	while (std::getline(iss, line))
	{
		// Extract the field name and value from each line
		std::size_t	colonPos = line.find(':');
		if (colonPos != std::string::npos)
		{
			std::string field = line.substr(0, colonPos);
			std::string value = line.substr(colonPos + 1);
			
			// std::cout << line << std::endl; // <------------------------------------cout
			
			// clean '\r'
			// erase first space after ':' in line
			// and finaly check if the field is already present if double => field 400 http_error
			if (!value.empty() && value.back() == '\r')
				value.pop_back();
			if (value[0] == ' ')
				value = value.substr(1);
			if (this->_req_dict.find(field) != this->_req_dict.end())
			{
				this->_valid = 400;
				return;
			}

			// add value
			this->_req_dict.insert(std::make_pair(field, value));
		}
		// if no ':' in line check if end of the header or an invalid header
		else
		{
			for (size_t i = 0; i < line.length(); i++)
			{
				if (line[i] != '\r' && line[i] != '\n')
				{
					this->_valid = 400;
					return ;
				}
			}
			break;
		}
	}

	// last checks :
	// if there is Host field
	// if method is a valid method
	// and if version is the correct one
	if ( (this->_method.empty() || this->__not_a_method()) 
		|| (this->_req_dict.find("Host") == this->_req_dict.end()
			&& this->_req_dict.find("host") == this->_req_dict.end()) )
		this->_valid = 400;
	else if (version.compare("HTTP/1.1"))
		this->_valid = 505;
}

// add body to the dico, by receiving only the body
void	Http_handler::add_body(const std::string &body)
{
	if (!body.empty())
		this->_req_dict.insert(std::make_pair("BODY", body));
	// std::cout << "======>" << this->_req_dict.find("BODY")->second.length() << std::endl;
}

// add body to the dico from the full request
void	Http_handler::load_body(std::string &request)
{
	size_t	pos = request.find("\r\n\r\n");
	if (pos + 4 >= request.length())
		return;

	// Extract the body from the request
	this->_req_dict.insert(std::make_pair("BODY", request.substr(pos + 4)));
	// std::cout << "======>" << this->_req_dict.find("BODY")->second.length() << std::endl;
}

bool	Http_handler::valid_header(std::string first_line)
{
	// Split the first line into its individual components
	std::istringstream	firstLineStream(first_line);

	std::string		method;
	std::string		address;
	std::string		version;

	firstLineStream >> method >> address >> version;
	
	if (method.empty() || __not_a_method(method))
		return false;
	if (address.empty() || address.find(this->_req_dict.find("Host")->second) == std::string::npos)
		return false;
	if (version.empty() || version.compare("HTTP/1.1"))
		return false;

	return true;
}

void	Http_handler::__inside_request_checker(std::string &actual_body, std::vector<std::string> &vect)
{
	if (!valid_header(actual_body.substr(0, actual_body.find('\n'))))
		return;

	size_t	pos = actual_body.find("\r\n\r\n");
	if (pos + 4 >= actual_body.length())
		return;

	vect.push_back(actual_body.substr(0, pos + 4));
}

std::pair<bool, std::vector<std::string> >	Http_handler::body_inspector()
{
	dico::iterator	ite = this->_req_dict.find("BODY");
	if (ite == this->_req_dict.end() || ite->second.length() > 10000)
		return std::make_pair<bool, std::vector<std::string> >(false, std::vector<std::string>());

	std::string		body(ite->second);
	std::vector<Header>	headers;

	std::regex pattern("(GET|POST|PUT|DELETE|HEAD|CONNECT|OPTIONS|TRACE|PATCH) .+?\\r\\n(.+?\\r\\n)*\\r\\n");
	std::sregex_iterator	it(body.begin(), body.end(), pattern);

	std::sregex_iterator	end;

	for (; it != end; ++it) {
		Header	header;
		header.start_pos = it->position();
		header.end_pos = it->position() + it->length() - 1;
		header.content = it->str();
		headers.push_back(header);
	}

	std::vector<std::string>	res;

	for (std::vector<Header>::iterator Hit = headers.begin(); Hit != headers.end(); Hit++)
	{
		res.push_back(Hit->content);
	}

	if (headers.size() <= 1)
		return std::make_pair<bool, std::vector<std::string> >(false, std::vector<std::string>());

	return std::make_pair<bool, std::vector<std::string> >(true, std::vector<std::string>(res));
}

void	Http_handler::pipelined_body_destroy()
{
	dico::iterator	ite = this->_req_dict.find("BODY");
	if (ite == this->_req_dict.end())
		return;
	size_t	pos = ite->second.find("\r\n\r\n");
	ite->second = ite->second.substr(pos);
}

// format addresse clean multiple '/' possible
// and interpret '%hex_value' to ascii
void	Http_handler::__clean_address()
{
	// format addresse clean multiple '/' possible
	size_t pos = this->_address.find("://");
	if (pos != std::string::npos)
	{
		this->_address = this->_address.substr(pos + 3);
		this->_address = this->_address.substr(this->_address.find('/'));
	}
	if (!this->_address.compare("/"))
	{
		int i = this->_address.length() - 1; 
		while (i > 0 && this->_address[i] == '/' && this->_address[i - 1] == '/')
		{
			this->_address.erase(i);
			i--;
		}
	}
	
	// and interpret '%hex_value' to ascii
	std::stringstream ss;
	for (std::string::iterator it = this->_address.begin(); it != this->_address.end(); ++it)
	{
		if (*it == '%')
		{
			// This character is the start of a URL-encoded sequence.
			// Get the next two characters and interpret them as a hexadecimal number.
			std::string hex_str = "0x" + std::string(it + 1, it + 3);
			int value;
			ss << std::hex << hex_str;
			ss >> value;
			// Replace the URL-encoded sequence with the corresponding character.
			*it = static_cast<char>(value);
			// Erase the next two characters from the string.
			this->_address.erase(it + 1, it + 3);
			// Increment the iterator past the two characters that were erased.
			it += 2;
			// Clear the error flags on the stringstream, but don't reset it.
			ss.clear();
		}
	}
}
//-----------------------------------------------------------------------------------------











// CHECKER ---------------------------------------------------------------------------
//check from the server associated with the request if the method is authorized at this address
// and check if address is valid at the same time
int	Http_handler::unauthorized_method(Server &serv)
{
	int ret = __path_evaluation(serv);
	if (ret)
		return ret;

	if (!this->_method.compare("GET"))
	{
		if (!SV_GETISSET(this->_loc))
			return 405;
	}
	else if (!this->_method.compare("POST"))
	{
		if (!SV_POSTISSET(this->_loc))	
			return 405;
	}
	else if (!this->_method.compare("DELETE"))
	{
		if (!SV_DELETEISSET(this->_loc))
			return 405;
	}
	else if (!this->_method.compare("HEAD"))
	{
		if (!SV_HEADISSET(this->_loc))
			return 405;
	}
	else if (!this->_method.compare("PUT"))
	{
		if (!SV_PUTISSET(this->_loc))
			return 405;
	}

	return 0;
}

bool	Http_handler::__index_path_handler(std::string &request_loc)
{
	struct stat file_stat;

	for (std::vector<std::string>::iterator it = this->_loc->index.begin();
		it != this->_loc->index.end(); it++)
	{
		// does index exists ?
		if (stat((request_loc + *it).c_str(), &file_stat) == 0)
		{
			std::ifstream	file;
			file.open(request_loc + *it, std::ios::in);
			if (!file.is_open())
				throw 500;

			std::stringstream	buffer;
			buffer << file.rdbuf();
			file.close();
			this->_response = buffer.str();
			this->header_content_type += g_ext.get_type(__get_extension(request_loc + *it));

			return (true);
		}
	}

	return (false);
}

// build the location in server (this->_target)
// according to server->root
int	Http_handler::__path_evaluation(Server &serv)
{
	this->_serv = &serv;
	std::string	conf_location;
	struct stat	path_stat;

	for (	std::vector<__location>::iterator it = serv._location.begin();
			it != serv._location.end();
			it++)
	{
		if (this->_address.compare(0, it->loc.length(), it->loc) == 0)// != std::string::npos) //pas find mais compare
		{
			if (conf_location.empty() || it->loc.length() > conf_location.length())
			{
				conf_location = it->loc;
				this->_loc = &(*it);
			}
		}
	}


	if (this->_loc == NULL)
		return 404;

	if (this->_loc->root.empty())
		this->_subroot = serv._root;
	else
	{
		this->_subroot = this->_loc->root;
		this->_address = this->_address.substr(this->_loc->loc.length());
	}
	
	if (this->_address[0] != '/')
		this->_address = "/" + this->_address;
	if (this->_subroot[this->_subroot.length() - 1] != '/')
		this->_subroot += "/";

	this->_target = this->_subroot + &this->_address[1];
	
	/*
		If the target is a directory, we check if there is a corresponding index file that exist
			--
		Note: This way we can execute the file as a cgi in the next step
	*/
	
	if (stat(this->_target.c_str(), &path_stat) != 0)
	{
		// If it s a POST or PUT request AND the directory from address (get back to last '/' in address)
		// doesnt exists neither => return 404
		// else evaluate in header field accept if ressource is present
		if (!this->_method.compare("POST") || !this->_method.compare("PUT"))
		{
			std::string	parent_directory =
						this->_target.substr(0, this->_target.find_last_of("/"));
			// std::cout << parent_directory << "<<<<<<<<<<" << std::endl;
			if (stat(parent_directory.c_str(), &path_stat) != 0)
				return 404;
		}
		else
		{
			int ret = __this_is_the_way();
			// std::cout << "the ret of this is the way is : " << ret << std::endl;
			if (ret)
				return ret;
		}
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		struct stat file_stat;

		if (*(this->_target.rbegin()) != '/') // check si target en fin de caractere a '/';
			this->_target += '/';
		for (std::vector<std::string>::iterator it = this->_loc->index.begin();
			it != this->_loc->index.end(); it++)
		{
			if (stat((this->_target + *it).c_str(), &file_stat) == 0)
			{
				this->_target += *it;
				break ;
			}
		}
	}

	/*
		To be selected as the location, CGI should correspond to this behaviours :
			- have the corresponding extention or file name as th adress
			- have authorised method for the requested method

		Ici on check dans le vector du cgi si 
			- l'extention du fichier correspond a celui du cgi
			- la methode utilisé correspond a une methode authorisé du cgi
		Si un tel cgi correspond aux criteres il sera selctionné pour etre la prochaine location
	
	*/
	for (	std::vector<__cgi>::iterator it = serv._cgi.begin();
			it != serv._cgi.end();
			it++)
	{
		if ( ! it->loc.compare(__get_extension(this->_target))) //ici changer la fonction de compare wildcard
		{
			if (!this->_method.compare("GET"))
			{
				if (!SV_GETISSET(it))
					continue ;
			}
			else if (!this->_method.compare("POST"))
			{
				if (!SV_POSTISSET(it))	
					continue ;
			}
			else if (!this->_method.compare("DELETE"))
			{
				if (!SV_DELETEISSET(it))
					continue ;
			}
			else if (!this->_method.compare("HEAD"))
			{
				if (!SV_HEADISSET(it))
					continue ;
			}
			else if (!this->_method.compare("PUT"))
			{
				if (!SV_PUTISSET(it))
					continue ;
			}
			this->_loc = &(*it);
			break ;
		}
	}
	return 0;
}

bool	Http_handler::__not_a_method()
{
	if (this->_method.compare("GET")
		&& this->_method.compare("POST")
		&& this->_method.compare("DELETE")
		&& this->_method.compare("HEAD")
		&& this->_method.compare("PUT")
		&& this->_method.compare("CONNECT")
		&& this->_method.compare("OPTIONS")
		&& this->_method.compare("TRACE")
		&& this->_method.compare("PATCH") )
		return (true);

	return (false);
}

bool	Http_handler::__not_a_method(std::string &method)
{
	if (method.compare("GET")
		&& method.compare("POST")
		&& method.compare("DELETE")
		&& method.compare("HEAD")
		&& method.compare("PUT")
		&& method.compare("CONNECT")
		&& method.compare("OPTIONS")
		&& method.compare("TRACE")
		&& method.compare("PATCH") )
		return (true);

	return (false);
}

bool Http_handler::__is_valid_http_time(const std::string &s)
{
	static const char *date_format = "%a, %d %b %Y %H:%M:%S %Z";

	struct tm tm;
	std::memset(&tm, 0, sizeof(tm));

	if (strptime(s.c_str(), date_format, &tm) == nullptr)
		return false;

	// Check if the resulting time is valid
	time_t t = mktime(&tm);
	if (t == -1)
		return false;

	return true;
}

// if this->_address incomplete
// Accept field evaluation to find possible address
int	Http_handler::__this_is_the_way()
{
	std::string	path;
	std::string	directory;
	struct stat file_stat;
	
	directory = this->_target.substr(0, this->_target.find_last_of('/'));
	if (stat(directory.c_str(), &file_stat) != 0
		|| !S_ISDIR(file_stat.st_mode))
		return 404;

	// Si il y'a field accept dans la requete
	if (this->_req_dict.find("Accept-Encoding") != this->_req_dict.end()
		|| this->_req_dict.find("Accept") != this->_req_dict.end())
	{
		std::string	vals;
		if (this->_req_dict.find("Accept") != this->_req_dict.end())
			vals = this->_req_dict.find("Accept")->second;
		else if (this->_req_dict.find("Accept-Encoding") != this->_req_dict.end())
			vals = this->_req_dict.find("Accept-Encoding")->second;

		// faux pas pousser meme dans les orties
		if (!vals.compare("*/*"))
			return 404;

		// Accept Parsing --------
		// multimap [(float)q=x.y] -> std::string (val)
		std::vector<std::string>		accept_field_pairs = __cpp_split(vals, ',');
		std::multimap<float, std::string>	accept_vals;
		
		for (std::vector<std::string>::iterator it = accept_field_pairs.begin();
				it != accept_field_pairs.end(); it++)
		{
			int	sep_pos = it->find(';');
			size_t	q_pos;			

			
			if ( (q_pos = it->find("q=")) == std::string::npos)
				accept_vals.insert(std::make_pair(1.0, it->substr(0, sep_pos)));
			else
				accept_vals.insert(std::make_pair(std::stof(it->substr(q_pos + 2)), it->substr(0, sep_pos)));
		}
		// ------------------------

		// pour chaques element dans multimap tester les valeurs demandées
		// reverse iterator pour l'ordre de priorité établie par la valeur q
		float	q = 0.9;
		bool	err300 = false;
		bool	err406 = false;
		
		for (std::multimap<float, std::string>::reverse_iterator it = accept_vals.rbegin();
				it != accept_vals.rend(); it++)
		{

			if ((!it->second.compare("compress") && !it->first)
				|| (!it->second.compare("gzip") && !it->first))
			{
				if (err406)
					return 406;
				err406 = true;
			}

			int	slash_pos = it->second.find('/');
			if (it->second[slash_pos + 1] == '*')
			{
    				DIR		*dir = opendir(directory.c_str());
				std::string	valid_ext;
				
				// verifie l'ensemble des fichiers présent dans le répertoire si il sont du type demandé (image / video / application / texte)
				for (struct dirent *dirEntry = readdir(dir); dirEntry; dirEntry = readdir(dir))
				{
					// si match
					if (g_ext.get_type(__get_extension(dirEntry->d_name))
						.find(it->second.substr(0, slash_pos)) != std::string::npos)
					{
						// si valid_ext (valid extension) not empty throw 300 multiple choice
						if (!valid_ext.empty())
							err300 = true;
						// else valid_ext = extension du fichier matched
						valid_ext = "." + __get_extension(dirEntry->d_name);
						this->header_alternate += g_ext.get_type(&valid_ext[1]) + "; q=" + std::to_string(q) + " , ";
						if (q > 0.1)
							q -= 0.1;
					}
				}
				closedir(dir);
				if (err300)
				{
					this->header_alternate.erase(this->header_alternate.end() - 3, this->header_alternate.end());
					return 300;
				}
				// q determine l'ordre de priorité si un fichier a été trouvé
				// pas besoin de check autre possibilitées
				if (!valid_ext.empty())
				{
					path = this->_address + valid_ext;
					break;
				}
			} // if wildcard

			else
			{
				if (!path.empty())
					break;

				// tmp_root + path request + . + extension du accept
				std::string	new_path = this->_target + "." + it->second.substr(slash_pos + 1);

				if (stat(new_path.c_str(), &file_stat) == 0)
					path = this->_address + "." + it->second.substr(slash_pos + 1);
			} // if not a wildcard

		}

		if (path.empty())
			return 404;
		this->_address = path;
		this->_target = this->_subroot + &this->_address[1];

		return 0;
	} // if accept field
	else
		return 404;
}
// -----------------------------------------------------------------------------------











// METHOD EXEC -----------------------------------------------------------------------
// dispatch to requested method
std::string	Http_handler::exec_request()
{
	try
	{
		// NOT TREATED METHODS
		if (!this->_method.compare("OPTIONS")
				|| !this->_method.compare("PATCH") || !this->_method.compare("TRACE")
				|| !this->_method.compare("CONNECT") || !this->_method.compare("PATCH"))
			throw 405;

		// BAD REQUEST NO METHOD OR BS METHOD
		if (this->_method.compare("GET") && this->_method.compare("HEAD")
			&& this->_method.compare("POST") && this->_method.compare("DELETE")
			&& this->_method.compare("PUT"))
			throw 400;

		// GET METHOD / HEAD METHOD
		if (!this->_method.compare("GET") || !this->_method.compare("HEAD"))
		{
			if ( (!this->_method.compare("GET") && !SV_GETISSET(this->_loc))
				|| (!this->_method.compare("HEAD") && !SV_HEADISSET(this->_loc)))
				throw 405;
	
			__Etag_gen(this->_target);

			std::map<std::string, std::string>::iterator	it;
			it = this->_req_dict.find("ETag");
			if (it != this->_req_dict.end())
				__Etag_reader(it->second);

			it = this->_req_dict.find("If-Match");
			if (it != this->_req_dict.end())
				__Etag_reader(it->second);

			it = this->_req_dict.find("If-Modified-Since");
			if (it != this->_req_dict.end())
				__condition_header(this->_target, MODIFIED_SINCE);

			if (! this->_loc->cgi_path.empty())
			{
				__CGI_exec(this->_loc->cgi_path); //oter argument de la fonction
				return std::string();
			}

			// Get the file requested
			this->__GET_response();
			
			// if range in http header
			// cut response accordingly
			// else return normally
			it = this->_req_dict.find("Range");
			if (it != this->_req_dict.end())
			{
				__range_cut(it->second);
				this->__200_response(206);
			}
			else
				this->__200_response(200);
		}

		// POST_METHOD
		else if (!this->_method.compare("POST"))
		{
			if (! this->_loc->cgi_path.empty())
			{
				__CGI_exec(this->_loc->cgi_path);
				return std::string();
			}
			else
			{
				int ret = this->__POST_response();
				this->__200_response(ret);
			}
		}

		else if (!this->_method.compare("PUT"))
		{
			if (!SV_PUTISSET(this->_loc))
				throw 405;
			int ret = this->__PUT_response();
			this->__200_response(ret);
		}

		// DELETE_METHOD
		else if (!this->_method.compare("DELETE"))
		{
			if (!SV_DELETEISSET(this->_loc))
				throw 405;

			this->__DELETE_response();
			this->__200_response(204);
		}
	}

	catch (int e) {
		__err_header(e);
	}

	return (this->_response);
}

void	Http_handler::__GET_response(void)
{
	// std::cout << ++g_getcount << std::endl;
	// HOME ----------------------------------------------------------------	
	// Si l'adresse est home -> '/' et browse inactive look dans config files les index
	if  (!this->_target.compare("/") && !SV_DIRISACTIVE(this->_loc))
	{
		if (__index_path_handler(this->_subroot))
			return;

		// if no index found on '/'
		// then internal error should at least have something on '/'
		throw 500;
	}

	// QUELQUE PART DANS LE SITE --------------------------------------------------
	std::ifstream	file;
	struct stat		path_stat;

	// Si l'adresse est home -> '/' ou autoindex
	// et browse active then return directory browser
	if (!this->_address.compare("/autoindex") || !this->_target.compare("/"))
	{
		if (stat(this->_subroot.c_str(), &path_stat) != 0)
			throw 500;
		return __browse(this->_subroot);
	}

	// if requested path is binary type
	else if (g_ext.get_category(this->_target, this->__get_extension()) == BIN)
	{
		// path already checked just need to init path_stat
		// if invalid result => internal error on previous checks
		if (stat(this->_target.c_str(), &path_stat) != 0)
			throw 500;

  		// if is a directory
		if (S_ISDIR(path_stat.st_mode))
		{
			// if is a directory and address doesn't finish with /
			// redirect on same address but with a '/'
			// (bs tester)
			if (this->_address[this->_address.length() - 1] != '/')
				throw 301;

			// if there is an index files on this directory
			// index file take priority
			if (__index_path_handler(this->_target))
				return; 
			
			// if directory browser active return directory browser val
			// else 404
			else if (SV_DIRISACTIVE(this->_loc))
				return __browse(this->_target);
			else if (!SV_DIRISACTIVE(this->_loc))
				throw 404;
		}
	}
	__get_file_content(file, this->_target);
}

// get content into this->_response (and close file)
void	Http_handler::__response_init(std::ifstream &file)
{
	std::stringstream	buffer;
	buffer << file.rdbuf();
	file.close();
	this->_response = buffer.str();
}

void	Http_handler::__get_file_content(std::ifstream &file, std::string request_loc)
{
	file.open(request_loc);
	if (!file.is_open())
		throw 500;

	__response_init(file);
}

// PUT request exec
int	Http_handler::__PUT_response()
{
	int	ret;
	struct stat	path_stat;

	// if file doesn't exist return 201 created
	// else return 204 no content (request accepted executed and no body to return)
	if (stat(this->_target.c_str(), &path_stat) != 0)
		ret = 201;
	else
		ret = 204;

	// if no body return 400 bad request
	if (this->_req_dict.find("BODY") == this->_req_dict.end()
		|| this->_req_dict.find("BODY")->second.empty())
		throw 400;

	// create or update file requested
	std::ofstream	file(this->_target, std::ios::out);
	if (!file.is_open())
		throw 500;
	file << this->_req_dict.find("BODY")->second;
	file.close();

	return ret;
}

// POST request exec
int	Http_handler::__POST_response()
{
	int			ret = 0;
	struct stat	path_stat;

	// if not on cgi and no body return 204
	// request received and useless but ok bro 
	if (this->_req_dict.find("BODY") == this->_req_dict.end()
		|| this->_req_dict.find("BODY")->second.empty())
		return (204);

	if (stat(this->_target.c_str(), &path_stat) != 0)
		ret = 201; // if this->_tag
	else if (S_ISDIR(path_stat.st_mode))
	{
		bool	updated = false;
		DIR	*dir = opendir(this->_target.c_str());
		std::vector<__cgi>::iterator it;

		for (struct dirent *dirEntry = readdir(dir); dirEntry; dirEntry = readdir(dir))
		{
			for (it = this->_serv->_cgi.begin();
				it != this->_serv->_cgi.end(); it++)
			{
				if (!it->loc.compare(__get_extension(dirEntry->d_name)))
				{
					if (updated)
					{
						closedir(dir);
						return 403;
					}
					this->_target += dirEntry->d_name;
					updated = true;
				}
			}
		}
		closedir(dir);
		if (!updated)
			return 204;
		else
			ret = 202;
	}

	if ( (this->_req_dict.find("Content-Length") == this->_req_dict.end()
			&& (this->_req_dict.find("Transfer-Encoding")->second.find("chunked") == std::string::npos
				&& this->_req_dict.find("Transfer-Encoding")->second.find("Chunked") == std::string::npos))
		|| this->_req_dict.find("Content-Type") == this->_req_dict.end())
		throw 411;

	if (this->_req_dict.find("Content-Type")->second.find("multipart/form-data")
			!= std::string::npos)
		throw 400;

// CHECK CGI SHIT OR UPDATE FILE
	std::fstream	file(this->_target);
	if (!file.is_open())
		throw 500;
	file << this->_req_dict.find("BODY")->second;
	file.close();

	return (ret);
}

void	Http_handler::__DELETE_response()
{
	struct stat path_stat;

	if (stat(this->_target.c_str(), &path_stat) != 0)
		throw 404;

	if (S_ISDIR(path_stat.st_mode))
		throw 403;

	if (remove(this->_target.c_str()))
		throw 500;
}
// -------------------------------------------------------------------------------------











// GETTERS --------------------------------------------------------------------------------
std::string	Http_handler::get_host_name() const {
	return (this->_req_dict.find("Host")->second);
}

std::string	Http_handler::get_method() const {
	return (this->_method);
}

std::string	Http_handler::get_body() const {
	dico::const_iterator	it = this->_req_dict.find("BODY");
	if (it != this->_req_dict.end())
		return (it->second);
	return (std::string());
}

std::string	Http_handler::get_alternates_path() {
	return (this->header_alternate);
}

int Http_handler::get_content_length_val()
{
	dico::const_iterator it = this->_req_dict.find("Content-Length");
	if (it != this->_req_dict.end())
	{
		int content_length = 0;
		std::stringstream ss(it->second);
		ss >> content_length;
		return content_length;
	}
	return -1;
}

int	Http_handler::invalid_request() const {
	return (this->_valid);
}

size_t	Http_handler::body_max_size() {
	return (this->_loc->body_limits);
}

std::string	Http_handler::get_connection() const
{
	std::map<std::string, std::string>::const_iterator	it = this->_req_dict.find("Connection");

	if (it != this->_req_dict.end())
		return (it->second);
	return (std::string("null"));
}

bool	Http_handler::get_keep_alive() const {
	return (this->_req_dict.find("Keep-Alive") != this->_req_dict.end());
}

int	Http_handler::keep_alive_value() const
{
	int result;
	std::map<std::string, std::string>::const_iterator	it;

	it = this->_req_dict.find("Keep_Alive");
	std::istringstream(it->second) >> result;
	if (std::istringstream(it->second).fail())
		throw 400;;

	return result;
}

int	&Http_handler::get_status() {
	return (this->_status);
}

int	Http_handler::get_cgi_pid() {
	return (this->_pid);
}

int	Http_handler::get_fd_response() {
	return this->_fd;
}

std::pair<int, int>	&Http_handler::awaiting_fd_for_writing(void) {
	return this->_cgi_fds;
}

int	Http_handler::get_pipe_to_cgi(){
	return this->_cgi_pipe;
}

std::string	&Http_handler::get_response() {
	return this->_response;
}
// -------------------------------------------------------------------------------------











// RESPONSE GEN ---------------------------------------------------------------------------
void	Http_handler::__200_response(int ret)
{
	size_t	pos;
	this->header_http1 += std::to_string(ret) + " " + g_ret[ret] + "\r\n";
	this->header_content_loc += this->_req_dict.find(this->_method)->second + "\r\n";
	this->header_date += Http_handler::get_time() + "\r\n";
	this->header_connect += "close\r\n";
	this->header_content_len += std::to_string(this->_response.length()) + "\r\n";
	
	if (!this->header_content_type.compare("Content-Type: "))
	{
		if (g_ext.get_type((this->_target), this->__get_extension()).empty())
			this->header_content_type += "text/html";
		else
			this->header_content_type += g_ext.get_type((this->_target), this->__get_extension());

		if ((pos = this->_response.find("encoding=")) != std::string::npos
			&& header_charset.empty())
		{
			std::string	tmp = this->_response.substr(pos + 10);
			std::string	charset = tmp.substr(0, tmp.find(('"')));

			for (std::string::iterator it = charset.begin(); it != charset.end(); ++it)
				*it += 32 * (*it >= 65 && *it <= 90);

			this->header_charset = "; charset=" + charset;
		}
	}
	if (!this->header_charset.empty())
		this->header_content_type += this->header_charset;

	this->_header += this->header_http1
				+ this->header_content_len
				+ this->header_content_loc
				+ this->header_content_type + "\r\n"
				+ this->header_date
				+ this->header_server + "\r\n"
				+ this->header_encoding + "\r\n";

	if ( !((get_keep_alive())
		|| (get_connection().compare("null")
			&& ((!get_connection().compare("keep-alive"))
				|| !get_connection().compare("Keep-Alive"))))) 
		this->_header += this->header_connect;

	if (!this->header_range.empty())
		this->_header += this->header_range + "\r\n";
	
	if ((pos = this->_response.find("lang=")) != std::string::npos
		&& header_language.empty())
	{
		std::string	tmp = this->_response.substr(pos + 6);
		std::string	lang = tmp.substr(0, tmp.find(('"')));
		
		this->header_language = "Content-Language: " + lang + "\r\n";
	}
	if (!this->_header.empty())
		this->_header += this->header_language;
	if (!this->header_ETag.empty())
		this->_header += this->header_ETag + "\r\n";

	if (this->_method.compare("HEAD") && !this->_response.empty())
		this->_response = this->_header + "\r\n" + this->_response;
	else
		this->_response = this->_header + "\r\n";
}

void	Http_handler::__err_header(const int ret)
{
	if (ret >= 400 && this->_response.empty())
	{
		this->__body_gen(ret);
		this->header_content_len += std::to_string(this->_response.length()) + "\r\n";
	}
	this->header_http1 += std::to_string(ret) + " " + g_errs[ret] + "\r\n";
	this->header_content_loc += this->_req_dict.find(this->_method)->second + "\r\n";
	if (!this->header_content_type.compare("Content-Type: "))
		this->header_content_type += "text/html\r\n";
	this->header_date += Http_handler::get_time() + "\r\n";
	this->header_connect += "close\r\n";
	
	this->_header += this->header_http1
				+ this->header_content_loc
				+ this->header_content_type
				+ this->header_date
				+ this->header_connect
				+ this->header_encoding + "\r\n"
				+ this->header_server + "\r\n";

	if (ret >= 400)
		this->_header += this->header_content_len;
	if (!this->header_language.empty())
		this->_header += this->header_language;
	else if (ret == 301)
	{
		this->header_location += this->_req_dict.find(this->_method)->second + "/\r\n";
		this->_header += this->header_location;
	}

	if (!this->header_ETag.empty())
		this->_header += this->header_ETag + "\r\n";

	if (ret < 400 || !this->_method.compare("HEAD"))
		this->_response = this->_header + "\r\n";
	else
		this->_response = this->_header + "\r\n"  + this->_response;
}

void	Http_handler::__body_gen(int ret)
{
	if (this->_serv->_error_default_root.empty())
		return (__default_body_gen(ret));
	
	std::fstream	file(this->_serv->_error_default_root);
	if (!file.is_open())
		return (__default_body_gen(ret));
	std::stringstream	buffer;
	buffer << file.rdbuf();
	file.close();
	this->_response += buffer.str();
}

void	Http_handler::__default_body_gen(int ret)
{
	this->_response += "<!DOCTYPE html>\r\n";
	this->_response += "<html>\r\n";
	this->_response += "	<head>\r\n";
	this->_response += "		<meta charset=\"UTF-8\">\r\n";
	this->_response += "		<title>webserv</title>\r\n";
	this->_response += "	</head>\r\n";
	this->_response += "	<body bgcolor=\"white\">\r\n";
	this->_response += "		<center><h1>" + std::to_string(ret) + " " + g_errs[ret] + "</h1></center>\r\n";
	this->_response += "		<center><hr>" + this->header_server + "</hr></center>\r\n";
	this->_response +=			g_gif[1] + "\r\n";
	this->_response += "		<center><p>Click <a href=\"/\">here</a> to return home.</p></center>\r\n";
	this->_response += "	</body>\r\n";
	this->_response += "</html>\r\n";
}
// ----------------------------------------------------------------------------------------











// CGI ----------------------------------------------------------------------------------
char	**Http_handler::__set_env()
{
	char **envp = new char*[sizeof(char*) * (env.size() + 1)];
	if (!envp)
		return NULL;
	int i = 0;
	for(std::map<std::string, std::string>::iterator it = env.begin(); it != env.end(); ++it)
	{
		envp[i] = strdup((it->first + "=" + it->second).c_str());
		++i;
	}
	envp[i] = NULL;
	return envp;
}

std::string	Http_handler::__get_ip(int client_fd)
{
	struct sockaddr_in	client_addr;
	socklen_t			addr_len = sizeof(struct sockaddr_in);
	char				ip[16];

	getsockname(client_fd, (struct sockaddr *)&client_addr, &addr_len);
	strncpy(ip, inet_ntoa(client_addr.sin_addr), 16);
	return (ip);
}

std::string	Http_handler::__get_query()
{
	unsigned long i = this->_address.find_first_of("?", 0);
	if (i == std::string::npos)
		return "";
	return this->_address.substr(i + 1, this->_address.size() - i);
}


// CGI_PART
void	Http_handler::__CGI_exec(std::string &cgi_path)
{
	int	readingPipe[2];
	int	writingPipe[2];
	int	errPipe[2];

	if (pipe(readingPipe) == -1 
	|| pipe(errPipe) == -1
	|| pipe(writingPipe) == -1)
		throw 500;
	// ----------------------------------------------------------
	dico::iterator	it = this->_req_dict.find("BODY");

	// FORK PROCESS
	pid_t pid = fork();
	if (pid == -1)
		throw 500;
	// CHILD
	else if (pid == 0)
	{
		if(this->_req_dict.find("X-Secret-Header-For-Test") != this->_req_dict.end())
		{
			env["HTTP_X_SECRET_HEADER_FOR_TEST"] = "1";
		}
		if (! this->_method.compare("POST"))
		{
			if (it != this->_req_dict.end())
				env["CONTENT_LENGTH"] = std::to_string(it->second.length());
			else
				env["CONTENT_LENGTH"] = "0";
		}
		dup2(writingPipe[0], STDIN_FILENO);
		dup2(readingPipe[1], STDOUT_FILENO);
		dup2(errPipe[1], STDERR_FILENO);

		close(readingPipe[0]);
		close(readingPipe[1]);
		close(writingPipe[0]);
		close(writingPipe[1]);
		close(errPipe[0]);
		close(errPipe[1]);
		

		env["AUTH_TYPE"] = "";
		env["CONTENT_TYPE"] = this->_req_dict.find("Content-Type")->second;
		env["GATEWAY_INTERFACE"] = "CGI/1.1";
		env["PATH_INFO"] = this->_address;
		env["PATH_TRANSLATED"] = this->_target;
		env["QUERY_STRING"] = this->_query;
		env["REMOTE_HOST"] = this->_req_dict.find("Host")->second;
		env["REMOTE_ADDR"] = __get_ip(this->_fd);
		env["REMOTE_USER"] = "";
		env["REMOTE_IDENT"] = "";
		env["REQUEST_METHOD"] = this->_method;
		env["REQUEST_URI"] = this->_address /*+ this->_query*/ ;
		env["SCRIPT_NAME"] = this->_address;
		env["SCRIPT_FILENAME"] = this->_target;
		env["SERVER_NAME"] = this->_req_dict.find("Host")->second;
		env["SERVER_PROTOCOL"] = "HTTP/1.1";
		env["SERVER_PORT"] = "18004";
		env["SERVER_SOFTWARE"] = "FT_webserv/1.0.0";


		char *argv[3];

		char	**env = __set_env();

		argv[0] = const_cast<char *>(cgi_path.c_str());
		argv[1] = const_cast<char*>(this->_target.c_str());
		argv[2] = NULL;

		// Check if there is a body in the request
		execve(argv[0], argv, env);

		exit(400);
	}
	// ----------------------------------------------------------
	if (! this->_method.compare("POST"))
	{
		this->_pidwrite = fork();
		if (this->_pidwrite == -1)
			throw 500;
		else if (this->_pidwrite == 0)
		{
			close(readingPipe[1]);
			close(readingPipe[0]);
			close(errPipe[0]);
			close(errPipe[1]);
			close(writingPipe[0]); 
			if (it != this->_req_dict.end())
				write(writingPipe[1], it->second.c_str(), it->second.length());
			close(writingPipe[1]); 
			exit(0);
		}
	}
	close(writingPipe[0]); 
	close(writingPipe[1]);  
	close(readingPipe[1]);
	close(errPipe[1]);

	// MAIN PROCESS ------------------
	this->_cgi_fds.first = readingPipe[0];
	this->_cgi_fds.second = errPipe[0];
	// this->_cgi_writing_pipe = writingPipe[1];
	this->_pid = pid;

	waitpid(pid, &this->_status, WNOHANG);
}

void	Http_handler::__cgi_response_parser(std::string &cgi_res)
{
	// Read the first line from the string stream
	std::istringstream	iss(cgi_res);
	std::string			line;

	std::getline(iss, line);

	// Split the first line into its individual components
	std::istringstream	firstLineStream(line);
	std::string			status;
	int					code;

	firstLineStream >> status >> code;
	
	this->_header += this->header_http1 + std::to_string(code) + " " + g_ret[code] + "\r\n";
	while (std::getline(iss, line))
	{
		std::size_t	colonPos = line.find(':');
		if (colonPos != std::string::npos)
		{
			this->_header += line + "\n";
		}
		else
			break;
	}
	
	size_t	pos = cgi_res.find("\r\n\r\n");
	if (pos + 4 >= cgi_res.length())
	{
		this->_response.clear();
		this->_header += "\r\n";	
		return;
	}
	// Extract the body from the request
	this->_response = cgi_res.substr(pos + 4);

	this->_header += "Content-Length: " + std::to_string(this->_response.length()) + "\r\n";
	this->_header += "\r\n";
}

 std::string	Http_handler::cgi_response(void)
{
	char	buffer[1048];
	int		n;

	if (waitpid(this->_pid, &this->_status, WNOHANG) == 0)
	{
		/* the cgi is not finished yet */
		while ( (n = read(this->_cgi_fds.first, buffer, 1048)) > 0)
				this->_response.append(buffer, n);
		// CHECK IF PROG RETURN IS VALID OR ERR
		return ("");
	}
	wait(&(this->_pidwrite));
	/* the cgi is ended, checking status */
	if (WIFEXITED(this->_status)) // if exited "normaly" (not a signal)
	{
 		// check le return (exit 400 500 ou -1 prog)
		this->_valid = WEXITSTATUS(this->_status);
		if (this->_valid == 244)
			this->_valid = 500;
		else if (this->_valid == 144)
		{
			this->_valid = 400;
		}

		if (this->_valid == 500 || this->_valid == 400)
		{
			while ((n = read(this->_cgi_fds.second, buffer, 1048)) > 0)
				this->_response.append(buffer, n);

			__err_header(this->_valid);

			return this->_response;
		}
		// -----------------------------------------------------
		if (this->_valid < 0)
		{
			while ((n = read(this->_cgi_fds.second, buffer, 1048)) > 0)
				this->_response.append(buffer, n);
			__err_header(500);
		}
		else
		{
			while ( (n = read(this->_cgi_fds.first, buffer, 1048)) > 0)
				this->_response.append(buffer, n);
			__cgi_response_parser(this->_response);
			this->_response = this->_header + this->_response;
		}
		return (this->_response);
	}

	return ("");
}
//---------------------------------------------------------------------------------------











// DIRECTORY BROWSER ----------------------------------------------------------------------
void	Http_handler::__browse(std::string &request_loc)
{
	this->header_content_type += "text/html";
	__directory_browser(request_loc.c_str(), this->_address);
}

void	Http_handler::__directory_browser(const char *path, std::string const &host)
{
    std::string	dirName(path);
    DIR *dir	= opendir(path);

    std::string page =\
"<!DOCTYPE html>\r\n\
<html>\r\n\
<head>\r\n\
<title>" + dirName + "</title>\r\n\
</head>\r\n\
<body>\r\n\
<h1>INDEX</h1>\r\n\
<p>\n";

    if (dirName[0] != '/')
        dirName = "/" + dirName;
    for (struct dirent *dirEntry = readdir(dir); dirEntry; dirEntry = readdir(dir))
	{
        page += __filesLst(std::string(dirEntry->d_name), host);
    }

    page +="\
</p>\r\n\
</body>\r\n\
</html>\r\n";

    closedir(dir);
    this->_response = page;
}

std::string         Http_handler::__filesLst(std::string const &dirEntry, std::string const &host)
{
    std::stringstream   ss;

	if (!host.compare("/autoindex") || !host.compare("/"))
    	ss << "<p><a href=/"  << dirEntry + '>' + dirEntry + "</a></p>\n";
	else
   		ss << "<p><a href=" + host << dirEntry + '>' + dirEntry + "</a></p>\n";

    return ss.str();
}
// ----------------------------------------------------------------------------------------











//ETAG ------------------------------------------------------------------------------------
std::string Http_handler::__base64_encode(const std::string &s)
{
	static const std::string base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";

	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	int len = s.length();
	while (len--)
	{
		char_array_3[i++] = s[j++];
		if (i == 3)
		{
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';
	}

	return ret;
}

std::string Http_handler::__base64_decode(const std::string &encoded_string)
{
	static const std::string base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";

	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && (encoded_string[in_] != '=') && __is_base64(encoded_string[in_]))
	{
		char_array_4[i++] = encoded_string[in_];
		in_++;
		if (i == 4)
		{
			for (i = 0; i < 4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 4; j++)
			char_array_4[j] = 0;

		for (j = 0; j < 4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++)
			ret += char_array_3[j];
	}

	return ret;
}

bool	Http_handler::__is_base64(unsigned char c) {
  return (std::isalnum(c) || (c == '+') || (c == '/'));
}

void	Http_handler::__Etag_gen(std::string path)
{
	// check path 404 if not found
	struct stat file_stat;
	if (stat(path.c_str(), &file_stat) != 0)
		throw 404;

	// get last time modified
	// to GMT
	struct tm	*gmt_time = gmtime(&file_stat.st_mtime);
	time_t		last_modified = mktime(gmt_time);

	char buffer[32];
    strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S %Z", gmtime(&last_modified));

    std::string	file_to_encode(buffer);	
	file_to_encode += static_cast<char>(-1) + path;
	
	std::string	etag(__base64_encode(file_to_encode));
	this->header_ETag = "ETag: \""  + etag + "\"";
}

void	Http_handler::__Etag_reader(std::string &etag)
{
	if (etag.front() == '"')
		etag.erase(etag.begin());
	if (etag.back() == '"')
		etag.pop_back();

	etag = __base64_decode(etag);
	// find separator to get path and time.
	size_t	sep = etag.find(static_cast<char>(-1));
	// si ne trouve pas le séparateur alors ce n'est pas un ETag valid (not generated by us)
	if (sep == std::string::npos)
		throw 412;

	std::string	file = etag.substr(sep + 1);

	// si le path dans etag n'existe pas et que le etag est quand même reconnue
	// alors Etag obsolete
	struct stat file_stat;
	if (stat(file.c_str(), &file_stat) != 0)
		throw 412;
}

void	Http_handler::__condition_header(std::string address, Condition condition)
{
	struct stat	file_stat;
	if (stat(address.c_str(), &file_stat) != 0)
		throw 404;

	std::map<std::string, std::string>::iterator it;
	if (condition == MODIFIED_SINCE)
		it = this->_req_dict.find("If-Modified-Since");

	struct tm *gmt_time = gmtime(&file_stat.st_mtime);
	time_t	last_modified = mktime(gmt_time);
	time_t	request_time = __string_to_time_t_header(it->second);

	if (request_time && request_time >= last_modified)
		throw 304;
}
// ---------------------------------------------------------------------------------------











//SPECIAL CASE ----------------------------------------------------------------------------
void Http_handler::__range_cut(std::string &range_val)
{
    size_t	first = 0;
    size_t	second = 0;
    bool	absolute = false;

    // Check if the header starts with "bytes=", which indicates a byte range.
    if (range_val.find("bytes=") == 0)
    {
        // Split the header into the range values.
        std::string rangeValues = range_val.substr(6);
        std::stringstream ss(rangeValues);
        std::string startString, endString;
        std::getline(ss, startString, '-');
        std::getline(ss, endString);

        // Convert the start and end values to integers.
        std::stringstream startStream(startString);
        std::stringstream endStream(endString);
	
	if (range_val.find("bytes=-") != std::string::npos)
		absolute = true;
       
	startStream >> first;
        endStream >> second;
    }

    // Check that the start index is non-negative and the end index is greater than the start index.
	if (first > this->_response.length() - 1 || first < 0
		|| second > this->_response.length() - 1 || second < 0
		|| second < first)
	{
		this->_response.clear();
		throw 416;
	}
	
	size_t	pos;
	if ((pos = this->_response.find("lang=")) != std::string::npos
		&& header_language.empty())
	{
		std::string	tmp = this->_response.substr(pos + 6);
		std::string	lang = tmp.substr(0, tmp.find(('"')));
		
		this->header_language = "Content-Language: " + lang + "\r\n";
	}
	if ((pos = this->_response.find("encoding=")) != std::string::npos
		&& header_charset.empty())
	{
		std::string	tmp = this->_response.substr(pos + 10);
		std::string	charset = tmp.substr(0, tmp.find(('"')));

		for (std::string::iterator it = charset.begin(); it != charset.end(); ++it)
			*it = *it + 32 * (*it >= 65 && *it <= 90);

		this->header_charset = "; charset =" + charset;
	}

	int	original_size = this->_response.length();
	// Extract the substring if the response string is non-empty.
	if (!this->_response.empty())
	{
		if (absolute == false)
			this->_response = this->_response.substr(first, second - first + 1);
		else
			this->_response = this->_response.substr(0, second);
	}
	this->header_range = "Content-Range: bytes "
						+ std::to_string(first)
						+ "-"
						+ std::to_string(second)
						+ "/"
						+ std::to_string(original_size);
}
//---------------------------------------------------------------------------------------











// UTILS ------------------------------------------------------------------------------
void	Http_handler::__close_and_throw(std::fstream &file, int err)
{
	file.close();
	throw err;
}

void	Http_handler::__close_and_throw(std::ifstream &file, int err)
{
	file.close();
	throw err;
}

time_t	Http_handler::__string_to_time_t_header(const std::string &s)
{
	static const char *date_format = "%a, %d %b %Y %H:%M:%S %Z";

	struct tm tm;
	std::memset(&tm, 0, sizeof(tm));

	strptime(s.c_str(), date_format, &tm);
//		throw 400;
	return mktime(&tm);
}

std::string	Http_handler::__get_extension()
{
	std::string	ext = this->_address.substr(this->_address.find_last_of(".") + 1);
	if (ext == this->_address)
		return (std::string());

	return (ext);
}

std::string	Http_handler::__get_extension(const std::string &path)
{
	std::string	extension;
	size_t		dot_pos = path.find_last_of('.');

	if (dot_pos != std::string::npos)
		extension = path.substr(dot_pos + 1);

	// Convert the extension to lowercase
	std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

	return extension;
}

void	Http_handler::__trim(std::string &str)
{
	// Trim leading whitespace
	str.erase(str.begin(), std::find_if(str.begin(), str.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));

	// Trim trailing whitespace
	str.erase(std::find_if(str.rbegin(), str.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
}

std::vector<std::string>	Http_handler::__cpp_split(std::string &src, char sep)
{
	std::vector<std::string>	substrings;
	std::string					current;

	for (size_t i = 0; i < src.length(); i++)
	{
		if (src[i] == sep || i == src.length() - 1)
		{
			if (!current.empty())
			{
				__trim(current);
				substrings.push_back(current);
			}
			current.clear();
		}
		else
			current += src[i];
	}
	return (substrings);
}
// ---------------------------------------------------------------------------------











//STATICS FT ------------------------------------------------------------------------
std::string	Http_handler::get_time()
{
	time_t		rawtime;
	struct tm	*timeinfo;
	
	char buffer[80];

	time(&rawtime);
	timeinfo = gmtime(&rawtime);
	strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S %Z", timeinfo);

	return (std::string(buffer));
}

void	body_gen_4_static(int ret, std::string &response)
{
	response += "<!DOCTYPE html>\r\n";
	response += "<html>\r\n";
	response += "	<head>\r\n";
	response += "		<meta charset=\"UTF-8\">\r\n";
	response += "		<title>webserv</title>\r\n";
	response += "	</head>\r\n";
	response += "	<body bgcolor=\"white\">\r\n";
	response += "		<center><h1>" + std::to_string(ret) + " " + g_errs[ret] + "</h1></center>\r\n";
	response += "		<center><hr>Server: FT_Webserv/1.0.0</hr></center>\r\n";
	response +=			g_gif[1] + "\r\n";
	response += "		<center><p>Click <a href=\"/\">here</a> to return home.</p></center>\r\n";
	response += "	</body>\r\n";
	response += "</html>\r\n";	
}

std::string	Http_handler::http_408()
{
	std::string header;

	header += "HTTP/1.1 " + std::to_string(408) + " " + g_errs[408] + "\r\n";
	header += "Content-Type: text/html\r\n";
	header += "Date: " + get_time() + "\r\n";
	header += "Connection: close\r\n\r\n";

	return (header);
}

std::string	Http_handler::http_XXX(int ret, std::string alt, std::string def)
{
	std::string	response;
	std::string	header;

	if (def.empty())
		body_gen_4_static(ret, response);
	else
	{
		std::fstream	file(def);
		if (!file.is_open())
			body_gen_4_static(ret, response);
		else
		{
			std::stringstream	buffer;
			buffer << file.rdbuf();
			file.close();
			response += buffer.str();
		}
	}

	header += "HTTP/1.1 " + std::to_string(ret) + " " + g_errs[ret] + "\r\n";
	header += "Content-Length: " + std::to_string(response.length()) + "\r\n";
	header += "Content-Type: text/html\r\n";
	header += "Transfer-Encoding: identity\r\n";
	header += "Date: " + get_time() + "\r\n";
	if (ret == 300)
	{
		header +=  alt + "\r\n";
	}
	header += "Connection: close\r\n\r\n";
	response = header + response;
	return (response);
}
// -----------------------------------------------------------------------------------------



//	one line by request
//	IP			auth	date						request						resp size		referer							user-agent------------------->
// 127.0.0.1 - frank [10/Oct/2000:13:55:36 -0700] "GET /apache_pb.gif HTTP/1.0" 200 2326 "http://www.example.com/start.html" "Mozilla/4.08 [en] (Win98; I ;Nav)"

