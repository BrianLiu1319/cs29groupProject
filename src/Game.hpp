#ifndef Game_hpp
#define Game_hpp
#include "Collider.hpp"
#include "Inventory.hpp"
#include "Menu.hpp"
#include "SFML/Graphics.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace sf;

class Game : public Menu {
	const string path = "assets/doge.png";
	// assetFolder is in Screen.hpp
	const string clickSFXPath01 = assetFolder + "click02.wav";
	vector<Bullet *> allBullets {};
	vector<Attacker *> allAttackers {};
	vector<Defender *> allDefenders {};
	Font font1;
	Event event;
	int money = 200;
	AllTextures allTextures {};
	vector<Land *> landList {};
	vector<Inventory *> InvenList {};
	unsigned int score = 0;
	bool gameOver = false;
	bool muteSfx = false;
	void addAttacker(vector<Attacker *> &attackers,
	  const Texture &attackerText,
	  Vector2f loc);
	void addDefender(vector<Defender *> &towers,
	  const Texture &towerTexture,
	  Vector2f loc);
	void gameClock(RenderWindow &window, vector<Collider *> &things);
	void checkCollision(vector<Attacker *> &attackers,
	  vector<Bullet *> &bullets,
	  vector<Defender *> &defenders);

	int howManyTower();
	Defender *defenderBuild(Land *aLand);
	//	void fire(Clock *clock, Defender *fireTower, vector<Bullet *> bulletList);
	void showMoney(int money, RenderWindow &renderWindow);

public:
	Game(Vector2f windowSize);
	int run(RenderWindow &renderWindow);
	unsigned int getScore() const { return score; }
	void toggleMuteSfx() override;
	void cleanUp();
};

#endif /* Game_hpp */
