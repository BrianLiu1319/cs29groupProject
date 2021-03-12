#include "Land.h"

Land::Land(int num, sf::Vector2f o) {
	string path = "/res/images/grass2.jpg";
	if ((num + 1) % 2 == 0) { path = "/res/images/grass.jpg"; }
	if (!image.loadFromFile(path, IntRect(0, 0, 74, 94))) { cout << "erro" << endl; }
	spLand.setTexture(image);
	spLand.setPosition(o);
	spLand.setOrigin(image.getSize().x / 2.0f, image.getSize().y / 2.0f);
	spLand.setTextureRect(IntRect(0, 0, 77, 94));
	empty = true;
	// spLand.setScale(Vector2f(0.5, 0.5));
}
