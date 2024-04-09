#include <iostream>
#include <SFML/Graphics.hpp>
#include <Luna.h>

using namespace sf;


const unsigned int windowSizeX = 800;
const unsigned int windowSizeY = 400;
const unsigned int groundLevel = windowSizeY - 150;
const int jumpSpeed = 8;
const int jumpHeight = groundLevel - 200;

struct Position
{
	int x;
	int y;
};

int main()
{
	RenderWindow window(VideoMode(windowSizeX, windowSizeY), "Luna Jump");
	window.setVerticalSyncEnabled(true);

	int gameState = 1; // 0: menu, 1: running, 2: game over

	// ---------- Luna (player) setup ----------
	Luna luna;
	luna.x = 60;
	luna.y = groundLevel;

	// ---------- Lilo (obstacle) setup ----------
		// Lilo (obstacle) textures
	Texture lilo1;
	Texture lilo2;
	Texture lilo3;
	if (!lilo1.loadFromFile("../Assets/Lilo1.png"))
	{
		std::cerr << "Error loading texture 'Lilo1.png'";
	}
	if (!lilo2.loadFromFile("../Assets/Lilo2.png"))
	{
		std::cerr << "Error loading texture 'Lilo2.png'";
	}
	if (!lilo3.loadFromFile("../Assets/Lilo3.png"))
	{
		std::cerr << "Error loading texture 'Lilo3.png'";
	}

	// Lilo (obstacle) sprites
	int liloIndex = 0;
	Sprite liloSprites[3];
	liloSprites[0] = Sprite(lilo1);
	liloSprites[1] = Sprite(lilo2);
	liloSprites[2] = Sprite(lilo3);

	// Default values for liloSprites
	FloatRect liloBox = liloSprites[liloIndex].getGlobalBounds();
	Position liloPosition;
	liloPosition.x = windowSizeX;
	liloPosition.y = groundLevel;

	for (Sprite& sprite : liloSprites)
	{
		sprite.setScale(Vector2f(0.2f, 0.2f));
		sprite.setPosition(Vector2f(liloPosition.x, liloPosition.y));
	}

	int liloSpeed = 10;

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

		// ---------- Logic ----------

		// Get object bounds for the current frame
		luna.box = luna.sprites[luna.index].getGlobalBounds();
		luna.box.width -= 15.f; luna.box.height -= 15.f; 
		liloBox = liloSprites[liloIndex].getGlobalBounds();
		liloBox.width -= 10.f;

		if (gameState == 1) // Game is running
		{
			if (luna.box.intersects(liloBox))
			{
				gameState = 2; // Game over
			}

			// ---------- Jumping ----------
			luna.jump(groundLevel, jumpHeight, jumpSpeed);

			// ---------- Lilo moving ----------
			if (liloPosition.x <= -100)
			{
				liloPosition.x = windowSizeX;
			}
			else
			{
				liloPosition.x -= liloSpeed;
			}
		}
		if (gameState == 2) // Game over
		{
			luna.index = 5; // Dead
			if (Keyboard::isKeyPressed(Keyboard::R))
			{
				luna.index = 0;
				luna.y = groundLevel;

				liloIndex = 0;
				liloPosition.x = windowSizeX;

				luna.hasLanded = true;
				luna.isAscending = false;
				luna.isDescending = false;
				gameState = 1; // Restart the game
			}
		}
	// ---------- Drawing ----------
		luna.sprites[luna.index].setPosition(Vector2f(luna.x, luna.y));
		liloSprites[liloIndex].setPosition(liloPosition.x, liloPosition.y);

		window.clear(Color::White);
		window.draw(liloSprites[liloIndex]);
		window.draw(luna.sprites[luna.index]);
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