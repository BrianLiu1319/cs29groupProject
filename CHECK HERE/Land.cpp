#include "Land.h"
using namespace std;
using namespace sf;
Land::Land()
{

}

Land::Land(int num, sf::Vector2f o)
{
	string path = "C:/temp/grass2.jpg";
	if ((num + 1) % 2 == 0)
	{
		path = "C:/temp/grass.jpg";
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


