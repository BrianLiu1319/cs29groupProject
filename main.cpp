/********************************************************
 *  Deniz Erisgen
********************************************************/
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string>
#include "Interface.h"

const std::string ResourcePath = "res/";
using namespace sf;

int main() {
	srand(time(NULL));
	RenderWindow window(VideoMode(1280, 720), "DogsnCats", Style::Close | Style::Resize);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	Texture backgroundTexture;
	backgroundTexture.loadFromFile(ResourcePath + "images/doge.png");
	Sprite bgSprite;
	bgSprite.setPosition((window.getSize().x / 2)-(backgroundTexture.getSize().x / 2),(window.getSize().y / 2)- (backgroundTexture.getSize().y /2));
	bgSprite.setTexture(backgroundTexture);

	while (window.isOpen()) {
		Event event{};
		while (window.pollEvent(event)) {
			switch (event.type) {
				case Event::Closed:
					window.close();
					break;
				case Event::MouseButtonPressed:  // move star with mouse
					break;
				case Event::KeyPressed:
					if (Keyboard::isKeyPressed(Keyboard::M));
					if (Keyboard::isKeyPressed(Keyboard::C));
					if (Keyboard::isKeyPressed(Keyboard::Right));
					if (Keyboard::isKeyPressed(Keyboard::Left));
					if (Keyboard::isKeyPressed(Keyboard::Up));
					if (Keyboard::isKeyPressed(Keyboard::Down));
					break;
				default:;
			}
		}
		window.clear();
		window.draw(bgSprite);
		window.display();
	}
	return 0;
}