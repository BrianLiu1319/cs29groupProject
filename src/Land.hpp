#pragma once

#include "SFML/Graphics/Sprite.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>

class Land {
private:
	int width = 0;
	int height = 0;
	sf::Vector2f oPoint1;
	bool empty = false;
	sf::Texture image;
	sf::Sprite spLand;

public:
	Land() = default;
	Land(int num, sf::Vector2f o);

	// getters and setters
	void setWidth(int x) { width = x; }
	int getWidth() { return width; }
	void setHeight(int height) { height = height; }
	int getHeight() { return height; }
	sf::Sprite getSprite() { return spLand; }
	sf::Vector2f getVector() { return spLand.getPosition(); }
	void setVector(sf::Vector2f a) { oPoint1 = a; }
	void setEmpty(bool em) { empty = em; }
	bool getEnpty() { return empty; }
};
