#include "Inventory.hpp"

Inventory::Inventory(Vector2f pt, int co, const Texture &texture) {
	spInven.setTexture(texture);
	spInven.setPosition(pt);
	spInven.setTextureRect(IntRect(0, 0, 54, 54));
	contain = co;
	// spLand.setScale(Vector2f(0.5, 0.5));
}