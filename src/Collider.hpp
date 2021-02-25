#ifndef CS29GROUPPROJECT_COLLIDER_H
#define CS29GROUPPROJECT_COLLIDER_H

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.h"
#include "SFML/System/Time.h"
#include <ostream>

using namespace std;
using namespace sf;
//Res const path
// This is the only place to change the sprite file
static const string bulSpritePath = "res/sprites/bul.png";
static const string catSpritePath = "res/sprites/cat1.png";
static const string towerSpritePath = "res/sprites/tower.png";
static const unsigned WINDOW_WIDTH = 1280;
static const unsigned WINDOW_HEIGHT = 720;

// direction types for Auto Travel
enum DIRECTION {
	LEFT, RIGHT
};

class Collider : public Sprite {
protected:
	int health {100};
	int speed {60};
	Texture textureOfObject {Texture()};
	string spritePath;
	DIRECTION defaultDirection;

	// remove other.health - this.health and trigger hurt animation
	virtual void animate() {};               // animate object
	friend ostream &operator <<(ostream &os, const Collider &collider);
//	Collider(int health, int speed) : health(health), speed(speed) { }
//	Collider(int health) : health(health), speed(60) { }
	// will be deleted
	string typeName() const;
	Collider(const string &textureFileName,DIRECTION direction = RIGHT);
	~Collider() override { cout << "Collider Destructor" << endl; }
	void autoTravel(DIRECTION direction);
	int getHealth() const { return health; }
public:
	virtual void hurt(Collider &other);
	virtual void updateObject();          // call funcs to calculate or whatever is needed to be done
};

class Bullet : public Collider {

public:
	Bullet() : Collider(bulSpritePath,RIGHT) { }

//	Bullet(int damagePoint) : Collider(damagePoint) { }

//	Bullet(int damagePoint, int movementSpeed) : Collider(damagePoint, movementSpeed) { }
};

class Attacker : public Collider {
	int movementSpeed {60};
	void attack() { }

public:
//	void hurt(Collider &other) override;

	Attacker(const string &textureFileName, int attackSpeed) : Collider(textureFileName), movementSpeed(attackSpeed) { }

	Attacker() : Collider(catSpritePath,LEFT) { }
};

class Defender : public Collider {
private:
	int price {40};

	void fire() {
		// create a bullet object
	}



public:
//	Defender(Vector2f location) { this->setPosition(location); };

	Defender(int price) : Collider(towerSpritePath), price(price) { }

};

#endif //CS29GROUPPROJECT_COLLIDER_H