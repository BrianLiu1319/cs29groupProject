/********************
 *  Deniz Erisgen
 *  Group Project
 *  Compiler:GCC
********************/
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string>
#include <iostream>
#include "Collider.h"

using namespace sf;
using std::cout;
using std::endl;
static const std::string ResourcePath = "res/";

int main() {
	srand(time(NULL));
	RenderWindow window(VideoMode(1280, 720), "DogsnCats", Style::Close | Style::Resize);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	Texture backgroundTexture;
	backgroundTexture.loadFromFile(ResourcePath + "sprites/doge.png");
	Sprite bgSprite;
	bgSprite.setPosition((window.getSize().x / 2)-(backgroundTexture.getSize().x / 2),(window.getSize().y / 2)- (backgroundTexture.getSize().y /2));
	bgSprite.setTexture(backgroundTexture);
	Defender some = Defender();
	Bullet b1 = Bullet();
	cout << some << endl << b1 << endl;
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
					else if (Keyboard::isKeyPressed(Keyboard::C));
					else if (Keyboard::isKeyPressed(Keyboard::Right));
					else if (Keyboard::isKeyPressed(Keyboard::Left));
					else if (Keyboard::isKeyPressed(Keyboard::Up));
					else if (Keyboard::isKeyPressed(Keyboard::Down));
					break;
				default:;
			}
		}
		window.clear();
		//window.draw(bgSprite);
		window.display();
	}
	return 0;
}



