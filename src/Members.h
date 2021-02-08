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
	Collidable() : uid((rand()*rand()*4)%4294967295), health(100), attackSpeed(90) { };
	~Collidable() = default ;
	virtual bool collided () const = 0;
	virtual sf::Vector2f getOrigin() const {return sprite.getOrigin();};
	virtual float getDistance() const = 0;
};


class Defender :public Collidable{
public:

};

class Attacker : public Collidable{
public:

};

class Bullet : public Collidable {

};


#endif //CS29GROUPPROJECT_MEMBERS_H
