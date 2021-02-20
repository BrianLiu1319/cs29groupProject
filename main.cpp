/********************
 *  Deniz Erisgen
 *  Group Project
 *  Compiler:GCC
********************/
#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <vector>
#include "Collider.h"

using namespace sf;
using std::cout;
using std::vector;
using std::endl;

int main() {
	srand(time(NULL));
	RenderWindow window(VideoMode(1280, 720), "DogsnCats", Style::Close | Style::Resize);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	Sprite bgSprite;
	std::string resPath = ResourcePath + "sprites/doge.png";
	Bullet testBulletOne = Bullet(resPath);
	testBulletOne.setPosition((window.getSize().x / 2) - (testBulletOne.getGlobalBounds().width / 2),
	                          (window.getSize().y / 2) - (testBulletOne.getGlobalBounds().height / 2));

	while (window.isOpen()) {
		Event event {};
		while (window.pollEvent(event)) {
			switch (event.type) {
				case Event::Closed:
					window.close();
					break;
				case Event::MouseButtonPressed:
					break;
				case Event::KeyPressed:
					if (Keyboard::isKeyPressed(Keyboard::M)) ;
					else if (Keyboard::isKeyPressed(Keyboard::C));

					else if (Keyboard::isKeyPressed(Keyboard::Right))
						testBulletOne.move(1.0f, 0.0f);
					if (Keyboard::isKeyPressed(Keyboard::Left))
						testBulletOne.move(-1.0f, 0.0f);
					if (Keyboard::isKeyPressed(Keyboard::Up))
						testBulletOne.move(0.0f, -1.0f);
					if (Keyboard::isKeyPressed(Keyboard::Down))
						testBulletOne.move(0.0f, 1.0f);
					break;
				default:;
			}
		}
		testBulletOne.travel();
		cout << testBulletOne.getOrigin().y << testBulletOne.getOrigin().x << " --- " << testBulletOne.getPosition().x
		     << " -- " << testBulletOne.getPosition().y << endl;
//      gameclock();
		window.clear();
//		window.draw(bgSprite);
		window.draw(testBulletOne);
		window.display();
	}
	return 0;
}


void gameClock() {
	// all goes in here
}