#include "Tower.h"
#include<SFML/Graphics.hpp>
#include<string.h>
#include<iostream>
#include <iostream>

using namespace std;
using namespace sf;

Tower::Tower(TPosition pt, string path, int hp)
{
	
	if (!image.loadFromFile(path, sf::IntRect(0, 0, 77, 94))) {
		std::cout << "erro" << std::endl;
	}
	
	spTower.setTexture(image);
	spTower.setPosition(pt.x, pt.y);
	position = pt;
	spTower.setTextureRect(IntRect(0, 0, 77, 94));
	//spTower.setScale(Vector2f(0.5, 0.5));
	nHp = hp;
}
Tower::Tower()
{

}