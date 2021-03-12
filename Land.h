#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Land {
private:
	bool empty;
	Texture image;
	Sprite spLand;

public:
	Land(int num, Vector2f o);
	Sprite getSprite() { return spLand; }
	Vector2f getVector() { return spLand.getPosition(); }
	void setEmpty(bool em) { empty = em; }
	bool getEmpty() const { return empty; }
};
