#pragma once
#include <SFML/Graphics.hpp>
#include <../MyGame/Lilo.h>
#include <../MyGame/Luna.h>
#include <../MyGame/Background.h>

using namespace sf;

class Game
{
public:
	int state = 0;
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

	void setStartScreen();
	void setRunning();
	void setGameOver();
	void render(RenderWindow& window, Background& bg, Lilo& lilo, Luna& luna);

private:
	void updateScore();
};

