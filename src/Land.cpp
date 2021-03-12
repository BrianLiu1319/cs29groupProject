#include "Land.h"
using namespace std;
using namespace sf;

Land::Land(int num, sf::Vector2f o)
{
	string path = "C:/Users/tommy/source/repos/jxsusilo/cs29groupProjectTrue/LATEST/assets/grass2.jpg";
	if ((num + 1) % 2 == 0)
	{
		path = "C:/Users/tommy/source/repos/jxsusilo/cs29groupProjectTrue/LATEST/assets/grass.jpg";
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


