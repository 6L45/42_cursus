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
		
		template<typename T>
		struct message
		{
			message_header<T>		header{};
			std::vector<uint8_t>	body;

			size_t	size()
				{ return (sizeof(message_header<T>) + body.size()); }


			// std::cout overlaod
			friend std::ostream&	operator<<(std::ostream &os, const message<T> &msg)
			{
				os << "ID: " << int(msg.header.id) << " Size: " << msg.header.size;
				return (os);
			}

			// push any POD-like data into the message bufferi = push_back
			template<typename DataType>
			friend message<T>&	operator<<(message<T> &msg, const DataType &data)
			{
				// check that the type of data being pushed can be trivially copyable
				static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");

				// cache the current size of vector, as this will be the point we insert the data
				size_t	i = msg.body.size();

				// resize the vector by the size of the data being pushed 
				msg.body.resize(msg.body.size() + sizeof(DataType));

				// physically copy the data into the newly allocated vector space
				std::memcpy(msg.body.data() + i, &data, sizeof(DataType));

				// recalculate the message size
				msg.header.size = msg.size();
			
				return (msg);
			}

			// = pop_back
			template<typename DataType>
			friend message<T>&	operator>>(message<T> &msg, DataType &data)
			{
				static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed in vector");
				
				// cache the location towards the end of the vector where pulled data starts
				size_t	i = msg.body.size() - sizeof(DataType);

				// physically copy the data from the vector into the user varaible
				std::memcpy(&data, msg.body.data() + i, sizeof(DataType));

				// shrink the vector to remove read bytes and reset end position
				msg.body.resize(i);

				// recalculate the message size
				msg.header.size = msg.size();

				return (msg);
			}
		};

		template <typename T>
		class	Connection;

		template<typename T>
		struct owned_message
		{
			std::shared_ptr<Connection<T>> remote = nullptr;
			message<T> msg;

			friend	std::ostream& operator<<(std::ostream &os, const owned_message<T> &msg)
			{
				os << msg.msg;
				return (os);
			}

		};
	}
}
