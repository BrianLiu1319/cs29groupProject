#ifndef CS29GROUPPROJECT_INTERFACE_H
#define CS29GROUPPROJECT_INTERFACE_H

#include <SFML/Graphics/Sprite.hpp>
#include "SFML/System/Vector2.h"
#include "SFML/System/Time.h"

class Collider {
protected:
	unsigned char health;
	unsigned attackSpeed;
	bool gotHit;
	sf::Sprite sprite;
public:
	Collider() : health(100), attackSpeed(90), gotHit(false) { };
	~Collider() = default ;
	virtual sf::Vector2f getOrigin() const {return sprite.getOrigin();};
	virtual bool collided () const {return gotHit;}
	virtual sf::Vector2f getDistance(Collider& attacker) const {
		return (this->getOrigin() - attacker.getOrigin());
	};
};
#endif //CS29GROUPPROJECT_INTERFACE_H
//uid((rand()*rand()*4) % 4294967295)