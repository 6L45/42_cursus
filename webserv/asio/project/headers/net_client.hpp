#pragma once

#include "net_common.hpp"

namespace olc
{
	namespace net
	{
		template<typename T>
		class Client_interface
		{
			public :

				Client_interface() : m_socket(m_context){}
				virtual ~Client_interface(){};

				bool	connect(const std::string &host, const uint16_t port)
				{
					try
					{
						m_connection = std::make_unique<Connection<T>>();
						asio::ip::tcp::resolver resolver(m_context);
						m_endpoints = resolver.resolve(host, std::to_string(port));

						m_connection->ConnectToServer(m_endpoints);

						thrContext = std::thread([this]() {m_context.run(); });

					}
					catch(const std::exception& e)
					{
						std::cerr << "Client exception " << e.what() << '\n';
						return (false);
					}
					
					return (true);
				}

				void	disconnect()
				{
					if (this->isConnected())
					{
						this->m_connection.Disconnect();
					}
					m_context.stop();
					if (thContext.joinable())
						thContext.join();
					m_connection.realase();
				}

				bool	isConnected()
				{
					if (m_connection)
						return (m_connection->isConnected);
					return (false);
				}

				Tsqueue<owned_message<T>>& incomming()
				{
					return (m_qMessagesIn);
				}

			protected :
				asio::io_context				m_context;
				std::thread						thContext;
				asio::ip::tcp::socket			m_socket;
				std::unique_ptr<Connection<T>>	m_connection;				

			private :
				Tsqueue<owned_message<T>>	m_qMessagesIn;
		};	
	} // namespace net
		
} // namespace olc

