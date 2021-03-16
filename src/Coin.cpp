#include "Coin.h"
#include"Collider.h"
using namespace std;
using namespace sf;
// coder: Youhao Chen (steven)
//description: coin.cpp include constructors of coin
Coin::Coin()
{

}
Coin::Coin(Vector2f point)
{
	Font font2;
	if (!font2.loadFromFile("font1.ttf"))
		cout << "erro " << endl;
	//string path = "coin.png";
	string path = "C:/Users/tommy/source/repos/jxsusilo/cs29groupProjectTrue/LATEST/assets/coin.png";
	Vector2f temp = point;
	oPoint = Vector2f(temp.x + 20, temp.y + 20);

	if (!image.loadFromFile(path, sf::IntRect(0, 0, 60, 60))) {
		std::cout << "erro" << std::endl;
	}

	spCoin.setPosition(oPoint.x, oPoint.y);
	spCoin.setTexture(image);
	//money = 20;
	//havent been using
	/*string ques = offerQue();
	queText.setFont(font2);
	queText.setFillColor(sf::Color::Red);
	queText.setString(ques);
	queText.setPosition(oPoint.x + 10, oPoint.y+10);
	queText.setCharacterSize(10);
	queText.setStyle(sf::Text::Regular);*/



}