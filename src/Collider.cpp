#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include "Collider.h"


std::ostream &operator <<(std::ostream &os, const Collider &collider) {
	os << collider.typeName() << " :" << /*"uid: " << collider.uid <<*/  " health: "
	   << collider.health << " attackSpeed: " << collider.attackSpeed
	   << " gotHit: " << collider.gotHit << " Origin: X:" << collider.getOrigin().x << " Y:" << collider.getOrigin().y;
	return os;
}

Collider::Collider(const std::string &textureFileName) {
	if (!this->textureOfObject.loadFromFile(textureFileName)) {
		std::cerr << "Can not load texture file " << std::endl;
	}
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