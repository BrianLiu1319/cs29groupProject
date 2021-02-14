#ifndef CS29GROUPPROJECT_COLLIDER_H
#define CS29GROUPPROJECT_COLLIDER_H
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.h"
#include "SFML/System/Time.h"
#include <ostream>

class Collider {
protected:
	const unsigned int uid {static_cast<unsigned int>((rand() + 1) * (rand() + 1) * 4 % 4294967295)};
	unsigned int health {100};
	unsigned int attackSpeed{60};
	bool gotHit {false};
	sf::Sprite spriteOfObject {sf::Sprite()};
public:
	/**************************
 	*  Default constructor
 	*  Creates an object with
 	*  	uuid= random
 	*  	health = 100
 	*  	attackSpeed = 60
 	*  	gotHit = False
	*   spriteOfObject = Sprite()
	**************************/
	Collider() = default;

	/********************************************************
	 *  Returns the origin of Sprite OBJ in a V2F
	********************************************************/
	virtual sf::Vector2f getOrigin() const { return spriteOfObject.getOrigin(); }

	/********************************************************
	 *  Returns the obj hit bool
	********************************************************/
	virtual bool collided() const { return this->gotHit; }

	/********************************************************
	 *  Calculates the distance between 2 Collider objects
	 *  by subtracting their origins
	 *
	 *  Input:Adress of a Collider OBJ
	 *  Output:Returns the difference a V2F which has X and Y
	********************************************************/
	virtual sf::Vector2f calcDistance(Collider &attacker) const { return (this->getOrigin() - attacker.getOrigin()); }

	explicit Collider(sf::Sprite &newSprite) { this->spriteOfObject = newSprite; }

	friend std::ostream &operator <<(std::ostream &os, const Collider &collider);

	Collider(unsigned int health, unsigned int attackSpeed) : health(health), attackSpeed(attackSpeed) { }

	Collider(const std::string& textureFileName);
};

class Bullet : public Collider {
	public:
	Bullet() : Collider(1,0){};
};

class Attacker : public Collider {

};

class Defender : public Collider {

};

#endif //CS29GROUPPROJECT_COLLIDER_H