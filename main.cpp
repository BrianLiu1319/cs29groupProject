/********************************************************
 *  Deniz Erisgen
********************************************************/
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

const std::string ResourcePath = "res/";

int main() {

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "DogsnCats", sf::Style::Close | sf::Style::Resize);

	sf::RectangleShape background(sf::Vector2f(1920.0f, 1080.0f));
	sf::Texture backgroundTexture;
	sf::Vector2f BackgroundSize = background.getSize();
	backgroundTexture.loadFromFile(ResourcePath + "images/doge.png");
	background.setTexture(&backgroundTexture);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseButtonPressed:  // move star with mouse
					break;
				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::M));
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::C));
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
					break;
				default:;
			}
		}
		window.display();
	}
	return 0;
}