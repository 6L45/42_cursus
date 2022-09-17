#pragma once

# include "net_common.hpp"

namespace olc
{
	namespace net
	{
		template<typename T>
		struct message_header
		{
			T			id{};
			uint32_t	size = 0;

		};
		
	}
}
