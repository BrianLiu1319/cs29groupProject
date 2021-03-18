#include "Land.hpp"
#include "FolderPath.hpp"
using namespace std;
using namespace sf;
Land::Land()
{

}

Land::Land(int num, sf::Vector2f o)
{
	//C:/Users/tommy/source/repos/jxsusilo/cs29groupProjectTrue/LATEST/assets/


	//string path = "/Users/jessicasusilo/Documents/Jessica S./DE ANZA/6 - Winter 2021/CIS 29/Project Assets/grass2.jpg";
	string path = assetFolder + "grass2.jpg";


	if ((num + 1) % 2 == 0)
	{
		//string path = "/Users/jessicasusilo/Documents/Jessica S./DE ANZA/6 - Winter 2021/CIS 29/Project Assets/grass.jpg";
		path = assetFolder + "grass.jpg";
	}

	if (!image.loadFromFile(path, sf::IntRect(0, 0, 74, 94))) {
		std::cout << "erro" << std::endl;
	}

	spLand.setTexture(image);
	spLand.setPosition(o);
	spLand.setTextureRect(IntRect(0, 0, 77, 94));
	empty = true;
	//spLand.setScale(Vector2f(0.5, 0.5));
}


