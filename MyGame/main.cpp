#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;


const unsigned int windowSizeX = 800;
const unsigned int windowSizeY = 400;
const unsigned int groundLevel = windowSizeY - 20;

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
		// Luna (player) textures
		// 512x512 pngs
	Texture lunaIdle;
	Texture lunaJump1;
	Texture lunaJump2;
	Texture lunaJump3;
	Texture lunaJump4;
	Texture lunaCursed;
	if (!lunaIdle.loadFromFile("../Assets/Luna.png"))
	{
		std::cerr << "Error loading texture 'Luna.png'";
	}
	if (!lunaJump1.loadFromFile("../Assets/Luna_Jump1.png"))
	{
		std::cerr << "Error loading texture 'Luna_Jump1.png'";
	}
	if (!lunaJump2.loadFromFile("../Assets/Luna_Jump2.png"))
	{
		std::cerr << "Error loading texture 'Luna_Jump2.png'";
	}
	if (!lunaJump3.loadFromFile("../Assets/Luna_Jump3.png"))
	{
		std::cerr << "Error loading texture 'Luna_Jump3.png'";
	}
	if (!lunaJump4.loadFromFile("../Assets/Luna_Jump4.png"))
	{
		std::cerr << "Error loading texture 'Luna_Jump4.png'";
	}
	if (!lunaCursed.loadFromFile("../Assets/Luna_Cursed.png"))
	{
		std::cerr << "Error loading texture 'Luna_Cursed.png'";
	}

	// Luna (player) sprites
	// lunaIndex can be used to select the version that should be drawn for that frame
	int lunaIndex = 0; //default to 0 -> idle
	Sprite lunaSprites[6];
	lunaSprites[0] = Sprite(lunaIdle);
	lunaSprites[1] = Sprite(lunaJump1);
	lunaSprites[2] = Sprite(lunaJump2);
	lunaSprites[3] = Sprite(lunaJump3);
	lunaSprites[4] = Sprite(lunaJump4);
	lunaSprites[5] = Sprite(lunaCursed);

	// Default values for lunaSprites
	FloatRect lunaBox = lunaSprites[lunaIndex].getGlobalBounds();
	Position lunaPosition;
	lunaPosition.x = 60;
	lunaPosition.y = groundLevel;

	for (Sprite& sprite : lunaSprites)
	{
		// Origin for transformations is bottom left corner of sprite.
		sprite.setOrigin(Vector2f(0, 512));
		sprite.setScale(Vector2f(0.2f, 0.2f));
		sprite.setPosition(Vector2f(lunaPosition.x, lunaPosition.y));
	}

	const int jumpSpeed = 8;
	const int jumpHeight = groundLevel - 200;
	bool isAscending = false;
	bool isDescending = false;
	bool hasLanded = true;

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
		FloatRect bounds = sprite.getGlobalBounds();
		// Origin for transformations is bottom left corner of sprite.
		sprite.setOrigin(Vector2f(0, bounds.height));
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
		lunaBox = lunaSprites[lunaIndex].getGlobalBounds();
		liloBox = liloSprites[liloIndex].getGlobalBounds();

		if (gameState == 1) // Game is running
		{
			if (lunaBox.intersects(liloBox))
			{
				gameState = 2; // Game over
			}

			// ---------- Jumping ----------
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
				lunaPosition.y -= jumpSpeed; // Going up equals subtracting pixels

				if ((groundLevel - lunaPosition.y) < ((groundLevel - jumpHeight) / 2))
				{
					lunaIndex = 1;
				}
				if ((groundLevel - lunaPosition.y) > ((groundLevel - jumpHeight) / 2))
				{
					lunaIndex = 2;
				}
			}
			if (isDescending)
			{
				lunaPosition.y += jumpSpeed; // Going down equals adding pixels

				if ((groundLevel - lunaPosition.y) > ((groundLevel - jumpHeight) / 2))
				{
					lunaIndex = 3;
				}
				if ((groundLevel - lunaPosition.y) < ((groundLevel - jumpHeight) / 2))
				{
					lunaIndex = 4;
				}
			}

			if (lunaPosition.y >= groundLevel)
			{
				lunaPosition.y = groundLevel;
				hasLanded = true;
				isDescending = false;
				lunaIndex = 0;
			}
			if (lunaPosition.y <= jumpHeight)
			{
				isAscending = false;
				isDescending = true;
			}

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
			lunaIndex = 5; // Dead
			if (Keyboard::isKeyPressed(Keyboard::R))
			{
				lunaIndex = 0;
				lunaPosition.y = groundLevel;

				liloIndex = 0;
				liloPosition.x = windowSizeX;

				hasLanded = true;
				isAscending = false;
				isDescending = false;
				gameState = 1; // Restart the game
			}
		}
	// ---------- Drawing ----------
		lunaSprites[lunaIndex].setPosition(Vector2f(lunaPosition.x, lunaPosition.y));
		liloSprites[liloIndex].setPosition(liloPosition.x, liloPosition.y);

		window.clear(Color::White);
		window.draw(liloSprites[liloIndex]);
		window.draw(lunaSprites[lunaIndex]);
		window.display();
	}

	return 0;
}