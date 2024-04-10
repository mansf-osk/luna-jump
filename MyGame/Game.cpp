#include <iostream>
#include "Game.h"

Game::Game()
	:font1(), font2(), text(), instructions()
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
	state = 1;
}

void Game::setGameOver()
{
	state = 2;
	text.setString("GAME OVER");
	instructions.setString("Press R to try again");
}

void Game::render(RenderWindow& window, Lilo& lilo, Luna& luna) const
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
		window.draw(lilo.sprites[lilo.index]);
		window.draw(luna.sprites[luna.index]);
	}
	// Game over
	if (state == 2)
	{
		window.draw(lilo.sprites[lilo.index]);
		window.draw(luna.sprites[luna.index]);
		window.draw(text);
		window.draw(instructions);
	}
}
