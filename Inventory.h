#pragma once
#include"Tower.h"
class Inventory
{
private:
	int width;
	int height;
	TPosition centerPosition; 
	TPosition oPoint;
	
	Texture image;
	Sprite spInven;
	int contain;//if contain == 0 it's a dog, if contain is 1,this Inventory contain a sunflower


public:
	Inventory(TPosition pt,int co);
	Inventory();
	Sprite getSprite()
	{
		return spInven;
	}


};

