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
#include"Inventory.h"
using namespace std;
using namespace sf;
//programmer: Youhao Chen (Steven)  if you have any question feel free to ask me. 



string path = "dog.png";
Font font1;
RenderWindow renderWindow(VideoMode(1000, 1000), "SFML Demo");
Event event;
TPosition positionTest = TPosition(300, 300);
Tower aTower = Tower(positionTest, path, 100);
thread* moveThread;
bullet aBullet = bullet(aTower, 50);
vector<bullet>bulletList = {};// use to store all the bullet
const int widthOfLand = 74;
const int heightOfLand = 94;
int money = 200;
bool bThread = true;
bool bExitThread = false;
//thread  MOVE control the move speed of bullet
void MOVE() {
	while (bThread) {
		sleep(milliseconds(60));
		for (int i = 0;i<bulletList.size();i++)// move all the bullet
			bulletList[i].getSp()->move(20, 0);
	}
	bExitThread = true;
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
// this function creat a inventory vector which stores all invertory
vector<Inventory*>generateInvenList()
{
	vector<Inventory*> InvenList = {};
	int x = 50; int y = 600;
	for (int i = 0; i < 2; i++)
	{
		TPosition aPosition = TPosition(x, y);
		Inventory* aInven = new Inventory(aPosition,i);
		InvenList.push_back(aInven);
		x += 60;
		
	}
	return InvenList;


}
// this function put 30 towers would be used into a vector
vector<Tower*>generateTowerList(vector <Land*> landList)
{
	vector<Tower*> towerList = {};
	int x = 0;
	int y = 0;
	for (int i = 0; i < 30; i++)
	{
		x = landList[i]->getOPosition().x;
		y = landList[i]->getOPosition().y;
		TPosition aPosition = TPosition(x, y);
		Tower* aInven = new Tower(aPosition,path ,100);
		towerList.push_back(aInven);

	}
	return towerList;


}

//this function cauculate how many towers we could build
int howManyTower(int money)
{
	Tower* aTower = new Tower();
	int cost = aTower->getCost();
	vector<Tower*> TowerList= {};
	int amount = money / cost;
	return amount;

}
//take a selected land and build the tower on this land.return the pointer of this tower
Tower* towerBuild( Land* aLand)
{
	Tower* aTower = new Tower(aLand->getOPosition(), path, 100);
	return aTower;
	
};
//calling this function to make a tower fire
void fire(Clock* clock, Tower* fireTower)
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

};
//this function draw all the towers which we have alrady built
void drawBuiltTower(vector <Tower*> builtTowerList)
{
	for (int i = 0; i < builtTowerList.size(); i++)
	{
		renderWindow.draw(builtTowerList[i]->getSp());
	}
};
//This function define a textview that shows the how much money user has. 
void showMoney(int money)
{
	
	Text showMoney;
	string show = "Money:  "+to_string(money);
	showMoney.setFont(font1);
	showMoney.setFillColor(sf::Color::Red);
	showMoney.setString(show);
	showMoney.setPosition(800, 100);
	showMoney.setCharacterSize(20);
	showMoney.setStyle(sf::Text::Regular);
	renderWindow.draw(showMoney);

}

int main()
{
	
	if (!font1.loadFromFile("font1.ttf"))
		cout << "erro " << endl;


	bulletList.push_back(aBullet);
	
	
	
	int towerInStore = 5; 

	int time = 0;
	moveThread = new thread(&MOVE);
	Clock*clock = new Clock();
	// define a land
	TPosition landPoint = TPosition(50, 50);
	Land* aLand = new Land(0, landPoint);
	vector <Land*> landList;		//vector to store the land, you can think this vector is the grass grid!
	vector<Inventory*> InvenList;
	vector<Tower*> towerList;		//This ia a vector stores all towers
	vector<Tower*> builtTowerList;// this a vector only stores the towers which has been built;
	int nInvenselected = -1;		//This int is a counter; represent the Inventory user selected; if user didnt select; it is -1;


	InvenList = generateInvenList();	// creat the Inventory list
	landList = genrateLandList();		// creat land list
	towerList = generateTowerList(landList);	// creat towerList




	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(0, 0)),
		sf::Vertex(sf::Vector2f(500, 500))
	};
	line->color = Color(256, 256, 0);
	int nSelected = -1;
	//vector<Tower*> towerList = {};
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
		
		/*if (clock.getElapsedTime().asMilliseconds()>=1000) {// if time > = 5 sec		//useless code
			bullet mBullet = bullet(aTower, 50);//creat a new bullet
			bulletList.push_back(mBullet);// push a bullet into list
			//clock.restart();// time = 0 second
		}*/
		

		renderWindow.clear();
		
		
		showMoney(money);
		// draw the landList(grid) by a for loop
		for (int i = 0; i < 30; i++)
		{
			renderWindow.draw(landList[i]->getSprite());
		}
		//draw InvenList below the grid
		for (int i = 0; i < 2; i++)
		{
			renderWindow.draw(InvenList[i]->getSprite());
		}
		
		

		if (event.type == Event::EventType::MouseButtonPressed)
		{
			Vector2i mousePressPosition = Mouse::getPosition(renderWindow);
			for (int i = 0; i < 2; i++)
			{
				Sprite InvenSp = InvenList[i]->getSprite();
				if (InvenSp.getGlobalBounds().contains(mousePressPosition.x, mousePressPosition.y))// if the range of a inventory contain the position of mouse
				{
					if (towerInStore > 0)
					{
						nInvenselected = i;														// the selected Inventory is i
						
					}
					
					break;
				}
			}

		}
		
		if(event.type == Event::EventType::MouseButtonReleased&&nInvenselected!=-1)// mouse event 
		{ 
			Vector2i mouseRepostion = Mouse::getPosition(renderWindow);// get the relative position of mouse (get where custom release button)
			//that's also where user want to build a tower
			
			for (int i = 0; i < 30; i++)//traverse the land list 
			{
				Sprite landSprit = landList[i]->getSprite();
				if (landSprit.getGlobalBounds().contains(mouseRepostion.x, mouseRepostion.y))// if the range of land contain the position of mouse
				{
					nSelected = i;														// the selected land is i
					break;
				}

			}
			
		}


		if(nSelected  >= 0 && nSelected < 30 && nInvenselected<2 && nInvenselected>-1)// make sure the selected code is inthe range of 0-30, the inventory shouldnt be -1
		{
			//pTower = towerBuild(landList[nSelected]);//build a tower on the selected land// last version code, useless now
			
			landList[nSelected]->setEmpty(false);		//set the empty of a land to false, prevent from being repeatly use
			//fire( clock, pTower);						//fire, drwa bullet list//last version fire useless now(case fire in this test version)
			builtTowerList.push_back(towerList[nSelected]);	//firstly put the select tower in to the list of towers which have been already built!

			money -= towerList[nSelected]->getCost();		// user' money should minus the cost of selected tower default cost of a tower is 40;
			nInvenselected = -1;							//now we finish all things we should make nInven back to -1; To prepare for next action;
			nSelected = -1;									//the selected land should also back to -1 
			towerInStore = howManyTower(money);				// this statement get how many tower we can build with rest money
		}
		
		if (builtTowerList.size() > 0) { drawBuiltTower(builtTowerList); }// If the number of towers that have been built is not zero, we draw the towers that have been built


		
		renderWindow.display();
	}
	bThread = false;
	while (!bExitThread)		//this make the thread sleep after user close window 
	{
		sleep(milliseconds(100));
	}
    return 0;
}


