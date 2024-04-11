#include <iostream>
#include "Game.h"

Game::Game()
	:font1(), font2(), text(), instructions(), scoreText()
{
	if (!font1.loadFromFile("../Assets/Honk-Regular.ttf"))
	{
		std::cerr << "Error loading font 'Honk-Regular'";
	}
	if (!font2.loadFromFile("../Assets/Roboto-Regular.ttf"))
	{
		std::cerr << "Error loading font 'Roboto-Regular'";
	}

	text.setFont(font1);
	text.setFillColor(Color::Black);
	text.setCharacterSize(50);

	instructions.setFont(font2);
	instructions.setFillColor(Color::Black);
	instructions.setCharacterSize(16);

	scoreText.setFont(font2);
	scoreText.setFillColor(Color::Black);
	scoreText.setCharacterSize(16);

	setStartScreen();
}

Game::~Game()
{
}

void Game::setStartScreen()
{
	state = 0;
	text.setString("Welcome to Luna Jump!");
	instructions.setString("Press ENTER to start and SPACE to jump");
}

void Game::setRunning()
{
	score = 0;
	speed = 10;
	isHighscore = false;
	state = 1;
}

void Game::setGameOver()
{
	state = 2;
	text.setString("GAME OVER");
	instructions.setString("Press R to try again");
}

void Game::render(RenderWindow& window, Background& bg, Lilo& lilo, Luna& luna)
{
	// Start Screen
	if (state == 0)
	{
		window.draw(text);
		window.draw(instructions);
	}
	// Game running
	if (state == 1)
	{
		updateScore();
		window.draw(bg.sprite);
		window.draw(lilo.sprites[lilo.index]);
		window.draw(luna.sprites[luna.index]);
		window.draw(scoreText);
	}
	// Game over
	if (state == 2)
	{
		updateScore();
		window.draw(bg.sprite);
		window.draw(lilo.sprites[lilo.index]);
		window.draw(luna.sprites[luna.index]);
		window.draw(text);
		window.draw(instructions);
		window.draw(scoreText);
	}
}

void Game::update(Lilo& lilo, Luna& luna, Background& bg)
{
	updateBounds(lilo, luna);

	// ---------- Gamestate 0: Start screen ----------
	if (state == 0)
	{
		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			setRunning();
		}
	}
	// ---------- Gamestate 1: Game is running ----------
	if (state == 1)
	{
		if (luna.bounds.intersects(lilo.bounds))
		{
			setGameOver();
		}

		// Check for jump input and perform jumps
		luna.jump(groundLevel, jumpHeight, jumpSpeed);
		// Move obstacles
		lilo.move(windowSizeX, speed);
		// Move background
		bg.move(speed, windowSizeX, windowSizeY);

		if (isHighscore)
		{
			highscore = score;
		}
	}
	// ---------- Gamestate 2: Game over ----------
	if (state == 2)
	{
		if (isHighscore)
		{
			luna.index = 6;	// Load highscore texture
		}
		else
		{
			luna.index = 5; // Load game over texture
		}
		if (Keyboard::isKeyPressed(Keyboard::R))
		{
			lilo.reset(windowSizeX);
			luna.reset(groundLevel);

			setRunning();
		}
	}

	updatePositions(lilo, luna);
}

void Game::updateScore()
{
	// Initial speed is 10, so we substract that to start with score 0
	score = speed - 10;
	if (score > highscore)
	{
		isHighscore = true;
	}
	scoreText.setString(("Score: " + std::to_string(score) + " Highscore: " + std::to_string(highscore)));
}

void Game::updatePositions(Lilo& lilo, Luna& luna)
{
	luna.sprites[luna.index].setPosition(Vector2f(luna.x, luna.y));
	lilo.sprites[lilo.index].setPosition(Vector2f(lilo.x, lilo.y));
	centerText(text, 0.f);
	centerText(instructions, windowSizeY / 8.f);
	centerText(scoreText, -(windowSizeY / 3.f));
}

void Game::centerText(Text& text, float offsetY)
{
	FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.f,
	textRect.top + textRect.height / 2.f);
	text.setPosition(Vector2f(windowSizeX / 2.f, windowSizeY / 2.f + offsetY));
}

void Game::updateBounds(Lilo& lilo, Luna& luna)
{
	luna.bounds = luna.sprites[luna.index].getGlobalBounds();
	luna.bounds.width -= 15.f; luna.bounds.height -= 15.f;
	lilo.bounds = lilo.sprites[lilo.index].getGlobalBounds();
	lilo.bounds.width -= 10.f;
}
