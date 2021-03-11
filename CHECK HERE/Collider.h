#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Time.hpp"
#include <ostream>

using namespace std;
using namespace sf;

//Res const path
// This is the only place to change the sprite file

/*
static const string bulSpritePath = "res/sprites/bul.png";
static const string catSpritePath = "res/sprites/cat1.png";
static const string towerSpritePath = "res/sprites/tower.png";
*/



static const string bulSpritePath = "C:/temp/bul.png";
static const string catSpritePath = "C:/temp/cat1.png";
static const string towerSpritePath = "res/sprites/tower.png";
static const string dogeTower = "C:/temp/doge.png";

static const unsigned WINDOW_WIDTH = 1280;
static const unsigned WINDOW_HEIGHT = 720;

// direction types for Auto Travel
enum DIRECTION {
	LEFT, RIGHT, TWR
};

class Collider : public Sprite {
protected:
	int health;
	float speed;
	Texture textureOfObject{ Texture() };
	string spritePath;
	DIRECTION defaultDirection;
	Vector2f position;

	Collider(const string& textureFileName, DIRECTION direction, Vector2f positionOfObj = { 0, 0 }, int objHealth = 100, float objSpeed = 60.0f);
	Collider(const Texture& textureTemp, DIRECTION direction, Vector2f positionOfObj, int objHealth = 10, float objSpeed = 60.0f);
	// remove other.health - this.health and trigger hurt animation
	virtual void animate() {};               // animate object
	friend ostream& operator <<(ostream& os, const Collider& collider);
	//	Collider(int health, int speed) : health(health), speed(speed) { }
	//	Collider(int health) : health(health), speed(60) { }
		// will be deleted
	string typeName() const;
	~Collider() override { cout << "Collider Destructor" << endl; }
	void autoTravel(DIRECTION direction);
public:
	int getHealth() const { return health; }
	void setDirection(DIRECTION ab) { defaultDirection = ab; }
	virtual void hurt(Collider& other);
	virtual void updateObject();          // call funcs to calculate or whatever is needed to be done
};

class Bullet : public Collider {
public:
	Bullet() : Collider(bulSpritePath, RIGHT, { 25, 360 }, 25) { scale(0.1, 0.1); }
	Bullet(sf::Vector2f a) : Collider(bulSpritePath, RIGHT, a, 50) { scale(0.1, 0.1); }
	Bullet(const sf::Texture& temp, sf::Vector2f a) : Collider(temp, RIGHT, a, 25) { scale(0.1, 0.1); }

	//  Bullet() : 
	//	Bullet(int damagePoint) : Collider(damagePoint) { }
	//	Bullet(int damagePoint, int movementSpeed) : Collider(damagePoint, movementSpeed) { }
};

class Attacker : public Collider {
	void attack() { }

public:
	//	void hurt(Collider &other) override;
	Attacker() : Collider(catSpritePath, LEFT, { WINDOW_WIDTH - 20,360 }, 100, 10.0f) {};
	Attacker(sf::Vector2f a) : Collider(catSpritePath, LEFT, { WINDOW_WIDTH, a.y }, 100, 10.0f) { scale(0.5, 0.5); };
};

class Defender : public Collider {
private:
	int price{ 40 };

	void fire() {
		// create a bullet object
	}
public: 
	explicit Defender(const Texture& towerTexture) : Collider(towerTexture, TWR, { 100, 360 }, 100, 0) {};

	Defender(sf::Vector2f a) : Collider(dogeTower, TWR, { a.x, a.y }, 200, 0.0f) { scale(0.5, 0.5); };

};

