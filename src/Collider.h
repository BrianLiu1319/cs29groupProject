#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Time.hpp"
#include <ostream>
#include "Animation.hpp"
#include "Coin.h"

using namespace std;
using namespace sf;
//Res const path
// This is the only place to change the sprite file

/*
static const string bulSpritePath = "res/sprites/bul.png";
static const string catSpritePath = "res/sprites/cat1.png";
static const string towerSpritePath = "res/sprites/tower.png";
*/
//	C:/Users/tommy/source/repos/jxsusilo/cs29groupProjectTrue/LATEST/assets //

// Tommy's Files 

static const string bulSpritePath = "C:/Users/tommy/source/repos/jxsusilo/cs29groupProjectTrue/LATEST/assets/bul.png";
static const string catSpritePath = "C:/Users/tommy/source/repos/jxsusilo/cs29groupProjectTrue/LATEST/assets/catSprites1.png";
static const string towerSpritePath = "C:/Users/tommy/source/repos/jxsusilo/cs29groupProjectTrue/LATEST/assets/tower.png";
static const string dogeTower = "C:/Users/tommy/source/repos/jxsusilo/cs29groupProjectTrue/LATEST/assets/dogSprites2.png";


//Uncomment back for Jessica ;)

/*
static const string bulSpritePath = "/Users/jessicasusilo/Documents/Jessica S./DE ANZA/6 - Winter 2021/CIS 29/Project Assets/bul.png";
static const string catSpritePath = "/Users/jessicasusilo/Documents/Jessica S./DE ANZA/6 - Winter 2021/CIS 29/Project Assets/catSprites1.png";
static const string towerSpritePath = "/Users/jessicasusilo/Documents/Jessica S./DE ANZA/6 - Winter 2021/CIS 29/Project Assets/tower.png";
static const string dogeTower = "/Users/jessicasusilo/Documents/Jessica S./DE ANZA/6 - Winter 2021/CIS 29/Project Assets/dogSprites2.png";
*/

static const unsigned WINDOW_WIDTH = 1280;
static const unsigned WINDOW_HEIGHT = 720;

const int MONEYMAKERCOST = 20;
const int MONEYPERCOIN = 10;

// direction types for Auto Travel
enum DIRECTION {
	LEFT, RIGHT, TWR
};

class Collider : public Sprite {
protected:
	int health;
	float speed;
	bool status = true;
	Texture textureOfObject{ Texture() };
	string spritePath;
	DIRECTION defaultDirection;
	Vector2f position;
	bool isMaker = false;

	Collider() = default;
	Collider(const string& textureFileName, DIRECTION direction, Vector2f positionOfObj = { 0, 0 }, int objHealth = 100, float objSpeed = 60.0f);
	Collider(const Texture& textureTemp, DIRECTION direction, Vector2f positionOfObj,  int objHealth = 20, float objSpeed = 60.0f);
	// remove other.health - this.health and trigger hurt animation
    
	friend ostream& operator <<(ostream& os, const Collider& collider);
	//	Collider(int health, int speed) : health(health), speed(speed) { }
	//	Collider(int health) : health(health), speed(60) { }
		// will be deleted
	string typeName() const;
	~Collider() override { cout << "Collider Destructor" << endl; }
	void autoTravel(DIRECTION direction);
public:
	void setStatus() { status = false; };
	bool getStatus() { return status; };
	int getHealth() const { return health; };
    virtual void animate() {}               // animate object
	void setDirection(DIRECTION ab) { defaultDirection = ab; }
	virtual void hurt(Collider& other);
	virtual void updateObject();          // call funcs to calculate or whatever is needed to be done
};

class Bullet : public Collider {
public:
	Bullet() : Collider(bulSpritePath, RIGHT, { 25, 360 }, 25) { scale(0.1, 0.1); }
	Bullet(sf::Vector2f a) : Collider(bulSpritePath, RIGHT, a, 50) { scale(0.1, 0.1); }
	Bullet(const sf::Texture& temp, sf::Vector2f a) : Collider(temp, RIGHT, a) { scale(0.1, 0.1); }
	//Bullet() : 

	//	Bullet(int damagePoint) : Collider(damagePoint) { }

	//	Bullet(int damagePoint, int movementSpeed) : Collider(damagePoint, movementSpeed) { }
};

class coinMaker : public Collider
{
private:
	int period;

	vector<Coin*> coins = {};
	int cost = MONEYMAKERCOST;

	bool bGenerate = true;
	bool bCheck = true;

	Thread* m_pGenerate = nullptr;	//generating thread
	Thread* m_pCheck = nullptr;		//checking thread
	Mutex mMutex;
	/*Texture makerImage;
	Sprite spMaker;*/
	//TPosition position;

public:
	coinMaker()
	{

	};
	//coinMaker(sf::Vector2f a) : Collider(moneyMakerPath, RIGHT, { a.x + 37.0f, a.y + 47.0f }, 100, 0.0f) { scale(1, 1); };
	coinMaker(Vector2f pt)
	{
		string path = "coinMaker.png";
		if (!textureOfObject.loadFromFile(path, sf::IntRect(0, 0, 77, 94))) {
			std::cout << "erro" << std::endl;
		}
		setTexture(textureOfObject);
		setPosition(pt.x, pt.y);
		position = pt;
		setTextureRect(IntRect(0, 0, 77, 94));


		m_pGenerate = new Thread(coinMaker::gernateCoin, this);
		m_pGenerate->launch();
		m_pCheck = new Thread(coinMaker::checkLive, this);
		m_pCheck->launch();
		isMaker = true;
	}

	~coinMaker()
	{
		bGenerate = false;
		bCheck = false;
	}
	int getCost()
	{
		return cost;
	}
	int howmanyCoininBox()
	{
		return coins.size();
	}
	void drawCoins(RenderWindow& renderWindow)
	{
		mMutex.lock();

		for (int i = 0; i < coins.size(); i++)
		{
			Coin* pCoin = coins[i];
			renderWindow.draw(coins[i]->getSp());
		}
		mMutex.unlock();

	}
	//this function return the money of coinmaker. Money = coin's value * the amount of coins.
	int clearCoin()
	{

		int counter = coins.size();//amount of coins vector;
		Coin* pCoin = coins[0];
		int value = pCoin->getMoney();

		int money = counter * value; //the total vaule of coin vector is vaule of each coin * amount of coins.

		coins.clear();				// clear coins vector.Because they are already collected.
		return money;

	}

	//this function use a thread to generate coins every 8seconds
	static void gernateCoin(coinMaker* pThis)
	{
		//thread
		while (pThis->bGenerate)
		{
			for (int i = 0; i < 80; i++) //8 seconds colck.
			{
				if (!pThis->bGenerate)
					break;
				sleep(milliseconds(100));
			}
			if (!pThis->bGenerate)
				break;
			if (pThis->coins.size() < 1)
			{
				Coin* pCoin = new Coin(pThis->position);
				pThis->mMutex.lock();
				pThis->coins.push_back(pCoin);
				pThis->mMutex.unlock();
			}



		}

	}
	static void checkLive(coinMaker* pThis)
	{
		while (pThis->bCheck)
		{

			pThis->mMutex.lock();
			if (pThis->coins.size() > 0)
			{
				for (vector<Coin*>::iterator it = pThis->coins.end() - 1; it != pThis->coins.begin(); it--)
				{
					Coin* pCoin = *it;
					pCoin->StepIt();
					if (pCoin->getLive() <= 0)
					{
						delete pCoin;
						pThis->coins.erase(it);
					}
				}
			}
			pThis->mMutex.unlock();
			sleep(milliseconds(3000));
		}
	}

};

