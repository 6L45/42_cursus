#ifndef WEBSERV_CLASS_HPP
# define WEBSERV_CLASS_HPP
#include "common.hpp"
#include "server.class.hpp"
#include "conf.class.hpp"
#include "Client.class.hpp"

/*
	Defining Macro for commande names
*/
# define CMD_END_WEBSERV "quit"
# define CMD_PAUSE "pause"
# define CMD_RUN "run"
# define CMD_RESTART_WEBSERV "restart"
# define CMD_PAUSE_SERV "pause server"
# define CMD_RUN_SERV "run serverv"
# define CMD_CHANGE_CONFIG_FILE "config"

/* 
	Defining Macro to acces the bit of the state info about webserv
*/
#define WS_ISRUNNING (_state & (1 << 0))
#define WS_ISINPAUSE (_state & (1 << 1))
#define WS_DISPLAY (_state & (1 << 2))

/*
	Macro to set the bit of options 
*/
#define WS_SETRUN (_state = _state | (1 << 0))
#define WS_SETPAUSE (_state = _state | (1 << 1))
#define WS_DISPLAYON (_state = _state | (1 << 2))
#define WS_SETEND (_state = _state & ~(1 << 0))
#define WS_SETUNPAUSE (_state = _state & ~(1 << 1))
#define WS_DISPLAYOFF (_state = _state & ~(1 << 2))


class Chunks
{
	public:
		Chunks();
		
		std::string	&get_full_body();
		int		get_body_size();
		int		concat(std::string &request);
		void		clear();

		static int	__hex_string_to_int(const std::string &hex_string);

	private:
		std::string	_body;
		std::string	_buffer;
		int		_size;

		bool		__eraseFirstLine(std::string &s);
};

typedef struct	s_client
{
	bool		fileno_server;
	int		fd;
	unsigned long		keep_alive;
	clock_t		t;
	std::string	request;
	std::string	response;
	Chunks		chunk;

	Http_handler	*request_handler;
	std::vector<std::string>	pipeline;	

	s_client() : chunk() {}
}				t_client;

class Webserv
{
	public :
		// constru - destru
		Webserv(Conf config, char** env);
		~Webserv();
		
		// public methods
		void 		launch();

	private :

		Webserv();

		typedef	std::vector<Server>::const_iterator	server_pointer;
		typedef int					port_fd;

		std::vector<t_client>				_client;
		std::map<int, int>				_corresponding_cgi_fd;
		std::multimap<port_fd,server_pointer>		_port_host;
		std::map<int,port_fd>				_track; // link the connexion port with the opened fd
		std::vector<Server>				_servers; //vector car le nombre de serveur reste le même
		std::list<Client>				_clients; //list car beaucoup de connexion et deconnexions sont attendues.
		char						_state;
		int						_max_connexion;
		fd_set						_current_sockets;
		fd_set						_current_write_sockets;
		std::set<int>					_fd_tracker;
		char						**_env;

		Conf						_conf;

	//CONSTRCUT
		port_fd		__create_socket(int port);

	//SOCKETS MECHANICS
		void	__timeout_handler();
		void	__check_sockets(fd_set &ready_sockets, fd_set &ready_write_sockets, struct sockaddr_in &client, socklen_t &client_len);
		void	__new_connect_init(int fd, int index);
		void	__close_connexion(int fd);

	//HTTP
		int 	__http_handler_init(int fd);
		void	request_handler(int fd); // webserv recupere la requete du client pour la donner au serveur qui garde en interne la manip a faire avec http selon ses valeurs
		int 	__chunks_status(int ret, int fd);
		void	__http_process(int fd, std::string &request);
		void	__cgi_fds_init(int fd);
		void	__http_execution(int fd);
		void	__pipeline_handler(int fd);
		
	// COM IN - OUT
		void	send_response(int fd, const std::string& response);
		void	send_response(int fd);
		void	__response_XXX_and_close(int fd, int ret);

	// UTILS
		bool	__is_a_socket(int fd) const;
		void	__console();
		void	__print_connexions_stats() const;
		int	__get_the_port(int fd);

		template <class T>
		void	__display(const T& msg, std::ostream& o);
		template <class T>
		void	__display_endl(const T& msg, std::ostream& o);
};

#endif

