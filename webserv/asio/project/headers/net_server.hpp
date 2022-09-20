#pragma once

# include "net_common.hpp"

namespace olc
{
	namespace net
	{
		template<typename T>
		class Server_interface
		{
			public :
				Server_interface(uint16_t port)
					: m_asioAcceptor(m_asioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
				{
					;
				}

				virtual ~Server_interface()
				{
					stop();
				}

				bool start()
				{
					try
					{
						WaitForClientConnection();
						m_threadContext = std::thread([this]() 
							{
								m_asioContext.run(); 
							});
					}
					catch(const std::exception& e)
					{
						std::cerr << "[SERVER] Exception : " << e.what() << '\n';
						return (false);
					}
					std::cout << "[SERVER] Started !" << std::endl;

					return (true);
				}

				bool stop()
				{
					m_asioContext.stop();

					if (m_threadContext.joinable())
						m_threadContext.join();
					
					std::cout << "[SERVER] Stopped" << std::endl;
				}

				// ASYNC - Instruct asio wait  for connection
				void	waitForClientConnection()
				{
					m_asioAcceptor.async_accept(
						[this](std::error_code ec, asio::ip::tcp::socket socket)
						{
							if (!ec)
							{
								std::cout << "[SERVER] New Connection : " << socket.remote_endpoint() << std::endl;
								/*std::shared_ptr<Connection<T>> newconn = 
									std::make_shared<Connection<T>>(Connection<T>::owner::server,
										m_asioContext, std::move(socket), m_qMessageIn);
								*/
								// give user the possibility to deny the connection
							/*	if (onclientConnect(newconn))
								{
									m_deqConnections.push_back(std::move(newconn));
									m_deqConnections.back()->connectToClient(nIDCounter++);

									std::cout << "[" << m_deqConnections.back()->GetID() << "]" << Connection Approved << std::endl;
								}
								else
									std::cout << "[------] Connection Denied" << std::endl;
							} */
							else
							{
								// Error has occured during acceptance
								std::cout << "[SERVER] New Connection Error : " << ec.message() << std::endl;
							}
							waitForClientConnection();
						}
					);
				}

				// Send message to a client 
				void	messageClient(std::shared_ptr<Connection<T>> client, const message<T> &msg)
				{
						if (client && client->IsConnected())
						{
							client->send(msg);
						}
						else
						{
							onClientDisconnnect(client);
							client.reset();
							m_deqConnections.erase(
								std::remove(m_deqConnections.begin(), m_deqConnections.end(), client), m_deqConnections.end();
							)
						}
				}

				// Send message to all clients
				void	messageAllClient(const message<T> &msg, std::shared_ptr<Connection<T>> pIgnoreClient = nullptr)
				{
					for (auto &client: m_deqConnections)
					{
						if (client && client->isConnected())
						{
							if (client != pIgnoreClient)
								client->send(msg);
						}
						else
						{
							onClientDisconnnect(client);
							client.reset();
							bInvalidClientExists = true;
						}
					}
				}

				void	update(size_t nMaxMessage = -1)
				{
					size_t	nMessageCount = 0;
					while (nMessageCount < nMaxMessage && !m_qMessageIn.empty())
					{
						auto msg = m_qMessageIn.pop_front();

						onMessage(msg.remote, msg.msg);
						nMessageCount++;
					}
				}

			protected :
				Tsqueue<owned_message<T>>	m_qMessageIn;
				asio::io_context			m_asioContext;
				std::thread					m_threadContext;
				asio::ip::tcp::acceptor		m_asioAcceptor;
				uint32_t					nIDCounter = 1000;

				std::deque<std::shared_ptr<Connection<T>>>	m_deqConnections;

				// called when a client connect, can veto the connection by returning false
				virtual bool	onClientConnect(std::shared_ptr<Connection<T>> client)
				{
					return (false);
				}

				// called when client appears to have dicsonnected
				virtual	void	onClientDisconnnect(std::shared_ptr<Connection<T>> client)
				{

				}

				// called when a message arrives
				virtual void	onMessage(std::shared_ptr<Connection<T>> client, message<T> &msg)
				{

				}
		};		
	} // namespace net
} // namespace olc
