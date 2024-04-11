#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Background
{
public:
	Texture tex;
	Sprite sprite;
	unsigned int offset = 0;

	Background();
	~Background();

	void move(int gameSpeed, const int windowSizeX, const int windowSizeY);
};

