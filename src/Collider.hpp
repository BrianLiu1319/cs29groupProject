#ifndef COLLIDER_H
#define COLLIDER_H
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"

#include <iostream>

using namespace std;
using namespace sf;



static const unsigned WINDOW_WIDTH = 1280;
static const unsigned WINDOW_HEIGHT = 720;

// direction types for Auto Travel
enum DIRECTION { LEFT, RIGHT, TWR };

class Collider : public Sprite {
protected:
	int health;
	float speed;
	Texture textureOfObject {Texture()};
	DIRECTION defaultDirection;
	Vector2f position;

	Collider(const Texture &textureTemp,
	  DIRECTION direction,
	  Vector2f positionOfObj,
	  int objHealth = 10,
	  float objSpeed = 60.0f);
	virtual void animate() {};  // animate object
	void autoTravel(DIRECTION direction);

public:
	int getHealth() const { return health; }
	void setDirection(DIRECTION ab) { defaultDirection = ab; }
	virtual void hurt(Collider &other);
	virtual void
	updateObject();  // call funcs to calculate or whatever is needed to be done
};

class Bullet : public Collider {
public:
	Bullet(const Texture &temp, Vector2f loc) : Collider(temp, RIGHT, loc, 25) {
		scale(0.05, 0.05);
		speed = 15;
	}
};

class Attacker : public Collider {
public:
	void attack() {}
	//	void hurt(Collider &other) override;
	Attacker(const Texture &catTexture, Vector2f loc) :
	    Collider(catTexture, LEFT, {WINDOW_WIDTH, loc.y}, 100, 10.0f) {
		scale(0.5, 0.5);
	};
};

class Defender : public Collider {
public:
	void fire(vector<Bullet *> &bulletsList, const Texture &bulletTextrue);
	Defender(const Texture &towerTexture, Vector2f loc) :
	    Collider(towerTexture, TWR, {loc.x, loc.y}, 100, 0) {
		scale(0.5, 0.5);
	};
};

class AllTextures {
	const string bulSpritePath = "assets/bul.png";
	const string catSpritePath = "assets/cat1.png";
	const string towerSpritePath = "assets/doge.png";
	const string landSpritePath = "assets/grass.jpg";
	const string landSpritePath2 = "assets/grass2.jpg";
	const string inventoryPath = "assets/inv.png";
	Texture *bullet;
	Texture *tower;
	Texture *attacker;
	Texture *land;
	Texture *land2;
	Texture *inv;

public:
	AllTextures();
	~AllTextures() {
		delete bullet;
		delete tower;
		delete attacker;
		delete land;
		delete land2;
		delete inv;
	}
	Texture &getBullet() const { return *bullet; }
	Texture &getTower() const { return *tower; }
	Texture &getAttacker() const { return *attacker; }
	Texture &getLand() const { return *land; }
	Texture &getLand2() const { return *land2; }
	Texture &getInv() const { return *inv; }
};


class Land {
	bool empty;
	Texture image;
	Sprite spLand;

public:
	Land(int num, Vector2f o, AllTextures *texture);
	Sprite getSprite() { return spLand; }
	Vector2f getPositionofLand();
	void setEmpty(bool em) { empty = em; }
	bool getEmpty() const { return empty; }
};




#endif
