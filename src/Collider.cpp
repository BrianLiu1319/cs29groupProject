#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include "Collider.h"

using std::cout;
using std::endl;

std::ostream &operator <<(std::ostream &os, const Collider &collider) {
	os << collider.typeName() << " :" << /*"uid: " << collider.uid <<*/  " health: "
	   << collider.health << " speed: " << collider.speed
	   << " gotHit: " << collider.gotHit << " Origin: X:" << collider.getOrigin().x << " Y:" << collider.getOrigin().y;
	return os;
}

Collider::Collider(const std::string &textureFileName) {
	if (!(textureOfObject.loadFromFile(textureFileName))) {
		std::cerr << "Can not load texture file " << std::endl;
	}
	this->setTexture(textureOfObject);
}

std::string Collider::typeName() const {
	std::string shapeName = typeid(*this).name();
#ifdef _MSC_VER       // for MS Visual Studio
	shapeName = shapeName.substr(6);
#else                 // for other compilers
	shapeName = shapeName.substr(shapeName.find_first_not_of("0123456789"));
#endif
	return shapeName;
}

void Collider::autoTravel(DIRECTION direction) {
	cout <<"this x :" << this->getPosition().x << endl;
	if (direction == RIGHT) {
		this->move(0.1f, 0.0f);
	} else if (direction == LEFT) {
		this->move(-0.1f, 0.0f);
	}
}

