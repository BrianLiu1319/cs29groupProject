#pragma once
#include "SFML/Graphics/Sprite.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Inventory {
	int width;
	int height;
	Vector2f position;
	Texture image;
	Sprite spInven;
	int contain;  // if contain == 0 it's a dog, if contain is 1,this Inventory
	              // contain a sunflower

public:
	Inventory(Vector2f a, int co);
	Sprite getSprite() { return spInven; }
};