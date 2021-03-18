#include "Coin.hpp"
#include "Collider.hpp"
using namespace std;
using namespace sf;
Coin::Coin() = default;
Coin::Coin(Vector2f point) {
	Font font2;
	if (!font2.loadFromFile(assetFolder + "Font1.ttf")) cout << "erro " << endl;
	string path = assetFolder + "coin.png";
	Vector2f temp = point;
	oPoint = Vector2f(temp.x + 20, temp.y + 20);

	if (!image.loadFromFile(path, sf::IntRect(0, 0, 200, 200))) {
		std::cout << "erro" << std::endl;
	}

	spCoin.setPosition(oPoint.x, oPoint.y);
	spCoin.setTexture(image);
	spCoin.setScale(0.25f, 0.25f);
}
