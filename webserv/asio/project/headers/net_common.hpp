#pragma once

# define ASIO_STANDALONE

# include <memory>
# include <mutex>
# include <deque>
# include <optional>
# include <vector>
# include <deque>
# include <algorithm>
# include <cstdint>
# include <chrono>
# include <iostream>
# include <thread>
# include <exception>
# include <cstring>

# include <boost/asio.hpp>
# include <boost/asio/ts/buffer.hpp>
# include <boost/asio/ts/internet.hpp>

using namespace boost;

#include "net_message.hpp"
#include "net_tsqueue.hpp"
#include "net_client.hpp"
#include "net_connection.hpp"
#include "net_server.hpp"

