#pragma once

# include "net_common.hpp"

namespace olc
{
	namespace net
	{
		template<typename T>
		class Tsqueue
		{
			public :
				Tsqueue() = default;
				Tsqueue(const Tsqueue<T> &) = delete;
				virtual ~Tsqueue() { this->clear(); }

				const T&	front()
				{
					std::scoped_lock	lock(this->muxQueue);
					return (this->dequeu.front());
				}

				const T&	back()
				{
					std::scoped_lock	lock(this->musQueue);
				}

				void	push_back(const T &item)
				{
					std::scoped_lock	lock(this->muxQueue);
					this->desQueue.emplace_back(std::move(item));
				} 
				
				void	push_front(const T &item)
				{
					std::scoped_lock	lock(this->muxQueue);
					this->desQueue.emplace_front(std::move(item));
				} 

				bool	empty()
				{
					std::scoped_lock	lock(this->muxQueue);
					return (this->deQueue.empty());
				}

				size_t	count()
				{
					std::scoped_lock	lock(this->muxQueue);
					return	this->deqQueue.size();
				}

				void	clear()
				{
					std::scoped_lock	lock(this->muxQueue);
					this->deqQueue.clear();
				}

				T	pop_front()
				{
					std::scoped_lock	lock(this->muxQueue);
					auto t = std::move(this->deqQueue.front());
					this->deqQueue.pop_front();
					
					return (t);
				}
				
				T	pop_back()
				{
					std::scoped_lock	lock(this->muxQueue);
					auto t = std::move(this->deqQueue.back());
					this->deqQueue.pop_back();
					
					return (t);
				}

			protected :
				std::mutex		muxQueue;
				std::deque<T>	deqQueue;
		};
	}
}
