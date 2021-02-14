#include <SFML/Graphics.hpp>
#include"SFML\Graphics.hpp"
#include"Tower.h"
#include<fstream>
#include<iostream>
#include<string>
#include "bullet.h"
#include<thread>
#include<windows.h>
#include<vector>
#include"Land.h"
using namespace std;
using namespace sf;

string path = "dog.png";
RenderWindow renderWindow(VideoMode(1000, 1000), "SFML Demo");
Event event;
TPosition positionTest = TPosition(300, 300);
Tower aTower = Tower(positionTest, path, 100);
thread moveThread;
bullet aBullet = bullet(aTower, 50);
vector<bullet>bulletList = {};// use to store all the bullet
const int widthOfLand = 74;
const int heightOfLand = 94;
//thread  MOVE control the move speed of bullet
void MOVE() {
	while (true) {
		sleep(milliseconds(60));
		for (int i = 0;i<bulletList.size();i++)// move all the bullet
			bulletList[i].getSp()->move(20, 0);
	}
}
//generate the land list to build grid(map);
vector<Land*> genrateLandList()
{
	vector<Land*>landList = {};
	int x = 50; int y = 50;
	for (int i = 0; i < 30; i++)
	{
		TPosition aPosition = TPosition(x, y);
		Land*aland = new  Land(i, aPosition);
		landList.push_back(aland) ;
		y += 94;
		if (y > 480)//if y is out of range then, change a column 
		{
			y = 50;
			x += 74;
		}
	}

	return landList;
};

//take a selected land and build the tower on this land.return the pointer of this tower
Tower* towerBuild( Land* aLand)
{
	Tower* aTower = new Tower(aLand->getOPosition(), path, 100);
	return aTower;
	
};
//calling this function to make a tower fire
void fire( Clock *clock,Tower* fireTower)
{
	Tower t = fireTower[0];
	
	int a = clock->getElapsedTime().asMilliseconds();
	if (clock->getElapsedTime().asMilliseconds() >= 1000) {// if time > = 5 sec
		bullet mBullet = bullet(t, 50);//creat a new bullet
		bulletList.push_back(mBullet);// push a bullet into list
		clock->restart();
		a = clock->getElapsedTime().asMilliseconds();
		int b = 0;
	}
	Vector2f pt = aBullet.getSp()->getPosition();
	
	for (int i = 0; i < bulletList.size(); i++) {// draw all the bullet in the vector

		renderWindow.draw(*bulletList[i].getSp());
	}
	
}


int main()
{
	


	bulletList.push_back(aBullet);

	int time = 0;
	moveThread = thread(&MOVE);
	Clock*clock = new Clock();
	// define a land
	TPosition landPoint = TPosition(50, 50);
	Land* aLand = new Land(0, landPoint);
	vector <Land*> landList;
	landList = genrateLandList();



	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(0, 0)),
		sf::Vertex(sf::Vector2f(500, 500))
	};
	line->color = Color(256, 256, 0);
	int nSelected = -1;
	Tower* pTower = NULL;

	while (renderWindow.isOpen())
	{
		while (renderWindow.pollEvent(event))
		{
			if (event.type == Event::EventType::Closed)
				renderWindow.close();

		}
		
		std::cout << "Elapsed time in microseconds: " << clock->getElapsedTime().asMilliseconds() << std::endl;
		
		// make plants shoot 1sec once
		
		/*if (clock.getElapsedTime().asMilliseconds()>=1000) {// if time > = 5 sec
			bullet mBullet = bullet(aTower, 50);//creat a new bullet
			bulletList.push_back(mBullet);// push a bullet into list
			//clock.restart();// time = 0 second
		}*/
		

		renderWindow.clear();
		// draw the landList by a for loop
		
		for (int i = 0; i < 30; i++)
		{
			renderWindow.draw(landList[i]->getSprite());
		}
		
		/*
		renderWindow.draw(aTower.getSp());
		Vector2f pt = aBullet.getSp()->getPosition();
		for (int i = 0; i < bulletList.size(); i++) {// draw all the bullet in the vector

			renderWindow.draw(*bulletList[i].getSp());
		}
		
		*/
		
		if(event.type == Event::EventType::MouseButtonPressed)// mouse event 
		{ 
			Vector2i mousepostion = Mouse::getPosition(renderWindow);// get the relative position of mouse
		
			for (int i = 0; i < 30; i++)//traverse the land list 
			{
				Sprite landSprit = landList[i]->getSprite();
				if (landSprit.getGlobalBounds().contains(mousepostion.x, mousepostion.y))// if the range of land contain the position of mouse
				{
					nSelected = i;														// the selected land is i
					break;
				}

			}
		}

		if(nSelected  >= 0 && nSelected < 30)// make sure the selected code is inthe range of 0-30
		{
			pTower = towerBuild(landList[nSelected]);	//build a tower on the selected land
			landList[nSelected]->setEmpty(false);		//set the empty of a land to false, prevent from being repeatlt use
			fire( clock, pTower);						//fire, drwa bullet list
			renderWindow.draw(pTower->getSp());			// draw the tower
		}


		renderWindow.display();
	}
    return 0;
}


