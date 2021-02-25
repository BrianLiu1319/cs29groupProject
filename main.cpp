/********************
 *  Deniz Erisgen
 *  Group Project
 *  Compiler:GCC
********************/
#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <vector>
#include "Collider.hpp"

using namespace sf;
using std::cout;
using std::vector;
using std::endl;
static const std::string ResourcePath = "res/";

int main() {
	srand(time(NULL));
	RenderWindow window(VideoMode(1280, 720), "DogsnCats", Style::Close | Style::Resize);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	Sprite bgSprite;
	std::string resPath = ResourcePath + "sprites/doge.png";
	Bullet bulletzz = Bullet(resPath);
	bulletzz.setPosition ((window.getSize().x / 2) - (bulletzz.getGlobalBounds().width / 2), (window.getSize().y / 2) - (bulletzz.getGlobalBounds().height / 2));
	while (window.isOpen()) {
		Event event{};
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
							bulletzz.move(1.0f, 0.0f);
						if (Keyboard::isKeyPressed(Keyboard::Left))
						bulletzz.move(-1.0f, 0.0f);
					    if (Keyboard::isKeyPressed(Keyboard::Up))
						bulletzz.move(0.0f, -1.0f);
					    if (Keyboard::isKeyPressed(Keyboard::Down))
						bulletzz.move(0.0f, 1.0f);
					break;
				default:;
			}
		}
		bulletzz.autoTravel();
		cout << bulletzz.getOrigin().y << bulletzz.getOrigin().x << " --- " << bulletzz.getPosition().x << " -- " << bulletzz.getPosition().y << endl;
//      gameclock();
		window.clear();
//		window.draw(bgSprite);
		window.draw(bulletzz);
		window.display();
	}
	return 0;
}


void gameClock() {
	// all goes in here
}