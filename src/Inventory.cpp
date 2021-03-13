#include "Inventory.hpp"

Inventory::Inventory(Vector2f pt, int co, AllTextures *allTextures) {
	spInven.setTexture(allTextures->getInv());
	spInven.setPosition(pt);
	spInven.setTextureRect(IntRect(0, 0, 54, 54));
	contain = co;
	// spLand.setScale(Vector2f(0.5, 0.5));
}