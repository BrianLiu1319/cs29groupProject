#ifndef CS29GROUPPROJECT_COLLIDER_H
#define CS29GROUPPROJECT_COLLIDER_H
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.h"
#include "SFML/System/Time.h"
#include <ostream>

class Collider : public sf::Sprite {
protected:
	//const unsigned int uid {static_cast<unsigned int>((rand() + 1) * (rand() + 1) * 4 % 4294967295)};
	unsigned int health {100};
	unsigned int attackSpeed{60};
	bool gotHit {false};
	sf::Texture textureOfObject {sf::Texture()};
	/**************************
 	*  Default constructor
 	*  Creates an object with
 	*  	uuid= random (OPTIONAL - DEBUG)
 	*  	health = 100
 	*  	attackSpeed = 60
 	*  	gotHit = False
	*   textureOfObj = texture()
	**************************/
	Collider() = default;

	/********************************************************
	 *  Returns the obj hit bool
	********************************************************/
	virtual bool collided() const { return this->gotHit; }

	/********************************************************
	 *  Calculates the distance between 2 Collider objects
	 *  by subtracting their origins
	 *
	 *  Input:Address of a Collider OBJ
	 *  Output:Returns the difference a V2F which has X and Y
	********************************************************/
	virtual sf::Vector2f calcDistance(Collider &attacker) const { return (this->getOrigin() - attacker.getOrigin()); }

	friend std::ostream &operator <<(std::ostream &os, const Collider &collider);

	explicit Collider(unsigned int health, unsigned int attackSpeed) : health(health), attackSpeed(attackSpeed) { }

	Collider(const std::string& textureFileName);

	std::string typeName() const;
};

class Bullet : public Collider {
	public:
	Bullet(unsigned health) : Collider(health,0){};
};

class Attacker : public Collider {

};

class Defender : public Collider {

};

#endif //CS29GROUPPROJECT_COLLIDER_H