#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include "Collider.h"


std::ostream &operator <<(std::ostream &os, const Collider &collider) {
	os << "uid: " << collider.uid << " health: " << collider.health << " attackSpeed: " << collider.attackSpeed
	   << " gotHit: " << collider.gotHit << " spriteOfObject: X:" << collider.spriteOfObject.getOrigin().x << " Y:" << collider.spriteOfObject.getOrigin().y;
	return os;
}

Collider::Collider(const std::string& textureFileName){
	sf::Texture objTexture;
	if (!objTexture.loadFromFile(textureFileName)) {
		std::cerr << "Can not load texture file " << std::endl;
	}
	this->spriteOfObject.setTexture(objTexture, true);
}