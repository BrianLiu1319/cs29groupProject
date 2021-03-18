#pragma once

#include "SFML/Graphics/Sprite.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>

class Land {
private:
	bool empty = false;
	sf::Texture image;
	sf::Sprite spLand;

public:
	Land() = default;
	Land(int num, sf::Vector2f o);

	sf::Sprite getSprite() { return spLand; }
	sf::Vector2f getVector() { return spLand.getPosition(); }
	void setEmpty(bool em) { empty = em; }
	bool getEmpty() { return empty; }
};
