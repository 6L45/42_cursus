#pragma once

# define ASIO_STANDALONE

# include <memory>
# include <mutex>
# include <deque>
# include <optional>
# include <vector>
# include <algorithm>
# include <cstdint>
# include <chrono>
# include <iostream>
# include <thread>

# include <boost/asio.hpp>
# include <boost/asio/ts/buffer.hpp>
# include <boost/asio/ts/internet.hpp>

using namespace boost;
