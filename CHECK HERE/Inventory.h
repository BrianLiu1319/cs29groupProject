#pragma once
#include<SFML/Graphics.hpp>
#include "SFML/Graphics/Sprite.hpp"
#include<string.h>
#include<iostream>
class Inventory
{
private:
	int width;
	int height;
	/*
	TPosition centerPosition;
	TPosition oPoint;
	*/
	sf::Vector2f position;
	sf::Texture image;
	sf::Sprite spInven;
	int contain;//if contain == 0 it's a dog, if contain is 1,this Inventory contain a sunflower


public:

	//Inventory(TPosition pt, int co);
	Inventory(sf::Vector2f a, int co);
	Inventory();
	sf::Sprite getSprite()
	{
		return spInven;
	}


};