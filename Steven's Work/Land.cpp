#include "Land.h"
Land::Land()
{

}
Land::Land(int num,TPosition pt)
{
	string path = "grass2.jpg";
	if ((num + 1) % 2 == 0)
	{
		path = "grass.jpg";
	}

	if (!image.loadFromFile(path, sf::IntRect(0, 0, 74, 94))) {
		std::cout << "erro" << std::endl;
	}
	spLand.setTexture(image);
	spLand.setPosition(pt.x, pt.y);
	oPoint= pt;
	spLand.setTextureRect(IntRect(0, 0, 77, 94));
	empty = true;
	//spLand.setScale(Vector2f(0.5, 0.5));
}