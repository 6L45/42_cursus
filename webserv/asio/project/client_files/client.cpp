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

	olc::net::message<CustomMsgTypes> msg;

	msg.header.id = CustomMsgTypes::FireBullet;

	int a = 1;
	bool b = true;
	float c = 3.14159f;

	struct 
	{
		float	x;
		float	y;
	} d[5];
	
	msg << a << b << c << d;

	a = 99;
	b = false;
	c = 99.0f;

	msg >> d >> c >> b >> a;

	return (0);
}
