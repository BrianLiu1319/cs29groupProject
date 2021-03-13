#include "Inventory.hpp"

Inventory::Inventory(Vector2f pt, int co, const Texture &texture) {
	invSprite.setTexture(texture);
	invSprite.setPosition(pt);
	invSprite.setTextureRect(IntRect(0, 0, 54, 54));
//	contain = co;
	invSprite.setScale(Vector2f(0.5, 0.5));
}