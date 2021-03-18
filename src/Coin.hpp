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
	int money = 10;
	int liveTime = 50000;
	Vector2f oPoint;

	Texture image;
	Sprite spCoin;

public:
	Coin();
	Coin(Vector2f point);
	~Coin() {};

	Sprite getSp() { return spCoin; }
	int getMoney() { return money; }
	Vector2f getPos() { return oPoint; }

	void StepIt() { liveTime -= 1000; }
	int getLive() { return liveTime; }
};
