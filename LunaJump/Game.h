#pragma once
#include <SFML/Graphics.hpp>
#include <Lilo.h>
#include <Luna.h>
#include <Background.h>

using namespace sf;

// Handles all game logic, displayed text, constant parameters, scoring and stores the gamespeed.
class Game
{
public:
	const unsigned int windowSizeX = 1200;
	const unsigned int windowSizeY = 400;
	const int groundLevel = windowSizeY - 50;
	const int playerPos = windowSizeX / 8;
	const int jumpSpeed = 10;
	const int jumpHeight = groundLevel - 200;
	int state = 0; // 0: Start screen, 1: Game running, 2: Game over
	Font font1;
	Font font2;
	Text text;
	Text instructions;
	Text scoreText;
	int speed = 10;
	int score = 0;
	int highscore = 0;
	bool isHighscore = false;

	Game();
	~Game();

	// Renders all game objects by drawing them to the referenced RenderWindow.
	void render(RenderWindow& window, Background& bg, Lilo& lilo, Luna& luna);

	// Loads the current object bounds for collision detection, handles game logic based on gamestate
	// and updates object positions afterwards.
	void update(Lilo& lilo, Luna& luna, Background& bg);

private:
	void setStartScreen();
	void setRunning();
	void setGameOver();
	void updateBounds(Lilo& lilo, Luna& luna);
	void updateScore();
	void updatePositions(Lilo& lilo, Luna& luna);
	void centerText(Text& text, float offsetY);
};

