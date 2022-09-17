#pragma once

# include "net_common.hpp" 

namespace olc
{
	namespace net
	{
		template<typename T>
		class Connection : public std::enable_shared_from_this<Connection<T>>
		{
			public :
				Connection();
				virtual ~Connection();

				bool	connectToServer();
				bool	disconnect();
				bool	isConnected() const;

				bool	send(const message<T> &msg);

			protected :
				asio::ip::tcp::socket	m_socket;
				asio::io_context		&m_asioContext;
				Tsqueue<message<T>>		m_qMessagesOut;
				Tsqueue<owned_message<T>>	&m_qMessageIn;
		};
	}
}
