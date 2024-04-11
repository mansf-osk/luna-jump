#include <iostream>
#include "Background.h"

Background::Background()
	:tex(), sprite()
{
	if (!tex.loadFromFile("../Assets/background.png"))
	{
		std::cerr << "Error loading texture 'background.png'";
	}
	sprite.setTexture(tex);

}

Background::~Background()
{
}

void Background::move(int gameSpeed, const int windowSizeX, const int windowSizeY)
{
	if (offset >= tex.getSize().x - windowSizeX)
	{
		// The original background image is 800px wide, so with modulo 800 we
		// make sure to get a seamless transition when shifting back.
		offset = offset % 800;
	}

	offset += gameSpeed;
	sprite.setTextureRect(IntRect(offset, 0, windowSizeX, windowSizeY));
}
