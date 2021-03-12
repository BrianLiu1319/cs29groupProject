#ifndef Game_hpp
#define Game_hpp

#include "Collider.hpp"
#include "Inventory.h"
#include "Menu.hpp"
#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
using namespace std;
using namespace sf;

class Game : public Menu {
	const string path = "assets/doge.png";
	// assetFolder is in Screen.hpp
	const std::string clickSFXPath01 = assetFolder + "click02.wav";

	Font font1;
	Event event;
	const int widthOfLand = 74;
	const int heightOfLand = 94;
	int money = 200;
	unsigned int score = 0;

	bool gameOver = false;
	bool muteSfx = false;

	void addBullet(vector<Bullet *> &things);
	void addAttacker(vector<Attacker *> &attackers, Vector2f loc);
	void gameClock(RenderWindow &window, vector<Collider *> &things);
	void checkCollision(vector<Attacker *> &attackers,
	  vector<Bullet *> &bullets,
	  vector<Defender *> &defenders);
	vector<Land *> genrateLandList();
	vector<Inventory *> generateInvenList();
	AllTextures myTextures {};

	int howManyTower(int money);
	Defender *defenderBuild(Land *aLand);
	void fire(Clock *clock, Defender *fireTower, vector<Bullet *> bulletList);
	void drawBuiltDefender(vector<Defender *> builtTowerList,
	  RenderWindow &renderWindow);
	void showMoney(int money, RenderWindow &renderWindow);

public:
	Game(sf::Vector2f windowSize);
	int run(RenderWindow &renderWindow);
	unsigned int getScore() const { return score; }
	void toggleMuteSfx();
};

#endif /* Game_hpp */
