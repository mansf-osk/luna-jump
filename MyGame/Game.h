#pragma once
#include<SFML/Graphics.hpp>
#include<../MyGame/Lilo.h>
#include<../MyGame/Luna.h>

using namespace sf;

class Game
{
public:
	int state = 0;
	Font font1;
	Font font2;
	Text text;
	Text instructions;

	Game();
	~Game();

	void setStartScreen();
	void setRunning();
	void setGameOver();
	void render(RenderWindow& window, Lilo& lilo, Luna& luna) const;
};

