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
using namespace std;
using namespace sf;

string path = "pea1.jpg";
RenderWindow renderWindow(VideoMode(1000, 1000), "SFML Demo");
Event event;
TPosition positionTest = TPosition(300, 300);
Tower aTower = Tower(positionTest, path, 100);
thread moveThread;
bullet aBullet = bullet(aTower, 50);
vector<bullet>bulletList = {};// use to store all the bullet

void MOVE() {
	while (true) {
		sleep(milliseconds(60));
		for (int i = 0;i<bulletList.size();i++)// move all the bullet
			bulletList[i].getSp()->move(20, 0);
	}
}
int main()
{
	bulletList.push_back(aBullet);
    /*
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    */
	int time = 0;
	moveThread = thread(&MOVE);
	Clock clock;
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(0, 0)),
		sf::Vertex(sf::Vector2f(300, 300))
	};
	line->color = Color(256, 256, 0);
	while (renderWindow.isOpen())
	{
		while (renderWindow.pollEvent(event))
		{
			if (event.type == Event::EventType::Closed)
				renderWindow.close();

		}
		
		std::cout << "Elapsed time in microseconds: " << clock.getElapsedTime().asMilliseconds() << std::endl;
		
		
		if (clock.getElapsedTime().asMilliseconds()>=1000) {// if time > = 5 sec
			bullet mBullet = bullet(aTower, 50);//creat a new bullet
			bulletList.push_back(mBullet);// push a bullet into list
			clock.restart();// time = 0 second
		}


		renderWindow.clear();
		

		renderWindow.draw(aTower.getSp());
		Vector2f pt = aBullet.getSp()->getPosition();
		for (int i = 0; i < bulletList.size(); i++) {// draw all the bullet in the vector
			renderWindow.draw(*bulletList[i].getSp());
		}
		
		
		renderWindow.display();
		
	}





    return 0;
}


