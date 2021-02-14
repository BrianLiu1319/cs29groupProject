#pragma once
#include "SFML/Graphics.hpp"
#include "Collider.h"

class Player
{
public:
	Player(sf::Texture* texture, float speed);
	~Player();

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);

	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
	float speed;
	//unsigned int row;
	//bool faceRight;
};

