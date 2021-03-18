#include "FolderPath.hpp"
#include "Inventory.hpp"
using namespace std;
using namespace sf;

Inventory::Inventory(Vector2f pt, int co) {
	string path;
	if (co == 0) {
		path = assetFolder + "coinMakerThumbnail.png";
	} else if (co == 1) {
		path = assetFolder + "dogSprite3Thumbnail.png";
	} else if (co == 2) {
		path = assetFolder + "dogSprite1Thumbnail.png";
	}

	if (!image.loadFromFile(path, sf::IntRect(0, 0, 54, 54))) { std::cout << "error" << std::endl; }

	spInven.setTexture(image);
	spInven.setPosition(pt);
	spInven.setTextureRect(IntRect(0, 0, 54, 54));
}
