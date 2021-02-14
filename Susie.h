#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"

class Susie
{
public:
	Susie(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Susie();

	void Draw(sf::RenderWindow& window);

	Collider GetCollider() { return Collider(body); }
private:
	sf::RectangleShape body;
};

