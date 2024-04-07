#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;


const unsigned int windowSizeX = 800;
const unsigned int windowSizeY = 400;
const unsigned int groundLevel = windowSizeY - 20;
int main()
{
	RenderWindow window(VideoMode(windowSizeX, windowSizeY), "Luna Jump");
	window.setVerticalSyncEnabled(true);

	Texture luna;
	// This is a 512x512 image.
	if (!luna.loadFromFile("../Assets/Luna.png"))
	{
		std::cerr << "Error loading texture 'Luna.png'";
	}
	luna.setSmooth(true);

	Sprite player;
	player.setTexture(luna);
	// Origin for transformations is bottom left corner of sprite.
	player.setOrigin(Vector2f(0, 512));
	player.setScale(Vector2f(0.2f, 0.2f));
	player.setPosition(Vector2f(50, groundLevel));

	// Game loop
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case Event::Closed:
					window.close();
					break;
			}
		}

		window.clear(Color::White);
		window.draw(player);
		window.display();
	}

	return 0;
}