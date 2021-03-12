#include "Inventory.hpp"

Inventory::Inventory(Vector2f pt, int co) {
	string path = "assets/inv.png";
	width = 54;
	height = 54;

	if (!image.loadFromFile(path, sf::IntRect(0, 0, 54, 54))) {
		std::cout << "erro" << std::endl;
	}
	spInven.setTexture(image);
	spInven.setPosition(pt);
	position = pt;
	spInven.setTextureRect(IntRect(0, 0, 54, 54));
	contain = co;
	// spLand.setScale(Vector2f(0.5, 0.5));
}