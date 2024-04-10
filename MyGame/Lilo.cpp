#include <iostream>
#include "Lilo.h"

using namespace sf;

Lilo::Lilo(float initX, float initY, int initSpeed)
	:tex1(), tex2(), tex3(), sprites()
{
	x = initX;
	y = initY;
	speed = initSpeed;

	if (!tex1.loadFromFile("../Assets/Lilo1.png"))
	{
		std::cerr << "Error loading texture 'Lilo1.png'";
	}
	if (!tex2.loadFromFile("../Assets/Lilo2.png"))
	{
		std::cerr << "Error loading texture 'Lilo2.png'";
	}
	if (!tex3.loadFromFile("../Assets/Lilo3.png"))
	{
		std::cerr << "Error loading texture 'Lilo3.png'";
	}

	sprites[0] = Sprite(tex1);
	sprites[1] = Sprite(tex2);
	sprites[2] = Sprite(tex3);

	for (Sprite& sprite : sprites)
	{
		sprite.setScale(Vector2f(0.2f, 0.2f));
		sprite.setPosition(Vector2f(x, y));
	}
}

Lilo::~Lilo()
{
}

void Lilo::move(const int entrypoint)
{
	if (x <= -100)
	{
		x = entrypoint;
	}
	else
	{
		x -= speed;
	}
}

void Lilo::reset(const int entrypoint)
{
	x = entrypoint;
}
