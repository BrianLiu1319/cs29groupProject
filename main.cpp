#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Collider.h"
#include "Susie.h"
#include <iostream>
#include <string>
using namespace sf;
using std::cout;
using std::endl;
using std::string;

void moveMario(const string& direction, const RenderWindow& window, Sprite& mario);
void moveMario1(const string& direction, const RenderWindow& window, Sprite& mario);

int main()
{
	RenderWindow window(VideoMode(1024, 768), "SFML Sprite Move Demo", sf::Style::Close);
	Event event;

	// Render window background
	sf::RectangleShape background(sf::Vector2f(1024.0f, 768.0f));
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile(std::string("C:/temp/MapDBD.png"));
	background.setTexture(&backgroundTexture);

	// Create sprite
	sf::Texture marioTexture;
	//marioTexture.loadFromFile("C:/temp/mario.png");

	sf::Texture susieTexture;
	//susieTexture.loadFromFile("C:/temp/Susie.png");

	// Text is Nullptr, but can use loaded textures instead
	Player player(nullptr, sf::Vector2f(400.0f, 400.0f), 100.0f);
	Susie susie(nullptr, sf::Vector2f(400.0f, 400.0f), sf::Vector2f(200.0f, 200.0f));

	/*
	* 
	sf::Sprite marioSprite(marioTexture);
	marioSprite.setScale(0.333f, 0.333f);
	marioSprite.setPosition(1024.0f/2, 768.0f/2);

	*/

	// Sound
	
	sf::SoundBuffer buffer;
	sf::Sound sound;


	if (!buffer.loadFromFile("oisusie.ogg"))
		return -1;
	sound.setBuffer(buffer);
	//sound.setPitch(0.6f);
	sound.setVolume(12.f);

	bool noDraw = false;
	
	// Time
	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Sound::Status Status;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
				
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) window.close();
				/*
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) moveMario("up", window, marioSprite);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) moveMario("down", window, marioSprite);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) moveMario("left", window, marioSprite);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) moveMario("right", window, marioSprite);
				else;
			default:
				;
				*/
				
			}
		}
		
		player.Update(deltaTime);
		

		// Checks if it's collided and if so, remove the collided object. 
		if (!noDraw)
		{
			if (susie.GetCollider().CheckCollision(player.GetCollider()))
			{
				noDraw = true;
				Status = sound.getStatus();

				if (Status == sf::Music::Status::Stopped)
				{
					sound.play();
				}
			}
			else
			{
				noDraw = false;
			}
		}

		window.clear(sf::Color(150, 150, 150));
		window.draw(background);
		player.Draw(window);
		if (!noDraw)
		{
			susie.Draw(window);
		}
		window.display();
	}
}

// consider set position back to left if it's too far right ? 

void moveMario(const string& direction, const RenderWindow& window, Sprite& mario)
{
	// delta is 1% of render window size
	sf::Vector2f delta = sf::Vector2f(window.getSize().x / 100.f, window.getSize().y / 100.f);
	sf::Vector2f position = mario.getPosition();
	if (direction == "up") mario.setPosition(position.x, position.y - delta.y);
	if (direction == "down") mario.setPosition(position.x, position.y + delta.y);
	if (direction == "left") mario.setPosition(position.x - delta.x, position.y);
	if (direction == "right") mario.setPosition(position.x + delta.x, position.y);
}

void moveMario1(const string& direction, const RenderWindow& window, Sprite& mario)
{
	// delta is 1% of render window size
	sf::Vector2f delta = sf::Vector2f(window.getSize().x / 100000.f, window.getSize().y / 100000.f);
	sf::Vector2f position = mario.getPosition();
	if (direction == "right") mario.setPosition(position.x + delta.x, position.y);
}
