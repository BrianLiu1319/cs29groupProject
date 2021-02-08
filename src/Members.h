#ifndef CS29GROUPPROJECT_MEMBERS_H
#define CS29GROUPPROJECT_MEMBERS_H
#include "SFML/System/Vector2.h"
#include "SFML/System/Time.h"

class Collidable {
protected:
	unsigned int uid;
	unsigned char health;
	unsigned attackSpeed;
	bool gotHit;
	sf::Sprite sprite;
public:
	Collidable() : uid((rand()*rand()*4) % 4294967295), health(100), attackSpeed(90), gotHit(false) { };
	~Collidable() = default ;
	virtual sf::Vector2f getOrigin() const {return sprite.getOrigin();};
	virtual bool collided () const = 0;
	virtual float getDistance() const = 0;
};

class Defender :public Collidable{
};

class Attacker : public Collidable{
};

class Bullet : public Collidable {
};

#endif //CS29GROUPPROJECT_MEMBERS_H
