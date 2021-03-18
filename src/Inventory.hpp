#pragma once

#include "SFML/Graphics/Sprite.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>

class Inventory {
private:
	int width = 0;
	int height = 0;

	sf::Vector2f position;
	sf::Texture image;
	sf::Sprite spInven;
	int contain;  // if contain == 0 it's a dog, if contain is 1,this Inventory
	              // contain a sunflower

public:
	Inventory() = default;
	Inventory(sf::Vector2f a, int co);
	sf::Sprite getSprite() { return spInven; }
};
