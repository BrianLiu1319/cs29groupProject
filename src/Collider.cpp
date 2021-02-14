#include "Collider.h"


std::ostream &operator <<(std::ostream &os, const Collider &collider) {
	os << "uid: " << collider.uid << " health: " << collider.health << " attackSpeed: " << collider.attackSpeed
	   << " gotHit: " << collider.gotHit << " sprite: X:" << collider.sprite.getOrigin().x <<" Y:"<< collider.sprite.getOrigin().y;
	return os;
}
