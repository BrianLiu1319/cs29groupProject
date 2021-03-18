#include "Inventory.hpp"
#include "FolderPath.hpp"
using namespace std;
using namespace sf;
Inventory::Inventory()
{

}
Inventory::Inventory(Vector2f pt, int co)
{
//C:/Users/tommy/source/repos/jxsusilo/cs29groupProjectTrue/LATEST/assets/
	string path = assetFolder + "play button.png";

	//string path = "/Users/jessicasusilo/Documents/Jessica S./DE ANZA/6 - Winter 2021/CIS 29/Project Assets/play button.png";
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
	//spLand.setScale(Vector2f(0.5, 0.5));

}
