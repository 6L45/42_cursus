#pragma once

# include <sys/types.h>
# include <sys/time.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <limits.h>

# include <regex>
# include <map>
# include <set>
# include <vector>
# include <stack>
# include <list>
# include <fstream>
# include <cstring>
# include <iostream>
# include <csignal>
# include <algorithm>
# include <sstream>
# include <utility>
# include <stdexcept>
# include <fstream>
# include <filesystem>
# include <ctime>
# include <utility>
# include <cstdio>
# include <cstdlib>  // for rand(), srand(), and RAND_MAX
# include <functional> //	std::ptr_fun && std::not1

# include <unistd.h>
# include <sys/wait.h>

# include "global_structs.hpp"

# define SERVER_PORT 18002
# define SA struct sockaddr
# define MAXLINE 4096
# define PORT 18005
# define CONF_EXTENTION_S_NAME ".conf"
# define KEEP_ALIVE 5
