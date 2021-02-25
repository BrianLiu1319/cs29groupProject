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
	// remove other.health - this.health and trigger hurt animation
	void animate();               // animate object
	friend ostream &operator <<(ostream &os, const Collider &collider);

//	Collider(int health, int speed) : health(health), speed(speed) { }

//	Collider(int health) : health(health), speed(60) { }

	// will be deleted
	string typeName() const;
public:

	Collider(const string &textureFileName);
	~Collider() override { cout << "Collider Destructor" << endl; }

	virtual void hurt(Collider &other);

	void updateObject();          // call funcs to calculate or whatever is needed to be done

	virtual void autoTravel(DIRECTION direction);

	int getHealth() const { return health; }
};

class Bullet : public Collider {
	DIRECTION defaultDirection = RIGHT;
public:
	void hurt(Collider &other) override;

	void autoTravel() { Collider::autoTravel(defaultDirection); }

	Bullet() : Collider(bulSpritePath) { }

//	Bullet(int damagePoint) : Collider(damagePoint) { }

//	Bullet(int damagePoint, int movementSpeed) : Collider(damagePoint, movementSpeed) { }
};

class Attacker : public Collider {
	DIRECTION defaultDirection = LEFT;
	int movementSpeed {60};

	void walk() { }

	void attack() { }

	void dead() { }

public:
	void hurt(Collider &other) override;
	void autoTravel() { Collider::autoTravel(defaultDirection); }

	Attacker(const string &textureFileName, int attackSpeed) : Collider(textureFileName), movementSpeed(attackSpeed) { }

	Attacker() : Collider(catSpritePath) { }
};

class Defender : public Collider {
private:
	int price {40};

	void fire() {
		// create a bullet object
	}

	void death() {

	}

	void idle() { }

public:
//	Defender(Vector2f location) { this->setPosition(location); };

	Defender(int price) : Collider(towerSpritePath), price(price) { }

};

#endif //CS29GROUPPROJECT_COLLIDER_H