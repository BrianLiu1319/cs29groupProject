#ifndef CS29GROUPPROJECT_COLLIDER_H
#define CS29GROUPPROJECT_COLLIDER_H
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"
#include <ostream>

class Collider : public sf::Sprite {
protected:
	//const unsigned int uid {static_cast<unsigned int>((rand() + 1) * (rand() + 1) * 4 % 4294967295)};
	int health{100};
	int speed{60};
	bool gotHit{false};
	sf::Texture textureOfObject {sf::Texture()};
//	virtual void animate() = 0;
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
	virtual void collided(Collider &otherObj);

	/********************************************************
	 *  Calculates the distance between 2 Collider objects
	 *  by subtracting their origins
	 *
	 *  Input:Address of a Collider OBJ
	 *  Output:Returns the difference a V2F which has X and Y
	********************************************************/
	virtual sf::Vector2f calcDistance(Collider &attacker) const {
		return (this->getPosition() - attacker.getPosition());
	}

	friend std::ostream &operator <<(std::ostream &os, const Collider &collider);

	Collider(int health, int speed) : health(health), speed(speed), gotHit(false) { }

	Collider(int health) : health(health), speed(60), gotHit(false) { }

	Collider(const std::string &textureFileName);

	Collider(sf::Vector2f location) { this->setPosition(location); }

	std::string typeName() const;
};

class Bullet : public Collider {
public:
	Bullet(const std::string &textureFileName) : Collider(textureFileName) { }
	Bullet(int damagePoint) : Collider(damagePoint){}
	Bullet(int damagePoint, int movementSpeed) : Collider(damagePoint,movementSpeed){}
	void travel (sf::RenderTarget& win);
	~Bullet() = default;
};

class Attacker : public Collider {
	int attackSpeed {60};
	void walk() {}
	void attack() {}
	void dead() {}
public:

	~Attacker(){ }
	Attacker(const std::string &textureFileName, int attackSpeed) : Collider(textureFileName),
	                                                                attackSpeed(attackSpeed) { }
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
	Defender(const std::string &textureFileName, int price) : Collider(textureFileName), price(price) {
		std::cout << "Def Const" << std::endl;
	}
	~Defender() { }
};

#endif //CS29GROUPPROJECT_COLLIDER_H