#include <iostream>
#include <SFML/Graphics.hpp>
#include <Luna.h>
#include <Lilo.h>
#include <Game.h>

using namespace sf;

const unsigned int windowSizeX = 1200;
const unsigned int windowSizeY = 400;
const unsigned int groundLevel = windowSizeY - 150;
const unsigned int playerPos = windowSizeX / 8;
const unsigned int jumpSpeed = 8;
const unsigned int jumpHeight = groundLevel - 200;

static void positionTextCenter(Text& text, float offsetY)
{
	FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.f,
		textRect.top + textRect.height / 2.f);
	text.setPosition(Vector2f(windowSizeX / 2.f, windowSizeY / 2.f + offsetY));
}

int main()
{
	RenderWindow window(VideoMode(windowSizeX, windowSizeY), "Luna Jump");
	window.setVerticalSyncEnabled(true);

	int gameState = 1; // 0: menu, 1: running, 2: game over

	// Initialize Luna (player)
	Luna luna(playerPos, groundLevel);

	// Initialize Lilo (obstacle)
	Lilo lilo(windowSizeX, groundLevel, 10);

	// Initialize game object
	Game game;

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

		// Get object bounds for the current frame
		// Bounds get reduced to make for better hitboxes
		luna.bounds = luna.sprites[luna.index].getGlobalBounds();
		luna.bounds.width -= 15.f; luna.bounds.height -= 15.f; 
		lilo.bounds = lilo.sprites[lilo.index].getGlobalBounds();
		lilo.bounds.width -= 10.f;

		// ---------- Gamestate 0: Start screen ----------
		if (game.state == 0)
		{
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				game.setRunning();
			}
		}
		// ---------- Gamestate 1: Game is running ----------
		if (game.state == 1)
		{
			if (luna.bounds.intersects(lilo.bounds))
			{
				game.setGameOver();
			}

			// Check for jump input and perform jumps
			luna.jump(groundLevel, jumpHeight, jumpSpeed);
			// Move obstacles
			lilo.move(windowSizeX);
		}
		// ---------- Gamestate 2: Game over ----------
		if (game.state == 2)
		{
			luna.index = 5; // Load game over texture
			if (Keyboard::isKeyPressed(Keyboard::R))
			{
				lilo.reset(windowSizeX);
				luna.reset(groundLevel);

				game.setRunning();
			}
		}

	// ---------- Drawing ----------
		luna.sprites[luna.index].setPosition(Vector2f(luna.x, luna.y));
		lilo.sprites[lilo.index].setPosition(Vector2f(lilo.x, lilo.y));
		positionTextCenter(game.text, 0.f);
		positionTextCenter(game.instructions, windowSizeY/8.f);

		window.clear(Color::White);
		game.render(window, lilo, luna);
		// Drawing collision boxes for debugging
		/*
		RectangleShape lunaRect(Vector2f(lunaBox.width, lunaBox.height));
		lunaRect.setFillColor(Color::Blue);
		lunaRect.setPosition(lunaBox.left, lunaBox.top);
		RectangleShape liloRect(Vector2f(liloBox.width, liloBox.height));
		liloRect.setFillColor(Color::Blue);
		liloRect.setPosition(liloBox.left, liloBox.top);

		window.draw(lunaRect);
		window.draw(liloRect);
		*/
		// End debug
		window.display();
	}

	return 0;
}
