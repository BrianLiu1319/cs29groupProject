#pragma once
#include<SFML/Graphics.hpp>
#include<string.h>
#include<iostream>
#include <iostream>

using namespace std;
using namespace sf;
struct TPosition
{
	int x;
	int y;
	TPosition(int a, int b) {
		x = a;
		y = b;
	}
	TPosition()
	{
		x = 0;
		y = 0;
	}
};
class Tower
{
private:
	int nHp;
	int ndamage;
	int cost;
	int attactSpeed;
	TPosition position;
	Texture image;
	Sprite spTower;
public:

	
	Sprite getSp() {
		return spTower;
	};
	int getnHp(int hp)
	{
		return nHp;
	};
	void setnHp(int hp)
	{
		nHp = hp;
	};
	int getDamage()
	{
		return ndamage;
	};
	void setDamage(int ad)
	{
		ndamage = ad;

	};
	int getCost()
	{
		return cost;
	};
	void setCost(int ad)
	{
		cost = ad;

	};

	int getAttactSpeed()
	{
		return attactSpeed;
	};
	void setAttactSpeed(int ad)
	{
		attactSpeed = ad;

	};
	TPosition getPosition()
	{
		return position;
	}
	void setPosition(TPosition p)
	{
		position = p;
	}
	void fire() {};
	void death() {};
	void build() {};
	Tower();
	Tower(TPosition pt, string path, int hp);

};

