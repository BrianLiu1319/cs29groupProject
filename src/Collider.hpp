#ifndef CS29GROUPPROJECT_COLLIDER_H
#define CS29GROUPPROJECT_COLLIDER_H

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.h"
#include "SFML/System/Time.h"
#include <ostream>

//Res const path
static const std::string ResourcePath = "res/";

// direction types for Auto Travel
enum DIRECTION {
	LEFT, RIGHT
};

class Collider : public sf::Sprite {
protected:
	int health {100};
	int speed {60};
	sf::Texture textureOfObject {sf::Texture()};

	// remove other.health - this.health and trigger hurt animation
	void animate();               // animate object
	/**************************
 	*  Default constructor
 	*  Creates an object with
 	*  	health = 100
 	*  	speed = 60
	*   textureOfObj = texture()
	**************************/
	Collider() = default;

	friend std::ostream &operator <<(std::ostream &os, const Collider &collider);

	Collider(int health, int speed) : health(health), speed(speed) { }

	Collider(int health) : health(health), speed(60) { }

	Collider(const std::string &textureFileName);

	// will be deleted
	std::string typeName() const;

public:
	~Collider() override { std::cout << "Collider Destructor" << std::endl; }

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

	Bullet(const std::string &textureFileName) : Collider(textureFileName) { }

	Bullet(int damagePoint) : Collider(damagePoint) { }

	Bullet(int damagePoint, int movementSpeed) : Collider(damagePoint, movementSpeed) { }
};

class Attacker : public Collider {
	DIRECTION defaulDirection = LEFT;
	int movementSpeed {60};

	void walk() { }

	void attack() { }

	void dead() { }

public:
	void hurt(Collider &other) override;

public:
	void autoTravel() { Collider::autoTravel(defaulDirection); }

	Attacker(const std::string &textureFileName, int attackSpeed) : Collider(textureFileName),
	                                                                movementSpeed(attackSpeed) { }

	Attacker(const std::string &textureFileName) : Collider(textureFileName) { }
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
	Defender(sf::Vector2f location) { this->setPosition(location); };

	Defender(const std::string &textureFileName, int price) : Collider(textureFileName), price(price) {
		std::cout << "Def Const" << std::endl;
	}

	~Defender() { }
};

#endif //CS29GROUPPROJECT_COLLIDER_H