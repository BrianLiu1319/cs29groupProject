#ifndef CS29GROUPPROJECT_COLLIDER_H
#define CS29GROUPPROJECT_COLLIDER_H
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.h"
#include "SFML/System/Time.h"
#include <ostream>

enum DIRECTION { LEFT,RIGHT};

class Collider : public sf::Sprite {
protected:
	//const unsigned int uid {static_cast<unsigned int>((rand() + 1) * (rand() + 1) * 4 % 4294967295)};
	int health{100};
	int speed{60};
	bool gotHit{false};
	sf::Texture textureOfObject {sf::Texture()};
//	virtual void animate() = 0;
	void hurt(Collider& other);
	void update();

	/**************************
 	*  Default constructor
 	*  Creates an object with
 	*  	uuid= random (OPTIONAL - DEBUG)
 	*  	health = 100
 	*  	speed = 60
 	*  	gotHit = False
	*   textureOfObj = texture()
	**************************/
	Collider() = default;

	/********************************************************
	 *  Returns the obj hit bool
	********************************************************/
	virtual bool collided() const { return this->gotHit; }

	friend std::ostream &operator <<(std::ostream &os, const Collider &collider);
	Collider(int health, int speed) : health(health), speed(speed) , gotHit(false){ }
	Collider(int health): health(health), speed(60) , gotHit(false){ }
	Collider(const std::string& textureFileName);
	// will be deleted
	std::string typeName() const;

public:
	void autoTravel(DIRECTION direction);
};

class Bullet : public Collider {
public:
	Bullet(const std::string &textureFileName) : Collider(textureFileName) { }
	Bullet(int damagePoint) : Collider(damagePoint){}
	Bullet(int damagePoint, int movementSpeed) : Collider(damagePoint,movementSpeed){}
	~Bullet() = default;
};

class Attacker : public Collider {
	int movementSpeed {60};
	void walk() {}
	void attack() {}
	void dead() {}

public:
	~Attacker(){ }
	Attacker(const std::string &textureFileName, int attackSpeed) : Collider(textureFileName), movementSpeed(attackSpeed) { }
};

class Defender : public Collider {
	int price {40};
	void fire () {
		// create a bullet object
	}
	void death() {

	}
	void idle() {

	}

public:
	Defender(sf::Vector2f location) { this->setPosition(location);} ;
	Defender(const std::string &textureFileName, int price) : Collider(textureFileName), price(price) {
		std::cout << "Def Const" << std::endl;
	}
	~Defender() { }
};

#endif //CS29GROUPPROJECT_COLLIDER_H