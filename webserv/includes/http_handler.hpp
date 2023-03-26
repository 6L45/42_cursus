#pragma once

# include "common.hpp"

class Server;
class __location;

enum Condition
{
	MODIFIED_SINCE = 1
};

class Http_handler // : inherit from a execution class ? 
{
	public :
	//DECLARATIONS
		typedef	std::map<std::string, std::string>					dico;
		typedef std::map<std::string, std::string>::iterator		MMAPIterator;
		typedef std::map<std::string, std::string>::const_iterator	MMAPConstIterator;

	// CONSTRUCT DESTRUCT	
		Http_handler(std::string &request, int &fd); // receive htttp request
		~Http_handler() {};

	// GETTER
		std::string		get_host_name(void) const;
		std::string		get_method(void) const;
		std::string		get_body(void) const;
		std::string		get_alternates_path(void);
		int			get_content_length_val();
		int			invalid_request(void) const;
		size_t			body_max_size();
		std::string		get_connection(void) const;
		bool			get_keep_alive() const;
		int			keep_alive_value(void) const;
		int			&get_status();
		int			get_cgi_pid(void);
		int			get_fd_response(void);
		std::pair<int, int>	&awaiting_fd_for_writing(void);
		int			get_pipe_to_cgi(void);
		std::string		&get_response(void);


	//CLASS BUILDER
		void			add_body(const std::string &body);
		void			load_body(std::string &request);
		std::pair<bool, std::vector<std::string> >	body_inspector();
		void			pipelined_body_destroy();

	//CHECKER
		int			unauthorized_method(Server &serv);
		bool			valid_header(std::string first_line);
	
	//METHOD EXEC
		std::string		exec_request();

	//CGI RELATED
		std::string		cgi_response(void);

	// STATIC
		static std::string	get_time(void);
		static std::string	http_408();
		static std::string	http_XXX(int ret, std::string alt = std::string(), std::string def = std::string());

	private :


		struct Header
		{
			int start_pos;
			int end_pos;

			std::string content;
		};

	//HEADER RESPONSE BUILD FIELDS
		std::string	header_http1;
		std::string	header_content_len;
		std::string	header_content_loc;
		std::string	header_content_type;
		std::string	header_date;
		std::string	header_last_modif;
		std::string	header_connect;
		std::string	header_server;
		std::string	header_encoding;
		std::string	header_location;
		std::string	header_alternate;
		std::string	header_transfer;
		std::string	header_ETag;
		std::string	cookie;
		std::string	header_range;
		std::string	header_language;
		std::string	header_charset;

	//DICO
		dico	env;				//CGI env
		dico	_req_dict;			//_requ_dict = http fields

	//CGI RELATED
		int			_fd;		//get_pid() du fd associé à la requête
		std::pair<int, int>	_cgi_fds;	//pipe output stdin && stderr
		int			_cgi_pipe;	//pipe write to running cgi
		int			_status;	//waipid status
		int			_pid;		//running cgi pid
		int			_pidwrite;	//running write pid for cgi
		Server*		_serv;

	//REQUEST RELATED
		std::string	_method;	//method
		std::string	_subroot;	//root server
		std::string	_address;	//http://localhost/<_address>
		std::string	_target;	//root + _address (real file location)
		std::string	_query;		//http://localhost/<_address>?<_query>

	//RESPONSE RELATED
		__location	*_loc;		//server info associated to _address
		std::string	_header;	//header response
		std::string	_response;	//body response (en construct)
						// return (response = header + response)
	//REQUEST HEADER CHECKER
		int		_valid;



	//CLASS BUILDER
		void		__clean_address(void);

	//CHECKER
		bool		__index_path_handler(std::string &request_loc);
		int		__path_evaluation(Server &serv);
		bool		__not_a_method();
		bool		__not_a_method(std::string &method);
		bool		__is_valid_http_time(const std::string &s);
		int		__this_is_the_way(void);
		void		__inside_request_checker(std::string &actual_body, std::vector<std::string> &vect);

	//METHOD EXEC
		void		__GET_response(void);
		void		__response_init(std::ifstream &file);
		void		__get_file_content(std::ifstream &file, std::string request_loc);
		void		__DELETE_response(void);
		int		__POST_response(void);
		int		__PUT_response(void);

	// RESPONSE GEN
		void		__200_response(int ret);
		void		__err_header(int ret);
		void		__body_gen(int ret);
		void		__default_body_gen(int ret);

	// GCI
		char		**__set_env(void);
		std::string	__get_ip(int client_fd);
		std::string	__get_query(void);
		void		__CGI_exec(std::string &cgi_path);
		void		__cgi_response_parser(std::string &cgi_res);

	// DIRECTORY BROWSER
		void		__browse(std::string &request_loc);
		void		__directory_browser(const char *path, std::string const &host);
		std::string	__filesLst(std::string const &dirEntry, std::string const &host);

	//ETAG
		std::string	__base64_encode(const std::string &input);
		std::string	__base64_decode(const std::string &input);
		bool		__is_base64(unsigned char c);
		void		__Etag_gen(std::string path);
		void		__Etag_reader(std::string &etag);
		void		__condition_header(std::string address, Condition condition);

	// SPECIAL CASE
		void		__range_cut(std::string &range_val);

		void		__privates_init(void);
	//UTILS
		void		__close_and_throw(std::fstream &file, int err);
		void		__close_and_throw(std::ifstream &file, int err);
		time_t		__string_to_time_t_header(const std::string &s);
		std::string	__get_extension();
		std::string	__get_extension(const std::string &path);
		void		__trim(std::string &str);
		std::vector<std::string>	__cpp_split(std::string &src, char sep);
};

# include "server.class.hpp"
