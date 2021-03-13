#ifndef INVENTORY_HPP
#define INVENTORY_HPP
#include "Collider.hpp"

class Inventory {
	Sprite invSprite;
	int contain;  // if contain == 0 it's a dog, if contain is 1,this Inventory
	              // contain a sunflower
public:
	Inventory(Vector2f pt, int co, const Texture &texture);
	Sprite getSprite() { return invSprite; }
};


#endif  // INVENTORY_HPP
