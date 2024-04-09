#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Luna
{
public:
	Texture idle;
	Texture jump1;
	Texture jump2;
	Texture jump3;
	Texture jump4;
	Texture cursed;
	int index = 0;
	Sprite sprites[6];
	float x = 0.f;
	float y = 0.f;
	FloatRect box;
	bool isAscending = false;
	bool isDescending = false;
	bool hasLanded = true;
	
	Luna();
	~Luna();

	void jump(const int groundLevel, const int jumpHeight, const int jumpSpeed);

};

