#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"

#include <iostream>
#include <ostream>

using namespace std;
using namespace sf;
class Coin {
	Vector2f oPoint;

	Texture image;
	Sprite spCoin;

public:
	Coin();
	explicit Coin(Vector2f point);
	~Coin() = default;
	Sprite getSp() { return spCoin; }
};
