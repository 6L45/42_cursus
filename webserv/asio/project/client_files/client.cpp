#include "net_common.hpp"

enum class	CustomMsgTypes : uint32_t
{
	FireBullet,
	MovePlayer
};

class	CustomClient : public olc::net::Client_interface<CustomMsgTypes>
{
	public :
		bool	firebullet(float x, float y)
		{
			olc::net::message<CustomMsgTypes> msg;
			msg.header.id = CustomMsgTypes::FireBullet;
			msg << x << y;
			send(msg);
		}
};

int	main()
{
	{
		CustomClient c;
		c.connect("Hello world !", 6000);
		c.firebullet(2.0f, 2.0f);
	}
}
