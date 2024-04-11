#include <random>
#include <ctime>
#include <iostream>
#include "Lilo.h"

using namespace sf;

Lilo::Lilo(float initX, float initY)
	:tex1(), tex2(), tex3(), sprites()
{
	x = initX;
	y = initY;

	if (!tex1.loadFromFile("./Assets/Lilo1.png"))
	{
		std::cerr << "Error loading texture 'Lilo1.png'";
	}
	if (!tex2.loadFromFile("./Assets/Lilo2.png"))
	{
		std::cerr << "Error loading texture 'Lilo2.png'";
	}
	if (!tex3.loadFromFile("./Assets/Lilo3.png"))
	{
		std::cerr << "Error loading texture 'Lilo3.png'";
	}
	
	sprites[0] = Sprite(tex1);
	sprites[1] = Sprite(tex2);
	sprites[2] = Sprite(tex3);

	for (Sprite& sprite : sprites)
	{
		FloatRect bounds = sprite.getGlobalBounds();
		sprite.setScale(Vector2f(0.2f, 0.2f));
		sprite.setOrigin(Vector2f(0, bounds.height));
		sprite.setPosition(Vector2f(x, y));
	}

	randomizeSprite();
}

Lilo::~Lilo()
{
}

void Lilo::move(const int entrypoint, int& gameSpeed)
{
	if (x <= -100)
	{
		randomizeSprite();
		x = static_cast<float>(entrypoint);
		gameSpeed += 1;
	}
	else
	{
		x -= gameSpeed;
	}
}

void Lilo::reset(const int entrypoint)
{
	x = static_cast<float>(entrypoint);
}

void Lilo::randomizeSprite()
{
	srand(static_cast<unsigned int>(time(NULL)));
	index = (rand() % 3);
}
