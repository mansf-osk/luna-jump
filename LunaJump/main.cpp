#include <iostream>
#include <SFML/Graphics.hpp>
#include <Luna.h>
#include <Lilo.h>
#include <Background.h>
#include <Game.h>

using namespace sf;

int main()
{
	// Initialize game object
	Game game;

	// Initialize game window
	RenderWindow window(VideoMode(game.windowSizeX, game.windowSizeY), "Luna Jump", Style::Close);
	window.setFramerateLimit(60);

	// Initialize Luna (player)
	Luna luna(static_cast<float>(game.playerPos), static_cast<float>(game.groundLevel));

	// Initialize Lilo (obstacle)
	Lilo lilo(static_cast<float>(game.windowSizeX), static_cast<float>(game.groundLevel));

	// Initialize moving background
	Background bg;

	// Game loop
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		// Logic 
		game.update(lilo, luna, bg);

		// Drawing 
		window.clear(Color::White);
		game.render(window, bg, lilo, luna);
		window.display();
	}
	return 0;
}
