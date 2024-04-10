#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Lilo
{
public:
	Texture tex1;
	Texture tex2;
	Texture tex3;
	int index = 0;
	Sprite sprites[3];
	float x = 0.f;
	float y = 0.f;
	FloatRect bounds;
	int speed = 0;

	Lilo(float initX, float initY, int initSpeed);
	~Lilo();

	void move(const int entrypoint);
	void reset(const int entrypoint);
};

