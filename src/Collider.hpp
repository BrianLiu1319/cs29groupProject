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
enum DIRECTION {LEFT,RIGHT};

class Collider : public sf::Sprite {
protected:
	int health{100};
	int speed{60};
	bool gotHit{false};
	sf::Texture textureOfObject {sf::Texture()};
	void hurt(Collider& other);   // remove other.health - this.health and trigger hurt animation
	void updateObject();          // call funcs to calculate or whatever is needed to be done
	void animate();               // animate object

	/**************************
 	*  Default constructor
 	*  Creates an object with
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
	virtual void autoTravel(DIRECTION direction);
};

class Bullet : public Collider {
	DIRECTION defaulDirection= RIGHT;
public:
	void autoTravel()  {Collider::autoTravel(defaulDirection);}

	Bullet(const std::string &textureFileName) : Collider(textureFileName) { }
	Bullet(int damagePoint) : Collider(damagePoint){}
	Bullet(int damagePoint, int movementSpeed) : Collider(damagePoint,movementSpeed){}
	~Bullet() = default;
};

class Attacker : public Collider {
	DIRECTION defaulDirection= LEFT;
	int movementSpeed {60};
	void walk() {}
	void attack() {}
	void dead() {}

public:
	void autoTravel() {	Collider::autoTravel(defaulDirection);}
	~Attacker(){ }
	Attacker(const std::string &textureFileName, int attackSpeed) : Collider(textureFileName), movementSpeed(attackSpeed) { }
	Attacker(const std::string &textureFileName) : Collider(textureFileName) { }
};

class Defender : public Collider {
private:
	int price {40};
	void fire () {
		// create a bullet object
	}
	void death() {

	}
	void idle() {}

public:
	Defender(sf::Vector2f location) { this->setPosition(location);} ;
	Defender(const std::string &textureFileName, int price) : Collider(textureFileName), price(price) {
		std::cout << "Def Const" << std::endl;
	}
	~Defender() { }
};

#endif //CS29GROUPPROJECT_COLLIDER_H