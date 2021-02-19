#pragma once
#include "Tower.h"
#include<SFML/Graphics.hpp>
#include<string.h>
#include<iostream>
#include <iostream>
class bullet
{
private:
	Tower parentTower;
	int damage;
	int speed;
	TPosition position;
	Texture bImage;
	CircleShape*spBullet;
public:
	bullet();
	bullet(Tower aTower, int aSpeed);
	Tower getTower()
	{
		return parentTower;
	};
	void setTower(Tower a) {
		parentTower = a;
	};
	int getDamage()
	{
		return damage;
	}
	void setDamage(int a)
	{
		damage = a;
	}
	int getSpeed()
	{
		return speed;
	};
	void setSpeed(int a)
	{
		speed = a;
	};
	CircleShape* getSp()
	{
		return spBullet;
	}
	//constructor:
	
	



};


