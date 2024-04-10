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
