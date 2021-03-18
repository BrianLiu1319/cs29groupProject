#include "FolderPath.hpp"
#include "Land.hpp"
using namespace std;
using namespace sf;

Land::Land(int num, sf::Vector2f o) {
	string path = assetFolder + "grass2.jpg";

	if ((num + 1) % 2 == 0) { path = assetFolder + "grass.jpg"; }

	if (!image.loadFromFile(path, sf::IntRect(0, 0, 74, 94))) { std::cout << "erro" << std::endl; }

	spLand.setTexture(image);
	spLand.setPosition(o);
	spLand.setTextureRect(IntRect(0, 0, 77, 94));
	empty = true;
}
