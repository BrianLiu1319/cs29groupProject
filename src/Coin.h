#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Time.hpp"
#include <ostream>
#include<iostream>

using namespace std;
using namespace sf;
class Coin
{

	int money = 10;
	/*int cost = 20;
	int qestion;*/
	int liveTime = 50000;
	Vector2f oPoint;
	
	Texture image;
	Sprite spCoin;
	/*Text queText;*/ //havent been using



public:
	Coin();
	Coin(Vector2f point);
	~Coin() {};

	Sprite getSp()
	{
		return spCoin;
	}
	int getMoney()
	{
		return money;
	}
	Vector2f getPos()
	{
		return oPoint;
	}

	//havent been using
	//string offerQue()
	//{
	//	questions q = questions();
	//	int b = 18; //18 is the amount 0f questions;
	//	int a = 1;
	//	srand((unsigned)time(NULL));
	//	int quesNum = (rand() % (b - a + 1)) + a;

	//	map<int, string>  quesList = q.getQues();
	//	map<int, string>  anList = q.getAns();

	//	return quesList[quesNum];
	//}



	void StepIt()
	{
		liveTime -= 1000;
	}
	int getLive()
	{
		return liveTime;
	}

};
