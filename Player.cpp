#include "Player.h"

Player::Player(sf::Texture* texture, float speed) 
{
	this->speed = speed;
	//row = 0;

	body.setTexture(texture);
	body.setSize(sf::Vector2f(1000.0f, 1500.0f));
	body.setScale(1.0f, 1.0f);
	body.setPosition(1024.0f / 2, 768.0f / 2);

}

Player :: ~Player()
{

}

void Player::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		movement.x -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		movement.x += speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		movement.y -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		movement.y += speed * deltaTime;

	body.move(movement);
	
}

void Player:: Draw(sf::RenderWindow& window)
{
	window.draw(body);
}