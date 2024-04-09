#include <iostream>
#include "Luna.h"

using namespace sf;

Luna::Luna()
	:idle(), jump1(), jump2(), jump3(), jump4(), cursed(), sprites()
{
	if (!idle.loadFromFile("../Assets/Luna.png"))
	{
		std::cerr << "Error loading texture 'Luna.png'";
	}
	if (!jump1.loadFromFile("../Assets/Luna_Jump1.png"))
	{
		std::cerr << "Error loading texture 'Luna_Jump1.png'";
	}
	if (!jump2.loadFromFile("../Assets/Luna_Jump2.png"))
	{
		std::cerr << "Error loading texture 'Luna_Jump2.png'";
	}
	if (!jump3.loadFromFile("../Assets/Luna_Jump3.png"))
	{
		std::cerr << "Error loading texture 'Luna_Jump3.png'";
	}
	if (!jump4.loadFromFile("../Assets/Luna_Jump4.png"))
	{
		std::cerr << "Error loading texture 'Luna_Jump4.png'";
	}
	if (!cursed.loadFromFile("../Assets/Luna_Cursed.png"))
	{
		std::cerr << "Error loading texture 'Luna_Cursed.png'";
	}
	sprites[0] = Sprite(idle);
	sprites[1] = Sprite(jump1);
	sprites[2] = Sprite(jump2);
	sprites[3] = Sprite(jump3);
	sprites[4] = Sprite(jump4);
	sprites[5] = Sprite(cursed);

	for (Sprite& sprite : sprites)
	{
		sprite.setScale(Vector2f(0.2f, 0.2f));
	}
}

Luna::~Luna()
{
}

void Luna::jump(const int groundLevel, const int jumpHeight, const int jumpSpeed)
{
	if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				if (hasLanded && !isAscending)
				{
					isAscending = true;
					hasLanded = false;
				}
			}

			if (isAscending)
			{
				y -= jumpSpeed; // Going up equals subtracting pixels

				if ((groundLevel - y) < ((groundLevel - jumpHeight) / 2))
				{
					index = 1;
				}
				if ((groundLevel - y) > ((groundLevel - jumpHeight) / 2))
				{
					index = 2;
				}
			}
			if (isDescending)
			{
				y += jumpSpeed; // Going down equals adding pixels

				if ((groundLevel - y) > ((groundLevel - jumpHeight) / 2))
				{
					index = 3;
				}
				if ((groundLevel - y) < ((groundLevel - jumpHeight) / 2))
				{
					index = 4;
				}
			}

			if (y >= groundLevel)
			{
				y = groundLevel;
				hasLanded = true;
				isDescending = false;
				index = 0;
			}
			if (y <= jumpHeight)
			{
				isAscending = false;
				isDescending = true;
			}

}
